# VIA/Vial 활성화
VIA_ENABLE = yes
VIAL_ENABLE = yes
 
# 링크 타임 최적화 (펌웨어 크기 줄이기)
LTO_ENABLE = yes
 
# RGB 조명 활성화
RGBLIGHT_ENABLE = yes
 
# STM32F103은 플래시가 작으므로 최적화 필요
# 불필요한 기능 비활성화
 
# QMK Settings (Vial에서 불필요)
QMK_SETTINGS = no
 
# 기본 기능들
MOUSEKEY_ENABLE = yes        # 마우스 키 필요시 yes
EXTRAKEY_ENABLE = yes        # 미디어 키 필요시 yes
CONSOLE_ENABLE = no          # 디버그 콘솔
COMMAND_ENABLE = no          # 디버그 명령어
 
# 고급 기능 (필요시 활성화)
TAP_DANCE_ENABLE = no        # Tap Dance
COMBO_ENABLE = no            # Combo
KEY_OVERRIDE_ENABLE = no     # Key Override
LEADER_ENABLE = no           # Leader Key
AUTO_SHIFT_ENABLE = no       # Auto Shift
 
# 공간 절약
MAGIC_ENABLE = no
GRAVE_ESC_ENABLE = no
SPACE_CADET_ENABLE = no
 
# 선택적: 더 많은 공간 필요시
# MOUSEKEY_ENABLE = no
# EXTRAKEY_ENABLE = no
