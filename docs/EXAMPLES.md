# Examples

This document describes the examples and example-style helper code currently in the STM32F411RE portions of the repository. It is based on the checked-in source files only. Hardware wiring, build import, flashing, and runtime behavior still need verification on real hardware unless noted otherwise.

The legacy `stm32_ssbp/` STM32F103/Blue Pill material is not covered here. It will be handled by the separate scope-audit work.

## Quick Index

| Area | Main files | Status |
| --- | --- | --- |
| GPIO blink tutorial | `Tutorial1/User Application/main.c` | Present, simple direct-register example |
| Combined GPIO, I2C LCD, and ADC example | `GPIO_Driver/User Application/main.c` | Present, needs hardware verification |
| Timer/delay helper | `GPIO_Driver/User Library/Timer_Delay.c` | Present, used by LCD/delay examples |
| I2C helper | `GPIO_Driver/User Library/I2C_Library.c` | Present, used by LCD I2C helper |
| LCD 4-bit helper | `GPIO_Driver/User Library/lcd_4bit.c` | Present |
| LCD 8-bit helper | `GPIO_Driver/User Library/lcd_8bit.c` | Source is currently commented out |
| LCD I2C helper | `GPIO_Driver/User Library/lcd_i2c.c` | Present, hard-coded address |
| Timer project | `Timers/src/main.c` | Stub only |

## GPIO Blink Tutorial

Purpose:

- Demonstrates direct register-level GPIO setup without the custom GPIO helper.
- Enables GPIOA, configures PA5 as an output, and toggles PA5 in a busy-loop delay.

Main files:

- `Tutorial1/User Application/main.c`
- `Tutorial1/User Application/system_stm32f4xx.c`
- `Tutorial1/User Application/startup_stm32f411xe.s`
- `Tutorial1/stm32_flash.ld`

Required hardware:

- STM32F411RE-based board.
- LED connected to PA5. On many Nucleo-style boards PA5 is the onboard LED, but this needs verification for the exact board.

Wiring:

| Signal | STM32 pin | Notes |
| --- | --- | --- |
| LED output | PA5 | Board LED assumption needs verification |

Expected behavior:

- PA5 toggles on and off with a software delay loop.

Clock and peripheral assumptions:

- Uses the default startup/system clock setup from the checked-in project files.
- Enables GPIOA through `RCC->AHB1ENR`.
- Does not use interrupts or timers.

Known limitations:

- The delay is a compiler-dependent busy loop.
- The PA5 LED assumption needs board-level verification.
- The current source contains tutorial-era comments and has not been cleaned up in this PR.

## Combined GPIO, I2C LCD, and ADC Example

Purpose:

- Shows custom GPIO helper usage.
- Configures PC0 as an analog input.
- Configures PA5 as an output.
- Enables I2C1 on PB6/PB7.
- Reads ADC1 and writes a voltage string to an I2C character LCD.

Main files:

- `GPIO_Driver/User Application/main.c`
- `GPIO_Driver/User Library/GPIO_Driver.c`
- `GPIO_Driver/User Library/GPIO_Driver.h`
- `GPIO_Driver/User Library/I2C_Library.c`
- `GPIO_Driver/User Library/I2C_Library.h`
- `GPIO_Driver/User Library/lcd_i2c.c`
- `GPIO_Driver/User Library/lcd_i2c.h`
- `GPIO_Driver/User Library/Timer_Delay.c`
- `GPIO_Driver/User Library/Timer_Delay.h`
- `GPIO_Driver/User Application/system_stm32f4xx.c`
- `GPIO_Driver/User Application/startup_stm32f411xe.s`
- `GPIO_Driver/stm32_flash.ld`

Required hardware:

- STM32F411RE-based board.
- Potentiometer or analog voltage source for PC0.
- 16x2 HD44780-compatible LCD with an I2C backpack.
- Pull-up resistors for I2C if they are not already present on the LCD backpack or board.
- Common ground between the board and external modules.

Wiring:

| Signal | STM32 pin | Notes |
| --- | --- | --- |
| Analog input | PC0 | Code configures PC0 as analog and selects ADC1 channel 10; verify against board pinout |
| I2C1 SCL | PB6 | Configured as alternate function AF4 |
| I2C1 SDA | PB7 | Configured as alternate function AF4 |
| LED output | PA5 | Configured as output, but current loop does not toggle it |
| LCD power | Needs verification | Match LCD backpack voltage requirements |
| LCD ground | GND | Common ground required |

