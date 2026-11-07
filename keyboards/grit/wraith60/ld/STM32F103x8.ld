/* GritWorks Wraith60 — STM32F103x8 behind the stm32duino bootloader.
 *
 * The wear-leveling EEPROM (embedded flash driver) lives in the last 8 KiB of
 * the 64 KiB flash, i.e. 0x0800E000-0x0800FFFF. The stock stm32duino script
 * lets the application run into that area without complaint, and the first
 * EEPROM write would then erase firmware code. Pretending the flash is 56 KiB
 * shrinks the application region to 0x08002000-0x0800DFFF, so an oversized
 * build fails at link time instead.
 */

f103_flash_size = 56k;
f103_ram_size = 20k;

INCLUDE platforms/chibios/boards/STM32_F103_STM32DUINO/ld/stm32duino_bootloader_common.ld
