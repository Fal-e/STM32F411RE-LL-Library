# Roadmap

This roadmap tracks maintenance priorities for the STM32F411RE low-level library revival. It is intentionally conservative: documentation, buildability, verification, and small safe audits come before driver rewrites.

## Current Baseline

The v0.1.0 baseline is a public maintenance baseline for the existing project. It focuses on making the repository understandable and maintainable:

- MIT license and project status
- README, contributing guide, code of conduct, and GitHub templates
- third-party notices for bundled vendor files
- build/import documentation
- lightweight documentation and metadata CI
- generated artifact cleanup
- examples documentation
- STM32F411RE scope documentation
- release notes and release checklist

## Next Priorities

### Build And Import Verification

- Verify `GPIO_Driver/`, `Tutorial1/`, and `Timers/` import into STM32CubeIDE.
- Verify whether Atollic TrueSTUDIO 9.1.0 can still import and build the projects.
- Record exact toolchain versions, include-path fixes, warnings, and generated outputs.
- Create a command-line build only after at least one IDE build is understood.

### Firmware CI

- Add compile-only CI after a command-line build exists.
- Keep documentation and metadata checks separate from firmware build checks.
- Do not add hardware-dependent CI unless a reliable hardware test setup exists.

### Hardware Verification

- Verify the GPIO blink tutorial on an STM32F411RE board.
- Verify the combined ADC and I2C LCD example with documented wiring.
- Verify LCD 4-bit and I2C helper behavior.
- Measure or review timer/delay assumptions before treating delays as accurate.

### Driver Audits

- Audit GPIO configuration helpers for register safety and clearer API expectations.
- Audit I2C blocking loops, error handling, and timeout behavior.
- Audit LCD helpers for pin assumptions, shared-port side effects, and initialization flow.
- Audit ADC example scaling and conversion-ready handling.
- Audit MPU6050 helper code before documenting it as a working example.

### Source Tree Maintenance

- Keep generated build outputs ignored.
- Avoid de-duplicating CMSIS/ST vendor trees until build/import behavior is verified.
- Decide the long-term home for `stm32_ssbp/` legacy STM32F103/Blue Pill material.
- Clean tutorial-era comments and naming only in small reviewable PRs.

## Not In Scope Yet

- Rewriting the drivers from scratch.
- Removing vendor trees without build proof.
- Claiming hardware behavior that has not been built, flashed, and observed.
- Treating `stm32_ssbp/` as part of the main STM32F411RE library.
