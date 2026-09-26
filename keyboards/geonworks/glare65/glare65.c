// Copyright 2026
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
// The single LED under Caps Lock is a Caps Lock indicator.
// Effect / color / brightness come from RGB Matrix settings (Vial Lighting tab);
// the LED is forced off whenever Caps Lock is off.
bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) return false;
    if (!host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(0, 0, 0, 0);
    }
    return false;
}

#endif
