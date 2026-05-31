# Contributing

Thanks for helping revive `STM32F411RE-LL-Library`.

This is an older bare-metal STM32F411RE project being brought back into public maintenance. The project currently prioritizes documentation, buildability, examples, maintainability, and careful review of hardware-facing code.

## Maintenance Workflow

Use this workflow for repository maintenance:

```text
one issue -> one branch -> one PR -> review -> merge -> changelog note
```

Each change should be tied to one GitHub issue and kept small enough to review comfortably. After review is complete and required checks or verification notes are in place, the PR can be merged.

## Good First Contributions

Good early contributions include:

- Documentation fixes
- Build or import instructions
- Example wiring notes
- Repository hygiene
- Compile-only checks
- Hardware behavior audits
- Small, well-explained driver fixes

Avoid broad rewrites or hardware behavior changes unless the change is clearly scoped, tested, and explained.

## Branches

Use a short branch name that describes the issue being handled.

Examples:

```text
docs/readme-overview
docs/examples-wiring
ci/compile-check
cleanup/gitignore
```

## Pull Requests

Every PR should include:

- Summary of the change
- Why it matters
- Files changed
- Verification performed
- Hardware tested, if any
- Known limitations or follow-up work
- Maintainer checklist
- Changelog note plan, if the PR changes project-facing behavior or documentation

Describe only what is present, built, or tested.

## Hardware-Facing Changes

For changes that affect peripheral behavior, clock setup, pin configuration, timing, I2C, LCD, ADC, MPU6050, or other hardware interactions, include:

- Board or microcontroller used
- Toolchain or IDE used
- Exact wiring
- Firmware built or flashed
- Observed behavior
- Any risks, assumptions, or unverified cases

If the change was reviewed but not tested on hardware, say that directly.

## Coding Notes

- Prefer small, readable C changes over large rewrites.
- Preserve existing behavior unless the PR explicitly explains why behavior changes.
- Keep register-level changes easy to audit.
- Prefer named constants and clear comments when they reduce hardware ambiguity.
- Do not reformat unrelated files in the same PR.

## Documentation Notes

When documenting examples or hardware requirements:

- Document what is present in the repository.
- Mark unclear wiring, clock, address, or board assumptions as `needs verification`.
- Avoid inventing features or examples.
- Keep limitations visible instead of hiding them.

## Code of Conduct

Please follow the repository [Code of Conduct](CODE_OF_CONDUCT.md).
