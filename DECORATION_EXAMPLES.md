# CreatorLab — Example Decoration Stamps

These are original starter-model concepts for the future CreatorLab stamp library. They are **design recipes**, not yet importable in-game object data. The actual stamp format must be implemented and validated against Geometry Dash 2.2081 / Geode 5.11.x before these can be applied automatically.

## Starter library

### 1. Clean Outline
- **Use:** simple block decoration and readable silhouettes.
- **Parts:** edge strip, corner cap, small inset line.
- **Variants:** thin / medium; left-right mirrored.
- **Placement rule:** edge pieces follow the block boundary; corner caps only at detected corners.
- **Suggested palette:** base shade + one accent.

### 2. Tech Panel
- **Use:** futuristic blocks and machinery.
- **Parts:** inset panel, two side bolts, small status light.
- **Variants:** panel with light on/off; bolt pair mirrored.
- **Placement rule:** panel goes in a sufficiently large interior zone; never over a slope tip.
- **Suggested palette:** dark base + metal shade + accent light.

### 3. Neon Circuit
- **Use:** cyber / glow style.
- **Parts:** short circuit line, junction dot, terminal node.
- **Variants:** straight, corner, T-junction.
- **Placement rule:** connect only compatible endpoints; keep glow accents within the selected area.
- **Suggested palette:** one main neon color and a restrained secondary color.

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

- Preview each stamp before applying it.
- Show a small thumbnail and its compatible shape tags.
- Let creators save their own stamps alongside the example library.
- Allow density, variation, symmetry, and seed controls.
- Keep the original level objects untouched until the creator confirms.
- Apply changes as one undoable operation.

## Implementation status

This document defines sample styles and placement rules only. No stamp importer, object placement engine, or built-in in-game model browser is implemented yet. The next implementation step is to define and test the stamp data format, then create the first real reusable stamp from selected editor objects.
