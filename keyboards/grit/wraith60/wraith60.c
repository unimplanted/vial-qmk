// Copyright 2026 unimplanted
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef RGBLIGHT_ENABLE
// Caps Lock tints the underglow cyan while keeping the current effect running.
// Every rgblight effect converts HSV to RGB through this weak hook, so only the
// output colour changes: the saved mode/hue/sat/val (and EEPROM) are untouched,
// and the original colour returns as soon as Caps Lock is released.
//#    define CAPS_LOCK_HUE 128 // cyan
//#    define CAPS_LOCK_SAT 255 // fully saturated, so it stays cyan even on white

//#    define CAPS_LOCK_HUE 11  // coral
//#    define CAPS_LOCK_SAT 175 // fully saturated, so it stays cyan even on white

//#    define CAPS_LOCK_HUE 21  // orange
//#    define CAPS_LOCK_SAT 255 // fully saturated, so it stays cyan even on white

#    define CAPS_LOCK_HUE 213 // margenta
#    define CAPS_LOCK_SAT 255 // fully saturated, so it stays cyan even on white

static bool caps_tint = false;

rgb_t rgblight_hsv_to_rgb(hsv_t hsv) {
    if (caps_tint) {
        hsv.h = CAPS_LOCK_HUE;
        hsv.s = CAPS_LOCK_SAT;
    }
    return hsv_to_rgb(hsv);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        led_update_ports(led_state); // Caps Lock LED on A1 (from "indicators")
    }
    if (res && caps_tint != led_state.caps_lock) {
        caps_tint = led_state.caps_lock;
        // Animated effects pick the tint up on their next frame; re-applying
        // the current mode also redraws static ones immediately.
        if (rgblight_is_enabled()) {
            rgblight_mode_noeeprom(rgblight_get_mode());
        }
    }
    return res;
}
#endif
