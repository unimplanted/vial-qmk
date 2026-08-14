// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * USB VID/PID, 제조사/제품명, 버전, diode_direction, matrix_pins,
 * matrix size, caps lock indicator, debounce 는 모두 keyboard.json으로 이전됨.
 *
 * 참고: V1 热拔插(핫스왑) 배선은 아래와 같음 — 필요 시 keyboard.json의
 * matrix_pins를 이 값으로 교체:
 *   cols: B2, B10, B11, A15, B3, B4, B5, B6, B8, B9, A3, A4, A5, A6
 *   rows: A2, A1, A0, B7, B0
 */

#define TAP_CODE_DELAY 15
