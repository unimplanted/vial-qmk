// Copyright 2025 Andrew Kannan (awkannan)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,  KC_5,  KC_6,  KC_7,  KC_8,    KC_9,    KC_0,   KC_MINS,  KC_EQL,   KC_BSPC, KC_BSPC, KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,    KC_O,    KC_P,   KC_LBRC,  KC_RBRC,  KC_BSLS,
  KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,  KC_G,  KC_H,  KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENTER,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, KC_RSFT, KC_RSFT,
  KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,                              KC_RALT, KC_RGUI, KC_RCTL
)
};



void bootmagic_scan(void) {
  matrix_scan();
  wait_ms(DEBOUNCE * 2);
  matrix_scan();

  if (matrix_get_row(BOOTMAGIC_ROW) & (1 << BOOTMAGIC_COLUMN)) {
    // Jump to bootloader.
    bootloader_jump();
  }
}

void keyboard_post_init_user(void) {
  gpio_set_pin_output(GP7);
  gpio_set_pin_output(GP10);
  gpio_set_pin_output(GP12);

  gpio_write_pin(GP7, 0);
  gpio_write_pin(GP10, 0);
  gpio_write_pin(GP12, 1);
}

bool led_update_kb(led_t led_state) {
  bool res = led_update_user(led_state);
  if(res) {
    gpio_write_pin(GP7, !led_state.caps_lock);
    gpio_write_pin(GP10, !led_state.caps_lock);
    gpio_write_pin(GP12, led_state.caps_lock);
  }
  return res;
}