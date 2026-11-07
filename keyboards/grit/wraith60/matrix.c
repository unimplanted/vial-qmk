// Copyright 2026 unimplanted
// SPDX-License-Identifier: GPL-2.0-or-later
//
// GritWorks Wraith60 (solder) custom matrix.
//
// Reconstructed from the vendor Vial firmware (2025-07-15). The PCB has no
// row/column matrix: a chain of 9 shift registers (72 outputs) drives one
// key at a time, and every key is sensed on a single shared input (A3).
//
//   A5 = shift clock, A7 = serial data, A4 = latch  (bit-banged, LSB first)
//   A3 = sense input (pull-down, high = pressed)
//
// To read key (r, c): latch low, shift out 9 bytes that are all zero except
// byte key_select[r][c].byte which holds key_select[r][c].mask, latch high,
// then sample A3. The chain is cleared again after every read.

#include "quantum.h"
#include "matrix.h"

#define SR_CLK_PIN A5
#define SR_DATA_PIN A7
#define SR_LATCH_PIN A4
#define SENSE_PIN A3
#define SR_BYTES 9

typedef struct {
    uint8_t byte;
    uint8_t mask;
} key_select_t;

// {byte index, bit mask} per matrix position; {0, 0} = no switch.
static const key_select_t key_select[MATRIX_ROWS][MATRIX_COLS] = {
    {{8, 0x40}, {8, 0x20}, {8, 0x10}, {8, 0x08}, {8, 0x04}, {8, 0x02}, {8, 0x01}, {7, 0x40}, {7, 0x20}, {7, 0x10}, {7, 0x08}, {7, 0x04}, {7, 0x02}, {7, 0x01}, {2, 0x40}},
    {{0, 0x10}, {5, 0x01}, {5, 0x02}, {5, 0x04}, {5, 0x08}, {5, 0x10}, {5, 0x20}, {6, 0x01}, {6, 0x02}, {6, 0x04}, {6, 0x08}, {6, 0x10}, {6, 0x20}, {6, 0x40}, {0, 0x00}},
    {{4, 0x40}, {4, 0x20}, {4, 0x10}, {4, 0x08}, {4, 0x04}, {4, 0x02}, {4, 0x01}, {3, 0x40}, {3, 0x20}, {3, 0x10}, {3, 0x08}, {3, 0x04}, {3, 0x02}, {3, 0x01}, {0, 0x00}},
    {{0, 0x08}, {0, 0x04}, {0, 0x02}, {0, 0x01}, {1, 0x40}, {1, 0x20}, {1, 0x10}, {1, 0x08}, {1, 0x04}, {1, 0x02}, {1, 0x01}, {3, 0x80}, {2, 0x20}, {2, 0x10}, {0, 0x00}},
    {{0, 0x00}, {0, 0x40}, {0, 0x20}, {0, 0x00}, {0, 0x00}, {1, 0x80}, {0, 0x00}, {2, 0x04}, {0, 0x00}, {2, 0x02}, {0, 0x00}, {2, 0x01}, {2, 0x08}, {0, 0x00}, {0, 0x00}},
};

static void sr_shift_byte(uint8_t value) {
    for (uint8_t bit = 0; bit < 8; bit++) {
        gpio_write_pin_low(SR_CLK_PIN);
        gpio_write_pin(SR_DATA_PIN, (value >> bit) & 1);
        gpio_write_pin_high(SR_CLK_PIN);
    }
}

static void sr_select(uint8_t byte, uint8_t mask) {
    gpio_write_pin_low(SR_LATCH_PIN);
    for (uint8_t i = 0; i < SR_BYTES; i++) {
        sr_shift_byte(i == byte ? mask : 0);
    }
    gpio_write_pin_high(SR_LATCH_PIN);
}

static inline void sr_clear(void) {
    sr_select(0xFF, 0);
}

void matrix_init_custom(void) {
    gpio_set_pin_output_push_pull(SR_CLK_PIN);
    gpio_set_pin_output_push_pull(SR_DATA_PIN);
    gpio_set_pin_output_push_pull(SR_LATCH_PIN);
    gpio_write_pin_high(SR_CLK_PIN);
    gpio_write_pin_high(SR_DATA_PIN);
    gpio_write_pin_high(SR_LATCH_PIN);
    gpio_set_pin_input_low(SENSE_PIN);
    sr_clear();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t row_data = current_matrix[row];

        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            const key_select_t sel = key_select[row][col];
            sr_select(sel.byte, sel.mask);
            waitInputPinDelay();

            if (gpio_read_pin(SENSE_PIN)) {
                row_data |= (MATRIX_ROW_SHIFTER << col);
            } else {
                row_data &= ~(MATRIX_ROW_SHIFTER << col);
            }

            sr_clear();
            matrix_output_unselect_delay(col, false);
        }

        if (current_matrix[row] != row_data) {
            current_matrix[row] = row_data;
            changed = true;
        }
    }

    return changed;
}
