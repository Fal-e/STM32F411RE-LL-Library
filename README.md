# STM32F411RE-LL-Library

Bare-metal low-level peripheral library and examples for the STM32F411RE microcontroller.

## Project Status

This is an older STM32F411RE bare-metal project being revived for public open-source maintenance. Current work is focused on documentation, buildability, examples, maintainability, and careful review of existing hardware-facing code.

No claims are made about production use, active users, downloads, or adoption.

## Supported Target

- Microcontroller: STM32F411RE
- Board: STM32F411RE-based development board
- Board-level assumptions: needs verification. Some examples use pins commonly associated with STM32 Nucleo-style boards, such as PA5 for an onboard LED.

## Current Library Contents

The main custom library files are in `GPIO_Driver/User Library/`.

- GPIO configuration, pin write, port write, and EXTI helper functions
- I2C1 helper functions
- Timer-based delay and 50 MHz clock setup helper
- LCD helpers for 4-bit, 8-bit, and I2C-connected character LCDs
- MPU6050 helper code: present, needs verification
- ADC usage example in `GPIO_Driver/User Application/main.c`

## Hardware Requirements

Hardware depends on the example being used.

- STM32F411RE-based board
- ST-LINK or compatible programmer/debugger: needs verification
- Potentiometer for the ADC example
- 16x02 character LCD with I2C backpack for the LCD I2C example
- Jumper wires and suitable power connections

Example wiring currently documented in the source:

- Potentiometer output to PC0
- I2C SCL to PB6
- I2C SDA to PB7
- LCD I2C address appears hard-coded as `0x27`: needs verification for your LCD module

## Folder Structure

```text
GPIO_Driver/
  User Library/        Custom GPIO, I2C, timer/delay, LCD, and MPU6050 code
  User Application/    Main STM32F411RE example using GPIO, I2C, ADC, and LCD
  Drivers/             Bundled CMSIS/ST files
  Debug/               Generated build outputs currently tracked; cleanup planned

Tutorial1/
  User Application/    Simple GPIO tutorial example
  Drivers/             Bundled CMSIS/ST files
  Debug/               Generated build outputs currently tracked; cleanup planned

Timers/
  User Library/        GPIO driver copy used by the timer project
  src/                 Timer project source; current main is a stub
  Drivers/             Bundled CMSIS/ST files
  Debug/               Generated build outputs currently tracked; cleanup planned

stm32_ssbp/
  Legacy STM32F103/Blue Pill material; scope needs review
```

## Getting Started

1. Clone the repository.
2. Open the project folder for the example you want to inspect, usually `GPIO_Driver`.
3. Review the source under `User Library` and `User Application`.
4. Verify board wiring and power before flashing any firmware.

## Build and Import Status

The repository currently contains Eclipse/Atollic TrueSTUDIO project files such as `.project`, `.cproject`, and `.elf.launch`.

Known from the current repository:

- Project files reference STM32F411RE and the `STM32F411xE` define.
- Linker scripts are present as `stm32_flash.ld`.
- Startup files are present for STM32F411RE examples.

Needs verification:

- Importing the existing projects into STM32CubeIDE.
- Building with Atollic TrueSTUDIO 9.1.0 or a compatible Eclipse-based setup.
- Building with `arm-none-eabi-gcc` from the command line.

A reproducible command-line build system is planned but is not yet present.

## Example Summary

### `GPIO_Driver/User Application/main.c`

Demonstrates:

- Configuring the clock helper to 50 MHz
- Configuring PC0 as analog input
- Configuring PA5 as output
- Enabling I2C1 on PB6/PB7
- Reading ADC1 and printing a voltage value to an I2C LCD

Required hardware:

- STM32F411RE-based board
- Potentiometer connected to PC0
- 16x02 LCD with I2C backpack connected to PB6/PB7

Known limitations:

- LCD I2C address is hard-coded in the LCD helper.
- Wiring and LCD backpack address need verification on real hardware.
- Build has not yet been verified as part of the revival work.

### `Tutorial1/User Application/main.c`

Demonstrates direct register-level GPIO setup and LED blinking on PA5.

Known limitations:

- Delay is a busy loop.
- Board assumption for PA5 LED needs verification.
- Source comments contain tutorial-era wording that may need cleanup.

### `Timers/src/main.c`

Currently a stub main file that includes STM32F4 and GPIO headers.

Known limitations:

- Example purpose needs verification.
- Timer behavior is not demonstrated in the current `main.c`.

## Limitations

- The repository still contains generated IDE/build artifacts.
- CMSIS/ST vendor files are duplicated across project folders.
- Command-line build support is not yet available.
- STM32F103/Blue Pill material exists in `stm32_ssbp/` and needs scope review.
- Hardware behavior has not yet been fully audited during the revival.
- Some comments, names, and examples reflect the original older project state.

## Roadmap

- Document third-party notices for bundled CMSIS/ST files.
- Add or document a reliable build/import path.
- Add compile-only CI once a command-line build exists.
- Clean generated IDE metadata and build outputs from source control.
- Improve example documentation and wiring notes.
- Clarify legacy/out-of-scope material.
- Audit GPIO, I2C, timer, LCD, ADC, and MPU6050 code before behavior changes.

## Contributing

This repository is being revived with small, reviewable changes.

See [CONTRIBUTING.md](CONTRIBUTING.md) for the full contribution workflow and [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) for participation expectations.

Preferred workflow:

```text
one issue -> one branch -> one PR -> Codex review -> fix -> merge -> changelog note
```

For hardware-facing changes, include:

- What hardware was used
- What was built or flashed
- What behavior was observed
- Any risks or assumptions

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE).

Bundled vendor files retain their own notices. See [THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md).