Expected behavior:

- The code repeatedly reads `ADC1->DR`, formats the result as a voltage-like value, prints `Voltage: <value>V` to the LCD, waits about one second, and clears the LCD.

Clock and peripheral assumptions:

- `config_clock_50MHz()` is called before I2C setup.
- `I2C_enable()` assumes a 50 MHz APB clock while configuring I2C1 standard mode timing.
- I2C1 uses PB6/PB7 with alternate function AF4.
- LCD I2C address is hard-coded as `0x27` in `lcd_i2c.c`.
- ADC1 is enabled directly through registers and runs in continuous conversion mode.

Known limitations:

- Hardware behavior has not been verified during the revival work.
- The current `main.c` does not call `lcd_i2c_init()` before printing.
- LCD backpack address `0x27` may not match every module.
- The ADC scaling expression is example code and needs review before being treated as calibrated measurement code.
- The ADC loop does not document reference voltage, input range, or source impedance assumptions.
- I2C error handling and timeout behavior need audit before relying on the example in a larger application.

## Timer and Delay Helper

Purpose:

- Provides `config_clock_50MHz()` and `delay_mS()` for examples that need millisecond-style delays.
- Configures TIM4 update interrupts for the delay counter.

Main files:

- `GPIO_Driver/User Library/Timer_Delay.c`
- `GPIO_Driver/User Library/Timer_Delay.h`
- Used by the LCD helpers and the combined example.

Required hardware:

- STM32F411RE-based board.
- No external hardware is required for the helper itself.

Wiring:

- None for the timer helper itself.

Expected behavior:

- `config_clock_50MHz()` configures the system clock helper path used by these examples and enables TIM4 interrupts.
- `delay_mS(ms)` starts TIM4, waits until the interrupt counter reaches `ms`, and stops TIM4.

Clock and peripheral assumptions:

- Uses HSI and PLL register configuration in `config_clock_50MHz()`.
- Uses TIM4 and `TIM4_IRQHandler()`.
- Assumes the project vector table/startup file provides the TIM4 interrupt entry.

Known limitations:

- Timing has not been measured on hardware during the revival work.
- The helper changes clock tree registers and should be reviewed carefully before reuse outside these examples.
- Delay accuracy depends on the clock configuration and interrupt behavior.

## LCD 4-Bit Parallel Helper

Purpose:

- Provides helper functions for a 16x2 character LCD in 4-bit parallel mode.

Main files:

- `GPIO_Driver/User Library/lcd_4bit.c`
- `GPIO_Driver/User Library/lcd_4bit.h`
- `GPIO_Driver/User Library/GPIO_Driver.c`
- `GPIO_Driver/User Library/Timer_Delay.c`

Required hardware:

- STM32F411RE-based board.
- HD44780-compatible 16x2 LCD wired in 4-bit mode.
- Suitable contrast circuit and power wiring for the LCD.

Wiring from current header definitions:

| LCD signal | STM32 pin |
| --- | --- |
| D4 | PA4 |
| D5 | PA5 |
| D6 | PA6 |
| D7 | PA7 |
| EN | PB10 |
| RS | PB3 |
| RW | PB4 |

Expected behavior:

- `lcd_init()` configures the data and control pins and initializes the LCD in 4-bit mode.
- `lcd_print()`, `lcd_clear()`, and `lcd_goto_xy()` provide basic 16x2 text output helpers.

Clock and peripheral assumptions:

- Requires GPIOA and GPIOB access through the custom GPIO helper.
- Uses `delay_mS()`, so `config_clock_50MHz()` should be called before using LCD delays.

Known limitations:

- The data pins must be on one port and the control pins must be on one port with the current implementation.
- `lcd_goto_xy()` is written for 16x2 layout.
- The helper clears the full data port mask in places; review is needed before sharing GPIOA with other hardware.
- Wiring has not been verified during the revival work.

## LCD 8-Bit Parallel Helper

Purpose:

- Contains an older 8-bit parallel LCD helper implementation.

Main files:

- `GPIO_Driver/User Library/lcd_8bit.c`
- `GPIO_Driver/User Library/lcd_8bit.h`

Required hardware:

- STM32F411RE-based board.
- HD44780-compatible LCD wired in 8-bit mode.

Wiring from current header definitions:

| LCD signal | STM32 pin |
| --- | --- |
| D0 | PA0 |
| D1 | PA1 |
| D2 | PA8 |
| D3 | PA9 |
| D4 | PA4 |
| D5 | PA5 |
| D6 | PA6 |
| D7 | PA7 |
| EN | PB10 |
| RS | PB3 |
| RW | PB4 |

