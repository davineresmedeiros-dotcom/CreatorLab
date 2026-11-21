# CreatorLab

**All-in-one creation toolkit for Geometry Dash.**

CreatorLab is an independent Geode mod project focused on tools and generators for level creators.

## Planned generators

- Auto Decoration
- Background, Structure, Effect, Object, and Transition
- Color Palette and Design Pattern
- Text, Animated Background, Block Variation, and Atmosphere

## Planned editor tools

- Smart Groups
- Trigger Studio
- Color Manager
- Object Tools
- Precision Editor

The project is being implemented incrementally. Features will only be marked complete after they are implemented and tested in-game.

## Decoration engine research

The decoration system is planned around reusable creator-made stamps, shape-aware matching, weighted variations, preview/undo, and later constraint-based tiling.

- [Decoration engine research and phased design](DECORATION_ENGINE.md)
- [Original decoration stamp example catalog](DECORATION_EXAMPLES.md)
- [Stamp format draft](docs/STAMP_FORMAT.md)
- [Neon Circuit straight-stamp data example](examples/neon-circuit-straight.json)

The catalog and JSON example describe design/data formats only. They are not yet an in-game stamp library or importable object set.

## Target compatibility

- Geometry Dash 2.2081
- Geode 5.11.x

## Build

Build using the Geode SDK and its CMake environment. GitHub Actions builds are manual-only; pushing commits does not trigger compilation.

## License

MIT — see [LICENSE](LICENSE).
