# CreatorLab

**All-in-one creation toolkit for Geometry Dash.**

CreatorLab is an independent Geode mod project designed to give level creators practical editor tools and controlled generators. The goal is to help build polished decorations and level sections without replacing the creator's decisions with a generic random layout.

## What CreatorLab is

Think of CreatorLab as a toolbox inside the Geometry Dash editor:

- **Stamps:** save a selected group of objects as a reusable decoration model.
- **Auto Decoration:** planned generator that creates decoration from editable rules, patterns, and style presets.
- **Smart Groups:** planned helpers for organizing object groups.
- **Trigger Studio:** planned tools for arranging and managing triggers.
- **Color Manager:** planned palette and color workflow tools.
- **Precision Editor:** planned tools for accurate placement and adjustments.

More planned generators include Background, Structure, Effect, Object, Transition, Color Palette, Design Pattern, Text, Animated Background, Block Variation, and Atmosphere.

## Current prototype

The editor currently has these entry buttons:

- **CreatorLab** — project/toolkit entry point.
- **Stamp** — captures selected objects to a JSON file.
- **Stamps** — cycles through saved stamp files to choose the active one.
- **Preview** — shows the selected stamp's name, file, object count, and position-bounds size without changing the level (information preview, not a visual ghost yet).\n- **Apply** — places the active stamp around the center of a selected target area, after checking its captured position bounds.

The stamp prototype currently stores object ID, relative X/Y position, rotation, and scale. The selected target objects are used as area markers; Apply is intended to create new objects without modifying those markers or copying groups, colors, triggers, or other extra properties.

**Important:** this is an early source prototype and has not yet been compiled or tested in Geometry Dash. The placement fit check uses object positions, not the full visible sprite bounds. Stamp preview, a proper file picker, and richer object-property support are not implemented yet.

## Decoration engine

- [Decoration engine research and phased design](DECORATION_ENGINE.md)
- [Original decoration stamp example catalog](DECORATION_EXAMPLES.md)
- [Stamp format draft](docs/STAMP_FORMAT.md)
- [Neon Circuit straight-stamp data example](examples/neon-circuit-straight.json)
- [Stamp Capture and Apply prototype notes](docs/STAMP_CAPTURE.md)

## Target compatibility

- Geometry Dash 2.2081
- Geode 5.11.x
- Android64 target

## Build

Build with the Geode SDK and its CMake environment. GitHub Actions builds are **manual-only**; pushing commits does not trigger compilation.

## License

MIT — see [LICENSE](LICENSE).
