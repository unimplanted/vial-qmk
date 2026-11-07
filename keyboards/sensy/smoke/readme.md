# Sensy Smoke (Vial)

65% 키보드. 제조사 Vial 펌웨어(`sensy_smoke_vial1.bin`)를 리버스 엔지니어링해서 포팅함.

* MCU: STM32F072CB (Cortex-M0, 128KB flash) — 부트로더: STM32 내장 DFU
* 매트릭스: 5 × 17, COL2ROW
* Caps Lock LED: B9 (active-low)
* VID/PID: 0x6666 / 0x0888

    make sensy/smoke:vial

부트로더 진입: Esc를 누른 채 USB 연결(Bootmagic), 또는 Fn + `\` (QK_BOOT), 또는 PCB 리셋/BOOT 버튼.
