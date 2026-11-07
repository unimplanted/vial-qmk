# RAMUNE60 (Vial)

GEONWORKS RAMUNE60 — 제조사 VIA 펌웨어 `ramune60_via_260604R1.uf2` 리버스 엔지니어링 기반 Vial 포팅.

* MCU: RP2040, VID/PID 0xBA02/0x0006
* Matrix 5×15, ROW2COL
  * cols: GP9 GP18 GP19 GP20 GP21 GP22 GP23 GP24 GP25 GP26 GP27 GP28 GP29 GP2 GP3
  * rows: GP16 GP17 GP6 GP5 GP4
* RGB Matrix: WS2812 38개 언더글로우 (GP8, PIO0), per-key LED 없음
* Caps Lock 인디케이터: 마제식·체리식 LED 2개, Caps ON 시 둘 다 점등 (GP7/GP10 sink, GP12 source)

부트로더 진입: Esc(0,0) 누른 채 연결 (Bootmagic), RESET 더블탭, 또는 Fn 레이어의 QK_BOOT.

    make geonworks/ramune60:vial
