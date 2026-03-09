/* SPDX-License-Identifier: GPL-2.0-or-later */
 
#pragma once
 
/* 
 * Vial UID - 고유 식별자
 * 터미널에서 생성: python3 -c 'import os; print("".join(f"0x{b:02X}, " for b in os.urandom(8)))'
 * 아래 값은 예시이므로 반드시 새로 생성하세요!
 */
#define VIAL_KEYBOARD_UID {0x3F, 0x8A, 0x2C, 0x15, 0x9B, 0x47, 0xE1, 0x6D}
 
/*
 * Vial 보안 언락 조합
 * ESC (0,0) + tab (0,1) 동시 누름
 */
#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 1 }
 
/*
 * 다이나믹 키맵 레이어 수
 * 최대 4개 레이어 (0~3)
 */
#define DYNAMIC_KEYMAP_LAYER_COUNT 4
 
/*
 * Tap Dance 엔트리 (선택사항)
 * VIAL_ENABLE이 yes면 기본 지원
 */
#define VIAL_TAP_DANCE_ENTRIES 8
 
/*
 * Combo 엔트리 (선택사항)
 */
#define VIAL_COMBO_ENTRIES 8
 
/*
 * Key Override 엔트리 (선택사항)
 */
#define VIAL_KEY_OVERRIDE_ENTRIES 8
