/* SPDX-License-Identifier: GPL-2.0-or-later */
 
#pragma once
 
#define VIAL_KEYBOARD_UID {0x3F, 0x8A, 0x2C, 0x15, 0x9B, 0x47, 0xE1, 0x6D}
 
#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 13 }
 
#define DYNAMIC_KEYMAP_LAYER_COUNT 4

#ifndef RGBLIGHT_ENABLE
#define RGBLIGHT_ENABLE
#endif
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
