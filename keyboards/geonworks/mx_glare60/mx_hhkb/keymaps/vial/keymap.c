#include QMK_KEYBOARD_H
#include "rgblight.h"

#define COLOR_RED         255, 0, 0      // 빨강
#define COLOR_GREEN       0, 255, 0      // 초록
#define COLOR_BLUE        0, 0, 255      // 파랑
#define COLOR_YELLOW      255, 255, 0    // 노랑
#define COLOR_CYAN        0, 255, 255     // 청록
#define COLOR_MAGENTA     255, 0, 255    // 자주
#define COLOR_ORANGE      255, 165, 0     // 오렌지
#define COLOR_PURPLE      128, 0, 128     // 보라
#define COLOR_WHITE       255, 255, 255   // 흰색
#define COLOR_OFF         0, 0, 0         // 꺼짐

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [0] = LAYOUT_all(
    KC_ESC,   KC_1,     KC_2,     KC_3,  KC_4,    KC_5,  KC_6,   KC_7,  KC_8,  KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSLS,   KC_GRV,
    KC_TAB,   KC_Q,     KC_W,     KC_E,  KC_R,    KC_T,  KC_Y,   KC_U,  KC_I,  KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSPC,
    KC_LCTL,  KC_A,     KC_S,     KC_D,  KC_F,    KC_G,  KC_H,   KC_J,  KC_K,  KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENTER,  KC_ENTER,
    KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,  KC_C,    KC_V,  KC_B,   KC_N,  KC_M,  KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  MO(1),
              KC_LALT,  KC_LGUI,                            KC_SPC,                                KC_RGUI,  KC_RALT),

    [1] = LAYOUT_all(
    _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_INS,   _______,
    KC_CAPS,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,  KC_SCRL,  KC_PAUS,  KC_UP,    _______,  KC_DEL,
    _______,  KC_VOLD,  KC_VOLU,  KC_MUTE,  _______,  _______,  _______,  _______,  KC_HOME,  KC_PGUP,  KC_LEFT,  KC_RGHT,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_END,   KC_PGDN,  KC_DOWN,  _______,  _______,
              _______,  _______,                                     _______,                                     MO(2),    _______),

    [2] = LAYOUT_all(
    QK_BOOT,  NK_TOGG,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
              _______,  _______,                                     _______,                                     _______,  _______)
    // clang-format on
};

// ↓↓↓ 아래 함수 추가 ↓↓↓

// LED 업데이트 함수

bool led_update_user(led_t led_state) {    // Caps Lock 상태에 따라 0번 LED 제어    
    if (led_state.caps_lock) {
        rgblight_setrgb_at(COLOR_ORANGE, 1); // 0번 LED: 빨강 (Caps Lock ON)
    } else {
        rgblight_setrgb_at(COLOR_OFF, 1); // 0번 LED 끄기 (Caps Lock OFF)
    }    // Scroll Lock 및 Num Lock 상태에 따라 1번 LED 제어    
    if (led_state.scroll_lock || led_state.num_lock) {
        rgblight_setrgb_at(COLOR_RED, 0); // 1번 LED: 노랑 (Scroll Lock 또는 Num Lock ON)    
    } else {        
        rgblight_setrgb_at(COLOR_OFF, 0); // 1번 LED 끄기 (Scroll Lock 및 Num Lock OFF)
    }
    return false; // 기본 동작 유지
}
