// Copyright 2026 unimplanted
// SPDX-License-Identifier: GPL-2.0-or-later
//
// 제조사 펌웨어(ramune60_via_260604R1) 리버스 엔지니어링 결과:
//   keyboard_pre_init (0x10000428): GP7/GP10/GP12 = SIO 출력, 초기값 GP7=H, GP10=H, GP12=L
//   led_update_kb     (0x10000464): Caps ON  -> GP7=L, GP10=L, GP12=H  (LED 2개 모두 점등)
//                                   Caps OFF -> GP7=H, GP10=H, GP12=L  (모두 소등)
//
// Caps Lock LED는 마제식/체리식 위치 2개. 어느 핀이 어느 LED인지 회로도가 없어
// CLED_MODE 키(QK_KB_0, Vial "Custom" 탭)로 Caps ON 시 핀 패턴을 순환 선택하게 함.
// 선택값은 EEPROM(eeconfig_kb)에 저장.

#include "quantum.h"

#define CAPS_LED_N1 GP7   // L = 점등 (sink)
#define CAPS_LED_N2 GP10  // L = 점등 (sink)
#define CAPS_LED_P  GP12  // H = 점등 (source)

enum { CLED_MODE = QK_KB_0 };

typedef struct {
    bool gp7, gp10, gp12;
} caps_pins_t;

// Caps OFF 패턴은 항상 원본과 동일 (H, H, L)
static const caps_pins_t caps_off = {true, true, false};

// Caps ON 패턴 후보
static const caps_pins_t caps_on[] = {
    {false, false, true },  // 0: 원본 (모두 점등)
    {false, true,  true },  // 1: GP7만 sink
    {true,  false, true },  // 2: GP10만 sink
    {true,  true,  true },  // 3: GP12만 source
    {false, false, false},  // 4: GP7+GP10 sink, GP12 끔
};
#define CAPS_MODE_COUNT (sizeof(caps_on) / sizeof(caps_on[0]))

static uint8_t caps_mode = 0;

static void caps_led_apply(bool on) {
    const caps_pins_t *p = on ? &caps_on[caps_mode] : &caps_off;
    gpio_write_pin(CAPS_LED_N1, p->gp7);
    gpio_write_pin(CAPS_LED_N2, p->gp10);
    gpio_write_pin(CAPS_LED_P, p->gp12);
}

void keyboard_pre_init_kb(void) {
    gpio_set_pin_output(CAPS_LED_N1);
    gpio_set_pin_output(CAPS_LED_N2);
    gpio_set_pin_output(CAPS_LED_P);
    caps_led_apply(false);
    keyboard_pre_init_user();
}

void eeconfig_init_kb(void) {
    caps_mode = 0;
    eeconfig_update_kb(caps_mode);
    eeconfig_init_user();
}

void keyboard_post_init_kb(void) {
    uint32_t v = eeconfig_read_kb();
    caps_mode  = (v < CAPS_MODE_COUNT) ? (uint8_t)v : 0;
    caps_led_apply(host_keyboard_led_state().caps_lock);
    keyboard_post_init_user();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        caps_led_apply(led_state.caps_lock);
    }
    return res;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (keycode == CLED_MODE) {
        if (record->event.pressed) {
            caps_mode = (caps_mode + 1) % CAPS_MODE_COUNT;
            eeconfig_update_kb(caps_mode);
            caps_led_apply(host_keyboard_led_state().caps_lock);
        }
        return false;
    }
    return process_record_user(keycode, record);
}
