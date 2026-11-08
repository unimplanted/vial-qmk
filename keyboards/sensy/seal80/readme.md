# Eason Seal.80 (MX)

TKL (80%) PCB by Eason. Port reverse-engineered from the stock Vial firmware
(`eason1_seal80_vial.bin`, MX version).

* MCU: STM32F072 (ChibiOS, app at 0x08000000, no custom bootloader)
* Bootloader: STM32 ROM DFU (system memory 0x1FFFC800)
* Matrix: 7 x 14, ROW2COL
* Indicators: Caps Lock B4, Scroll Lock B3 (active high)

Make example:

    make eason1/seal80:vial

Flashing: hold Esc (0,0) while plugging in (Bootmagic), or use `QK_BOOT`,
then flash with `qmk flash` / dfu-util.
