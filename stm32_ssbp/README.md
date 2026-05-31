# Legacy STM32F103/Blue Pill Material

This folder is legacy STM32F103/Blue Pill material. It is not the primary STM32F411RE library target for this repository.

The repository is currently maintained around the STM32F411RE folders:

- `GPIO_Driver/`
- `Tutorial1/`
- `Timers/`

## What This Folder Contains

Current contents include:

- STM32F103 startup and system files in `src/`
- STM32F10x Standard Peripheral Driver files in `Libraries/STM32F10x_StdPeriph_Driver/`
- STM32F10x CMSIS files in `Libraries/CMSIS/`
- Older GPIO and delay helpers in `ssbp_drivers/`
- An STM32F103C8 linker script
- Eclipse/Atollic project metadata

## Maintenance Status

- Kept for history and reference.
- Not part of the default STM32F411RE build/import path.
- Not verified during the current public maintenance revival.
- Should not be treated as STM32F411RE-compatible code without a dedicated migration review.

## Working With This Folder

Only import or build this folder if you are intentionally reviewing the legacy STM32F103/Blue Pill material.

For STM32F411RE work, use the main project folders listed above. Scope details are documented in `../docs/SCOPE.md`.
