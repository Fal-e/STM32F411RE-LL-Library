# Release Checklist

This document describes how to prepare a repository release. It is written for small maintenance releases where the release notes must be honest about what was and was not verified.

## Release Naming

Use semantic version tags:

```text
v0.1.0
```

The first revived public maintenance release should use this GitHub release title:

```text
v0.1.0 - revived public maintenance baseline
```

## Pre-Release Checklist

Before creating a release:

- Confirm `Development` is up to date with `origin/Development`.
- Confirm all intended PRs are merged.
- Confirm GitHub Actions are passing on the final branch.
- Confirm `CHANGELOG.md` has the correct version section.
- Confirm `docs/releases/v0.1.0.md` matches the final merged state.
- Confirm `README.md`, `ROADMAP.md`, `RELEASE.md`, and documentation links are current.
- Confirm no generated `Debug/`, `.metadata/`, or build artifacts are tracked.
- Confirm no source code or hardware behavior is described as verified unless it was actually tested.

## Local Checks

Run from the repository root:

```text
git status --short --branch
git diff --check
git grep -n -E "^(<<<<<<<|=======|>>>>>>>)" -- README.md .gitignore CHANGELOG.md ROADMAP.md RELEASE.md CONTRIBUTING.md CODE_OF_CONDUCT.md AGENTS.md THIRD_PARTY_NOTICES.md stm32_ssbp/README.md docs .github
```

For v0.1.0, also confirm the release notes include:

- what changed
- what was verified
- what still needs toolchain verification
- what still needs hardware verification

## Create The Tag

After the release prep PR is merged and the final commit on `Development` is correct:

```text
git checkout Development
git pull --ff-only origin Development
git tag -a v0.1.0 -m "v0.1.0 - revived public maintenance baseline"
git push origin v0.1.0
```

## Create The GitHub Release

Use the GitHub UI or GitHub CLI.

With GitHub CLI:

```text
gh release create v0.1.0 --repo Fal-e/STM32F411RE-LL-Library --title "v0.1.0 - revived public maintenance baseline" --notes-file docs/releases/v0.1.0.md
```

Before publishing, check:

- the tag is `v0.1.0`
- the target branch/commit is the intended `Development` commit
- the release title is exactly `v0.1.0 - revived public maintenance baseline`
- the release notes do not overstate build, toolchain, or hardware verification

## After Release

After publishing:

- Confirm the release page renders correctly.
- Confirm README links still work.
- Open follow-up issues for build/import verification, hardware checks, and driver audits.
- Start the next `Unreleased` section in `CHANGELOG.md` when the next change lands.
