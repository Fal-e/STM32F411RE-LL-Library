# Project Scope

This repository is maintained as an STM32F411RE bare-metal low-level library and examples project.

The current tree also contains older STM32F103/Blue Pill material. That material is kept for history and reference, but it is not part of the primary STM32F411RE maintenance scope.

## Primary Scope

The primary maintained target is:

- Microcontroller: STM32F411RE
- Project style: bare-metal C using register-level code and bundled CMSIS/ST headers
- Current import/build style: Eclipse/Atollic project metadata, with STM32CubeIDE import still needing verification

Primary STM32F411RE project folders:

| Folder | Current role |
| --- | --- |
| `GPIO_Driver/` | Main STM32F411RE example and custom GPIO, I2C, timer/delay, LCD, ADC, and MPU6050-related files |
| `Tutorial1/` | Simple STM32F411RE GPIO register tutorial |
| `Timers/` | STM32F411RE timer project folder; current `main.c` is a stub |

These folders contain STM32F4 startup/system files, STM32F411RE linker scripts, and project metadata documented in `docs/BUILDING.md`.

## Legacy STM32F103 Material

The `stm32_ssbp/` folder is legacy STM32F103/Blue Pill material.

Evidence from the current tree:

- `stm32_ssbp/stm32_flash.ld` identifies an STM32F103C8 target.
- `stm32_ssbp/src/startup_stm32f10x_md.s` is an STM32F10x startup file.
- `stm32_ssbp/src/system_stm32f10x.c` and `stm32_ssbp/src/stm32f10x_conf.h` are STM32F10x files.
- `stm32_ssbp/Libraries/STM32F10x_StdPeriph_Driver/` contains the STM32F10x Standard Peripheral Driver.
- `stm32_ssbp/ssbp_drivers/ss_gpio.h` includes a Blue Pill-specific note.
- The build/import notes identify this folder as `STM32F103C8` with `STM32F10X_MD`.

This folder is not deleted in this PR because removing or restructuring legacy embedded source should wait until import/build behavior and history impact are understood.

## Maintenance Rules

- Treat STM32F411RE work as the default repository scope.
- Do not mix STM32F103 code into STM32F411RE examples without a separate review and clear migration plan.
- Do not claim STM32F103/Blue Pill behavior is supported or verified unless it is actually built, flashed, and tested.
- Keep changes to `stm32_ssbp/` documentation-only until a dedicated legacy cleanup decision is made.
- If the legacy folder is kept long term, document its build/import path separately from the STM32F411RE projects.

## Current Verification Status

Verified in this documentation pass:

- The project folders and target families were identified from current filenames, linker scripts, source files, and existing build/import documentation.
- No source code, vendor files, project metadata, linker scripts, startup files, or hardware-facing behavior were changed.

Still needs verification:

- STM32F411RE project import/build in STM32CubeIDE or TrueSTUDIO.
- STM32F411RE hardware behavior.
- Whether `stm32_ssbp/` should remain as legacy reference material, move to an archive folder, or be removed in a future major cleanup.
- Any STM32F103/Blue Pill build or hardware behavior.
