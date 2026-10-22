#pragma once

#define VIAL_KEYBOARD_UID {0x9F, 0xCD, 0xD6, 0x08, 0x71, 0x2C, 0xCA, 0x96}

#define DYNAMIC_KEYMAP_LAYER_COUNT 8

/* Unlock combo: Esc (0,0) + Enter (3,13) */
#ifndef RGBLIGHT_ENABLE
 #define VIAL_UNLOCK_COMBO_ROWS { 0, 3 }
 #define VIAL_UNLOCK_COMBO_COLS { 0, 13 }
#endif

