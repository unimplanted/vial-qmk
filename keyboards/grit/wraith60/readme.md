# GritWorks Wraith60 (solder)

60% PCB by GritWorks. Ported to Vial from the vendor firmware
(`GritWorks_Wraith60_solder_vial_20250715.bin`); no vendor source or schematic was available.

* MCU: STM32F103 with stm32duino bootloader (application at 0x08002000)
* Matrix: 9 chained shift registers (bit-banged on A4/A5/A7), one shared sense input on A3 — see `matrix.c`
* Caps Lock LED: A1 (active low)
* Underglow: 12× WS2812 on B7 (TIM4 CH2 PWM), max brightness 180
* Caps Lock tints the underglow cyan without changing the running effect or saved settings

Make example for this keyboard (after setting up your build environment):

    make gritworks/wraith60:vial

Bootloader: hold Esc while plugging in (bootmagic), or use `QK_BOOT`.
