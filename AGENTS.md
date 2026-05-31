# Maintainer Guidance

This repository is an STM32F411RE bare-metal C project. Keep maintenance work small, easy to review, and careful around hardware-facing behavior.

## Maintenance Workflow

Use this workflow for repository maintenance:

```text
one issue -> one branch -> one PR -> review -> merge -> changelog note
```

Each change should be tied to one GitHub issue. Keep PRs focused on one topic and avoid bundling unrelated cleanup with source, build, or documentation changes.

## Project Voice

Write public-facing text as the project maintainer. Keep it direct, factual, and human. State the current project status naturally and put verification caveats where they help users make good hardware decisions.

## Embedded C Review Rules

Review hardware-facing changes with extra care when they touch:

- RCC and clock setup
- GPIO modes, pulls, speeds, alternate functions, and EXTI
- I2C timing, start/stop handling, ACK/NACK behavior, and bus recovery
- Timer configuration and delay calculations
- ADC configuration, sampling, conversion order, and reference-voltage assumptions
- LCD 4-bit, 8-bit, and I2C helpers
- MPU6050 register access, scaling, and I2C transactions
- Startup files, linker scripts, CMSIS/ST headers, or interrupt vectors

Do not rewrite driver behavior as part of a documentation, hygiene, or template PR. If a behavior change is needed, keep it isolated and explain the register-level effect.

## Build And Test Expectations

Every PR should say exactly what was checked.

For documentation-only changes, note that no source, build, or hardware behavior changed.

For build/import changes, include:

- Toolchain or IDE name and version
- Project folder imported or command executed
- Target microcontroller define
- Build result
- Any warnings or errors left unresolved

For hardware-facing changes, include:

- Board or STM32F411RE hardware used
- Wiring and connected modules
- Toolchain or IDE used
- Firmware built or flashed
- Expected behavior
- Observed behavior
- Any measurements, serial output, debugger output, or screenshots that support the result

Do not state that hardware was tested unless it was actually tested on hardware.

## Documentation Expectations

Documentation should describe what is in the repository now. If wiring, toolchain behavior, clock configuration, LCD address, board assumptions, or example behavior is uncertain, mark it as `needs verification`.

Do not invent examples, supported boards, successful builds, test coverage, or hardware results. Planned work belongs in the roadmap or follow-up issues.

## Vendor And Generated Files

CMSIS, ST, IDE-generated, and legacy vendor files should be handled conservatively.

- Do not edit vendor code for style cleanup.
- Do not de-duplicate vendor trees unless the build has been verified after the change.
- Do not delete generated/debug/build artifacts unless they are clearly generated and the cleanup is scoped to repository hygiene.
- Keep third-party notices up to date when bundled vendor material changes.

## Pull Request Checklist

Before merge, confirm:

- The PR is tied to one issue.
- The scope is small and reviewable.
- The PR description lists files changed, verification performed, risk level, known limitations, maintainer checklist, and release-note impact.
- Hardware-facing changes include board, wiring, toolchain, expected behavior, and observed behavior.
- Unverified hardware behavior is marked clearly.
- The changelog is updated in a separate follow-up PR when needed.
