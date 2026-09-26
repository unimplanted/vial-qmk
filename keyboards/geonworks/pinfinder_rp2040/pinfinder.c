// RP2040 matrix / WS2812 pin finder.
// Open a text editor, plug the board in, press keys.  For every key press
// the board types  "GPa>GPb"  meaning: driving GPa LOW pulled GPb LOW.
//   COL2ROW board: a = row pin, b = col pin
//   ROW2COL board: a = col pin, b = row pin
// (whichever side ends up with 10 distinct pins is the row side)
//
// Hold any key 3..10 s then release: WS2812 LED test on every pin that has
// not appeared in a key press yet. Board types "LEDn " before each attempt;
// the caps LED lights up (white) on the correct pin and stays lit.
// Hold any key > 10 s: jump to the UF2 bootloader.
#include "quantum.h"
#include "hardware/structs/timer.h"
#include "hardware/structs/sio.h"
#include <stdio.h>

#define NPINS 30
#define STABLE_SCANS 8

static uint32_t stuck_mask;           // pins that read low with nothing driven
static uint32_t used_mask;            // pins seen in any key press
static uint32_t raw[NPINS], deb[NPINS];
static uint8_t  cnt[NPINS];
static uint32_t baseline[NPINS];     // pairs connected with no key pressed (ignored)

#define QLEN 32
static uint8_t q_a[QLEN], q_b[QLEN];
static uint8_t q_head, q_tail;

static bool     announced;
static bool     holding;
static uint32_t hold_start;
static bool     want_led_test;

static inline uint32_t read_all(void) { return sio_hw->gpio_in & ((1u << NPINS) - 1); }

void matrix_init_custom(void) {
    for (uint8_t p = 0; p < NPINS; p++) gpio_set_pin_input_high(p);
    wait_ms(5);
    stuck_mask = ~read_all() & ((1u << NPINS) - 1);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    for (uint8_t a = 0; a < NPINS; a++) {
        if (stuck_mask & (1u << a)) { raw[a] = 0; continue; }
        gpio_set_pin_output(a);
        gpio_write_pin_low(a);
        wait_us(15);
        uint32_t low = ~read_all() & ((1u << NPINS) - 1);
        low &= ~(1u << a);
        low &= ~stuck_mask;
        gpio_set_pin_input_high(a);
        raw[a] = low;
    }
    wait_us(20);

    if (timer_read32() < 1500) {   // learn always-connected pairs, don't report
        for (uint8_t a = 0; a < NPINS; a++) { baseline[a] |= raw[a]; deb[a] = 0; }
        return false;
    }
    for (uint8_t a = 0; a < NPINS; a++) raw[a] &= ~baseline[a];

    bool any = false;
    for (uint8_t a = 0; a < NPINS; a++) {
        if (raw[a] != deb[a]) {
            if (++cnt[a] >= STABLE_SCANS) {
                uint32_t rising = raw[a] & ~deb[a];
                for (uint8_t b = 0; b < NPINS; b++) {
                    if (rising & (1u << b)) {
                        uint8_t n = (q_head + 1) % QLEN;
                        if (n != q_tail) { q_a[q_head] = a; q_b[q_head] = b; q_head = n; }
                        used_mask |= (1u << a) | (1u << b);
                    }
                }
                deb[a] = raw[a];
                cnt[a] = 0;
            }
        } else {
            cnt[a] = 0;
        }
        if (deb[a]) any = true;
    }

    uint32_t now = timer_read32();
    if (any && !holding) { holding = true; hold_start = now; }
    if (holding) {
        uint32_t held = now - hold_start;
        if (held > 10000) reset_keyboard();
        if (!any) {
            holding = false;
            if (held >= 3000) want_led_test = true;
        }
    }
    (void)current_matrix;
    return false;
}

// ---------- WS2812 bit-bang (self-calibrating, all-ones = tolerant) ----------
static uint32_t loops_per_us = 30;

static inline void __attribute__((always_inline)) spin(uint32_t n) {
    while (n--) __asm__ volatile("nop");
}

static void calibrate(void) {
    chSysLock();
    uint32_t t0 = timer_hw->timerawl;
    spin(200000);
    uint32_t t1 = timer_hw->timerawl;
    chSysUnlock();
    uint32_t dt = t1 - t0;
    if (dt) loops_per_us = 200000 / dt;
    if (!loops_per_us) loops_per_us = 1;
}

static void ws_send(uint8_t pin, uint8_t val, uint8_t nleds) {
    uint32_t mask = 1u << pin;
    uint32_t t0h = (loops_per_us * 35) / 100;  // ~350 ns
    uint32_t t0l = (loops_per_us * 80) / 100;  // ~800 ns
    uint32_t t1h = (loops_per_us * 75) / 100;  // ~750 ns
    uint32_t t1l = (loops_per_us * 50) / 100;  // ~500 ns
    gpio_set_pin_output(pin);
    gpio_write_pin_low(pin);
    wait_us(300);
    chSysLock();
    for (uint8_t l = 0; l < nleds * 3; l++) {
        for (uint8_t bit = 0; bit < 8; bit++) {
            if (val & (0x80 >> bit)) {
                sio_hw->gpio_set = mask; spin(t1h);
                sio_hw->gpio_clr = mask; spin(t1l);
            } else {
                sio_hw->gpio_set = mask; spin(t0h);
                sio_hw->gpio_clr = mask; spin(t0l);
            }
        }
    }
    chSysUnlock();
    wait_us(300);
    gpio_set_pin_input_high(pin);
}

static void led_test(void) {
    char buf[64];
    calibrate();
    snprintf(buf, sizeof(buf), "\nLED test (cal %lu/us): ", (unsigned long)loops_per_us);
    send_string(buf);
    for (uint8_t p = 0; p < NPINS; p++) {
        if (used_mask & (1u << p)) continue;
        snprintf(buf, sizeof(buf), "LED%u ", p);
        send_string(buf);
        ws_send(p, 0x40, 4);   // dim white on up to 4 chained LEDs
        wait_ms(1500);
    }
    send_string("done\n");
}

void housekeeping_task_kb(void) {
    char buf[48];
    if (!announced && timer_read32() > 3000) {
        announced = true;
        send_string("\nPinFinder ready. stuck-low:");
        if (!stuck_mask) send_string(" none");
        for (uint8_t p = 0; p < NPINS; p++) {
            if (stuck_mask & (1u << p)) { snprintf(buf, sizeof(buf), " GP%u", p); send_string(buf); }
        }
        send_string("\n");
    }
    if (!announced) return;
    while (q_tail != q_head) {
        snprintf(buf, sizeof(buf), "GP%u>GP%u\n", q_a[q_tail], q_b[q_tail]);
        q_tail = (q_tail + 1) % QLEN;
        send_string(buf);
    }
    if (want_led_test) { want_led_test = false; led_test(); }
}
