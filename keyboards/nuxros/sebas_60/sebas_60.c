/* Copyright 2023 Cheng Liren
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "quantum.h"

void bootloader_jump(void) {
    uint32_t *boot_magic = (uint32_t *)0x20004c00;
    *boot_magic          = 0xc220b134;
    NVIC_SystemReset();
}

void mcu_reset(void) {
    NVIC_SystemReset();
}

void matrix_init_user(void) {
    gpio_write_pin_low(WS2812_DI_PIN);
}

#ifdef RGBLIGHT_ENABLE
// const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {0, 4, HSV_RED}
// );

// const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
//     my_capslock_layer
// );

// led_t m_led;

// bool led_update_kb(led_t led_state)
// {
//     if (!led_update_user(led_state)) {
//         return false;
//     }
//     m_led = led_state;
//     rgblight_set_layer_state(0, led_state.caps_lock);
//     return true;
// }

// #include "ws2812.h"

// void ws2812_setleds_custom(rgb_led_t *ledarray, uint16_t leds) {
//     // if (m_led.caps_lock == false) {
//     //     ledarray[0].r = 0;
//     //     ledarray[0].g = 0;
//     //     ledarray[0].b = 0;
//     // }

//     ws2812_setleds(ledarray, leds);
// }

// const rgblight_driver_t rgblight_driver = {
//     .init    = ws2812_init,
//     .setleds = ws2812_setleds_custom,
// };

// void keyboard_post_init_kb(void) {
//     rgblight_layers = my_rgb_layers;
//     keyboard_post_init_user();
// }

#endif
