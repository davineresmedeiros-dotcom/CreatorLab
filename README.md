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

## Decoration engine

- [Decoration engine research and phased design](DECORATION_ENGINE.md)
- [Original decoration stamp example catalog](DECORATION_EXAMPLES.md)
- [Stamp format draft](docs/STAMP_FORMAT.md)
- [Neon Circuit straight-stamp data example](examples/neon-circuit-straight.json)
- [Stamp Capture prototype notes](docs/STAMP_CAPTURE.md)

The editor source now includes an initial Stamp Capture button and JSON save prototype. It records object IDs, positions relative to a centered selection anchor, relative position bounds, rotation, and scale. This source change is **not compiled or tested in-game yet**; colors, flips, groups, port data, preview, and placement remain future work.

## Target compatibility

- Geometry Dash 2.2081
- Geode 5.11.x

## Build

Build using the Geode SDK and its CMake environment. GitHub Actions builds are manual-only; pushing commits does not trigger compilation.

## License

MIT — see [LICENSE](LICENSE).