Expected behavior:

- Needs verification. The implementation in `lcd_8bit.c` is currently commented out to avoid duplicate symbol definitions with the 4-bit helper.

Clock and peripheral assumptions:

- Same GPIO and delay assumptions as the 4-bit helper if the code is re-enabled.

Known limitations:

- Not active in the current build as checked in.
- Should not be treated as a working example until it is separated from the 4-bit helper or given unique function names.

## LCD I2C Helper

Purpose:

- Sends HD44780-style LCD commands and data through an I2C backpack.

Main files:

- `GPIO_Driver/User Library/lcd_i2c.c`
- `GPIO_Driver/User Library/lcd_i2c.h`
- `GPIO_Driver/User Library/I2C_Library.c`
- `GPIO_Driver/User Library/Timer_Delay.c`

Required hardware:

- STM32F411RE-based board.
- HD44780-compatible 16x2 LCD with an I2C backpack.
- I2C pull-ups if not already present.

Wiring:

| Signal | STM32 pin | Notes |
| --- | --- | --- |
| SCL | PB6 | I2C1 SCL, AF4 |
| SDA | PB7 | I2C1 SDA, AF4 |
| LCD backpack address | `0x27` | Hard-coded; needs verification per module |

Expected behavior:

- `lcd_i2c_init()` initializes the display.
- `lcd_i2c_print()`, `lcd_i2c_clear()`, and `lcd_i2c_goto_xy()` provide basic 16x2 text output helpers.

Clock and peripheral assumptions:

- Requires `config_clock_50MHz()` and `I2C_enable()` before LCD I2C operations.
- I2C timing is configured for standard mode with a 50 MHz APB assumption.

Known limitations:

- Address and backpack bit mapping are hard-coded.
- `lcd_i2c_goto_xy()` is written for 16x2 layout.
- No timeout is documented for failed I2C transfers.
- Hardware behavior has not been verified during the revival work.

## I2C Helper and Scanner

Purpose:

- Provides direct-register helper functions for I2C1 start, stop, address, write, read, and a basic scan routine.

Main files:

- `GPIO_Driver/User Library/I2C_Library.c`
- `GPIO_Driver/User Library/I2C_Library.h`

Required hardware:

- STM32F411RE-based board.
- I2C device connected to PB6/PB7.
- Pull-up resistors as required by the I2C bus.

Wiring:

| Signal | STM32 pin |
| --- | --- |
| I2C1 SCL | PB6 |
| I2C1 SDA | PB7 |

Expected behavior:

- The helper is intended to configure I2C1 and provide blocking register-level transfers.
- `I2C_scan()` is present but marked by source comments as incomplete.

Clock and peripheral assumptions:

- `I2C_enable()` assumes `config_clock_50MHz()` was called first.
- Uses I2C1 and AF4 on PB6/PB7.

Known limitations:

- `I2C_scan()` is not a complete scanner.
- Blocking loops do not document timeout behavior.
- Error handling needs review before use outside examples.

## Timer Project Stub

Purpose:

- Placeholder project for timer-related work.

Main files:

- `Timers/src/main.c`
- `Timers/User Library/GPIO_Driver.c`
- `Timers/User Library/GPIO_Driver.h`
- `Timers/src/system_stm32f4xx.c`
- `Timers/src/startup_stm32f411xe.s`
- `Timers/stm32_flash.ld`

Required hardware:

- STM32F411RE-based board.

Wiring:

- None documented in the current `main.c`.

Expected behavior:

- No timer behavior is currently demonstrated. The `main.c` file is an empty stub.

Clock and peripheral assumptions:

- Uses the checked-in STM32F411RE project startup/system files.
- Includes `stm32f4xx.h` and `GPIO_Driver.h`.

Known limitations:

- Needs a real timer example or should be documented as a placeholder until one is added.
- No hardware-facing behavior should be inferred from the current stub.

## Verification Status

What was checked for this documentation pass:

- Source files and headers listed above were inspected.
- Wiring tables were derived from current macros and comments.
- No source code, project metadata, vendor files, or hardware-facing behavior was changed.

What still needs manual verification:

- Import and build in STM32CubeIDE or TrueSTUDIO.
- Flashing each example to an STM32F411RE board.
- Actual GPIO, ADC, I2C, LCD, and timer behavior.
- Exact board pinout, LCD backpack address, and external wiring.
