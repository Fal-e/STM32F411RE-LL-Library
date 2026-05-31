# Build And Import Notes

This repository currently uses Eclipse/Atollic-style project metadata. A verified command-line build system is not present yet, so the safest current path is to import the existing projects into an Eclipse-based STM32 IDE and verify the build there.

No source, linker, startup, or project metadata changes are made by this document.

## Project Folders

| Folder | Target in project metadata | Main status |
| --- | --- | --- |
| `GPIO_Driver/` | `STM32F411RE`, define `STM32F411xE` | Main STM32F411RE example and custom user libraries |
| `Tutorial1/` | `STM32F411RE`, define `STM32F411xE` | Simple STM32F411RE GPIO tutorial example |
| `Timers/` | `STM32F411RE`, define `STM32F411xE` | STM32F411RE timer project; current main file is a stub |
| `stm32_ssbp/` | `STM32F103C8`, define `STM32F10X_MD` | Legacy STM32F103/Blue Pill material; outside the main STM32F411RE scope |

The STM32F411RE project folders contain:

- `.project` and `.cproject` Eclipse project files
- `stm32_flash.ld` linker script
- `startup_stm32f411xe.s` startup file
- `system_stm32f4xx.c`
- bundled CMSIS/ST headers

The `.cproject` files identify the original toolchain family as Atollic ARM Tools. Some metadata references `TrueSTUDIO for STM32 9.1.0`.

## STM32CubeIDE Import Path

These steps are intended for verification. They still need to be tested on a clean STM32CubeIDE install.

1. Clone the repository.
2. Open STM32CubeIDE and choose a workspace outside the repository.
3. Use `File -> Import -> General -> Existing Projects into Workspace`.
4. Select the repository root, or select one project folder at a time.
5. Import the STM32F411RE projects:
   - `GPIO_Driver`
   - `Tutorial1`
   - `Timers`
6. Leave `stm32_ssbp` out unless you are intentionally reviewing the legacy STM32F103 material.
7. If STM32CubeIDE prompts to migrate project metadata, review the changes before accepting them.
8. Open project properties and check:
   - target MCU is `STM32F411RE`
   - preprocessor symbol includes `STM32F411xE`
   - FPU setting matches FPv4-SP-D16 with hard-float ABI
   - linker script points to `../stm32_flash.ld`
   - include paths resolve to the local project folders
9. Build the `Debug` configuration first.
10. Confirm whether the IDE produces a fresh `Debug/<project>.elf`, `.map`, and `.list`.

Important: older revisions contained generated `Debug/` outputs. Those outputs are ignored now; a fresh IDE build should recreate them locally.

## TrueSTUDIO Import Path

The checked-in project metadata appears to come from Atollic TrueSTUDIO for STM32 9.1.0.

These steps still need verification on a machine with TrueSTUDIO installed.

1. Open TrueSTUDIO.
2. Use `File -> Import -> General -> Existing Projects into Workspace`.
3. Select the repository root or an individual project folder.
4. Import `GPIO_Driver`, `Tutorial1`, or `Timers`.
5. Check that the ARM tools path is valid for your installation.
6. Check that the target is `STM32F411RE` and the define is `STM32F411xE`.
7. Check include paths for old absolute paths and replace them with workspace-relative paths if needed.
8. Build the `Debug` configuration.
9. Record warnings, errors, and generated artifact paths.

## Known Import Issues To Check

The current project metadata may contain old machine-specific paths. In particular, review include paths that reference an old `C:\Users\Falcon\Atollic\TrueSTUDIO\...` workspace.

If include paths are unresolved, prefer workspace-relative paths such as:

```text
${workspace_loc:/GPIO_Driver/User Library}
${workspace_loc:/Timers/User Library}
```

Also verify that CMSIS include paths point to the local project tree:

```text
../Drivers/CMSIS/Include
../Drivers/CMSIS/Device/ST/STM32F4xx/Include
```

## Command-Line Build Status

A root Makefile or CMake project is intentionally not added yet.

Reasons:

- No `Makefile`, generated makefile, or CMake setup is currently checked in.
- `arm-none-eabi-gcc` was not available in the local PATH during this documentation pass.
- The current `.cproject` files include IDE-managed settings and some old absolute include paths.
- The repository duplicates CMSIS/ST vendor trees across project folders.

Adding a command-line build should be a separate PR after at least one STM32F411RE project imports and builds successfully in an IDE.

A future command-line build will need to confirm:

- exact compiler version
- Cortex-M4, Thumb, FPU, and float ABI flags
- `STM32F411xE` define
- include directory list
- source file list for each project
- `startup_stm32f411xe.s`
- `stm32_flash.ld`
- linker flags and runtime library assumptions

## Manual Verification Checklist

When verifying a build/import flow, record:

- operating system
- IDE or toolchain version
- project folder imported
- configuration built, usually `Debug`
- target MCU and preprocessor symbols
- include-path fixes made, if any
- build result
- warnings or errors
- whether firmware was flashed
- board and wiring, if hardware was used
- observed hardware behavior, if hardware was used

Do not state that hardware was tested unless firmware was actually flashed and observed on hardware.
