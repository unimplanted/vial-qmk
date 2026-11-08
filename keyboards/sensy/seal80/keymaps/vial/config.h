// Copyright 2026 unimplanted
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* UID taken from the stock Eason Seal.80 (MX) Vial firmware */
#define VIAL_KEYBOARD_UID {0x14, 0x59, 0x23, 0x99, 0x6A, 0xDB, 0x2F, 0xE9}

/* Stock firmware: 4 layers, 2079-byte macro buffer. 8 layers costs +784 bytes,
 * leaving ~1.3 KB for macros in the same EEPROM. */
#define DYNAMIC_KEYMAP_LAYER_COUNT 8
