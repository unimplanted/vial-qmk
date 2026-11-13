# Gehirn60

60% solderable PCB (HHKB / WKL, split backspace, ISO, split shifts, 6U/6.25U/7U bottom row).

* Keyboard Maintainer: [unimplanted](https://github.com/unimplanted)
* Hardware Supported: Gehirn60 (STM32F411CE, 8 MHz HSE)

Pin mapping, diode direction and USB IDs were recovered from the factory VIA firmware.
Caps Lock indicator: THT LED on the Caps Lock position, driven by B1 (active high).

Make example for this keyboard (after setting up your build environment):

    make bionlenja/gehirn60:vial

Flashing example for this keyboard:

    make bionlenja/gehirn60:vial:flash

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Esc) and plug in the keyboard
* **Physical reset button**: Hold BOOT0 / press the reset button on the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` (Fn + Esc in the default keymap)
