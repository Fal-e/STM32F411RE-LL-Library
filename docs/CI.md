# Continuous Integration

This repository uses a lightweight GitHub Actions workflow for repository documentation and metadata checks.

The workflow is intentionally conservative. Firmware compile checks will be added after the STM32F411RE build/import path is verified.

## Current Workflow

Workflow file:

```text
.github/workflows/repo-checks.yml
```

The workflow runs on:

- pull requests
- pushes to `Development`
- manual `workflow_dispatch`

Current checks:

- required maintenance files exist
- maintained Markdown/YAML files do not contain trailing whitespace
- maintained docs/config files do not contain merge-conflict markers
- README links to build/import and CI documentation

## What CI Does Not Check Yet

The current workflow does not:

- compile firmware
- import projects into STM32CubeIDE or TrueSTUDIO
- flash hardware
- validate wiring
- validate clock, GPIO, I2C, LCD, ADC, timer, or MPU6050 behavior
- clean generated `Debug/` artifacts
- validate external links

Those checks need separate follow-up work.

## Why Firmware Compile CI Is Deferred

The repository currently has Eclipse/Atollic project metadata, but no verified command-line Makefile or CMake build. The local documentation pass also did not have `arm-none-eabi-gcc` available in PATH.

Compile CI should be added after:

- at least one STM32F411RE project imports and builds successfully in an IDE
- the exact compiler and flags are documented
- source lists, include paths, linker scripts, and startup files are verified
- generated build outputs are separated from source-controlled files

## Local Checks

Before opening documentation or metadata PRs, run:

```text
git diff --check
```

To check maintained docs/config files for merge-conflict markers:

```text
git grep -n -E "^(<<<<<<<|=======|>>>>>>>)" -- README.md CHANGELOG.md CONTRIBUTING.md CODE_OF_CONDUCT.md AGENTS.md THIRD_PARTY_NOTICES.md docs .github
```

For source or hardware-facing PRs, also include the manual build, import, and hardware verification notes requested in the pull request template.
