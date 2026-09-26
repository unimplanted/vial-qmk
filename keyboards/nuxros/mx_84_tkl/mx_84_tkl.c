// Copyright 2026 HMC Studio
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "ws2812.h"

void keyboard_pre_init_kb(void) {
    // PB4 is NJTRST after reset. Disable JTAG only (keep SWD for recovery)
    // so PB4 can be used as the WS2812 data pin.
    AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG) | AFIO_MAPR_SWJ_CFG_JTAGDISABLE;

    // Keep the first WS2812 DIN low before the RGB Matrix driver starts.
    gpio_set_pin_output(WS2812_DI_PIN);
    gpio_write_pin_low(WS2812_DI_PIN);

    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
    // Clear any color latched while the MCU was resetting before honoring EEPROM state.
    ws2812_set_color_all(0, 0, 0);
    ws2812_flush();

    keyboard_post_init_user();
}
