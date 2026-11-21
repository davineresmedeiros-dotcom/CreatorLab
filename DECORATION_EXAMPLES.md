# CreatorLab — Example Decoration Stamps

These are original starter-model concepts for the future CreatorLab stamp library. They are **design recipes**, not yet importable in-game object data. The actual stamp format must be implemented and validated against Geometry Dash 2.2081 / Geode 5.11.x before these can be applied automatically.

## First style in development: Neon Circuit

Neon Circuit is the first priority for the decoration engine. Its look should feel like a clean futuristic circuit board: connected neon traces, small junctions, terminal dots, and restrained glow accents. The generator must favor readable connected paths over random clutter.

### Neon Circuit stamp set

1. **Circuit Straight** — short horizontal/vertical trace with two compatible endpoints.
2. **Circuit Corner** — 90-degree trace; endpoints must match neighboring trace directions.
3. **Circuit T-Junction** — three-way connection for branching paths.
4. **Circuit Cross** — four-way connector; use sparingly to avoid visual overload.
5. **Terminal Node** — endpoint dot / small socket, only for a path end.
6. **Pulse Node** — small accent light placed on an existing trace, not as a disconnected decoration.
7. **Circuit Frame** — optional trace along a block edge, with corner-safe variants.

### Placement and generation rules

- Build a connected path graph first, then place compatible stamps along its edges.
- Endpoints carry direction tags: N, E, S, W. A stamp may connect only when the neighboring endpoint directions agree.
- Support straight, corner, T, and cross pieces; use a terminal node for intentional path ends.
- Keep all stamp bounds inside the selected block/region; reject placements that spill outside.
- Avoid overlapping traces and avoid placing a junction on a slope tip or narrow edge.
- Use a small accent budget: traces are the main visual, nodes are secondary, pulse lights are rare.
- Provide mirrored and rotated variants, but transform endpoint tags together with the artwork.
- Use a fixed seed for repeatable results and preview before applying.
- Start with a modest density; offer sparse / balanced / dense rather than unrestricted random placement.

### Suggested palette roles

- **Trace:** primary neon channel.
- **Node:** same hue or slightly brighter accent.
- **Panel / backing:** dark shade, optional.
- **Glow:** optional low-intensity secondary effect.

Palette values should remain user-controlled through CreatorLab's Color Manager; do not hardcode a single color scheme into the stamp geometry.

### Suggested starter preset

- Style: Neon Circuit
- Density: Balanced
- Symmetry: Off by default
- Variation: Medium
- Seed: fixed per preview
- Glow accents: Low
- Path connectivity: Required

## Other example styles

### 2. Clean Outline
- **Use:** simple block decoration and readable silhouettes.
- **Parts:** edge strip, corner cap, small inset line.
- **Variants:** thin / medium; left-right mirrored.
- **Placement rule:** edge pieces follow the block boundary; corner caps only at detected corners.
- **Suggested palette:** base shade + one accent.

### 3. Tech Panel
- **Use:** futuristic blocks and machinery.
- **Parts:** inset panel, two side bolts, small status light.
- **Variants:** panel with light on/off; bolt pair mirrored.
- **Placement rule:** panel goes in a sufficiently large interior zone; never over a slope tip.
- **Suggested palette:** dark base + metal shade + accent light.

### 4. Crystal Cave
- **Use:** cave, fantasy, or nature-themed blocks.
- **Parts:** small crystal cluster, rock shard, tiny ground accent.
- **Variants:** 2–4 crystal silhouettes with different rotations.
- **Placement rule:** clusters attach to edges or corners; avoid filling the entire interior.
- **Suggested palette:** stone shade + crystal accent.

### 5. Ornamental Arch
- **Use:** temples, castles, and decorative structures.
- **Parts:** column segment, arch segment, top ornament.
- **Variants:** mirrored column; short / tall arch.
- **Placement rule:** use paired columns and a compatible arch span; keep the center opening clear.
- **Suggested palette:** stone base + highlight + optional accent.

## Library behavior planned

- Preview each stamp before applying.
- Show a thumbnail and compatible shape / endpoint tags.
- Let creators save their own stamps alongside the example library.
- Allow density, variation, symmetry, and seed controls.
- Keep original level objects untouched until the creator confirms.
- Apply changes as one undoable operation.

## Implementation status

Neon Circuit is the first planned style, with a defined stamp set and connectivity rules. This document is still a design specification: no stamp importer, object placement engine, or in-game model browser is implemented yet. The next engineering step is to define and test the stamp data format, then capture the first real reusable stamp from selected editor objects.
