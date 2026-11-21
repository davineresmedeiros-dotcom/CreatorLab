# CreatorLab Decoration Engine — design notes

This document records the researched direction for CreatorLab's decoration tools. It is a design plan, not a claim that these features are implemented yet.

## What the research shows

- Geometry Dash's native Smart-Block Auto-Build is template-driven: the creator decorates a template, saves it, and the editor matches that design to compatible block shapes.
- Templates can have weighted variations. Rotation and X/Y flips help reuse a design across orientations.
- Antiprime's AutoBuild is a separate creator tool. Public tutorials describe a puzzle-tiling workflow and Wave Function Collapse (WFC), with further template and utility features planned in its update notes.
- The useful lesson is to combine creator-authored designs with shape-aware matching and controlled variation—not to scatter random decoration.

## CreatorLab approach

### Phase 1 — Reusable Decoration Stamps
1. Let the creator select a small decorated group and save it as a named stamp.
2. Store each object's ID, relative position to a stamp anchor, rotation, scale, flip flags, color channels, z layer and z order.
3. Keep the source group untouched; create a preview copy before applying.
4. Allow stamps to be placed at a target point or repeated along a selected region.
5. Offer safe transforms (rotation / flip) only when enabled by the creator.
6. Apply as one undoable operation and provide Cancel / Undo.

### Phase 2 — Shape-aware Auto Decoration
1. Read the selected solid geometry and classify tiles/edges/corners/slopes.
2. Divide the selection into zones: outline, corners, inner fill, accents and empty-space details.
3. Match compatible stamp variants to each zone; do not place a block-design stamp on an incompatible shape.
4. Use weighted variants and a seeded random generator so results can vary but remain reproducible.
5. Validate placements against the selection bounds, avoid excessive overlap, and enforce an object budget.
6. Preview the result before inserting it into the level.

### Phase 3 — Puzzle Tiling / WFC-inspired generation
- Represent the level area as a grid of cells and define which tile/stamp variants may neighbor one another.
- Generate only combinations whose edge/connection rules are compatible.
- Use constraints and backtracking/repair for conflicts; if generation fails, keep the previous preview and report why.
- Provide controls for density, variation, symmetry, and a fixed seed.
- WFC is a later extension; first ship reliable stamp capture, matching, preview, and undo.

## First practical milestone: Stamp MVP

The first usable release is deliberately smaller than the full generator:

1. **Capture** — save a creator-selected decoration as a stamp.
2. **Choose** — choose a saved stamp explicitly (current prototype cycles through filenames).
3. **Preview** — show a non-destructive ghost at the target center before placement.
4. **Fit check** — verify the stamp's local bounds against the selected target region.
5. **Apply** — create only the new stamp objects; do not edit the selected area markers.
6. **Undo safety** — verify that one undo removes the entire placement, and canceling preview creates nothing.

### MVP acceptance checks

- Applying with no selected target area does nothing and explains why.
- An oversized stamp is rejected before any object is created.
- Preview/cancel never changes the level.
- Applying leaves the selected area markers and their groups/properties unchanged.
- A failed creation reports failure instead of claiming success.
- All placement code is reviewed and tested in-game before the feature is marked complete.

### After Stamp MVP: first Auto Decoration generator

The first generator should decorate a creator-selected region using only compatible, creator-authored stamps:

- **Style:** Neon Circuit (initial example style).
- **Density:** sparse / balanced / dense, controlling how many eligible placements are attempted.
- **Pattern:** straight traces, corners, terminals, and junctions; connect only matching ports.
- **Seed:** fixed numeric seed for repeatable results.
- **Preview:** generated placements appear as a preview and can be canceled.
- **Budget:** cap the number of new objects to protect editor performance.

The generator must not simply scatter objects. It should build a connected pattern from stamp ports, check the region bounds, and stop cleanly when no compatible placement remains.

## Important constraints

- Preserve the user's existing objects and never silently replace them.
- Never claim generated decoration is guaranteed to be playable or visually perfect.
- Avoid copying Antiprime's code, proprietary templates, or assets. CreatorLab's algorithms and built-in examples must be original.
- Keep the Android64 / Geometry Dash 2.2081 / Geode 5.x target in mind.
- Builds are manual-only; commits must not trigger automatic compilation.

## Research references

- [Antiprime AutoBuild v1.3.0 tutorial](https://www.youtube.com/watch?v=YryjlXPfjk0) — public update overview, puzzle tiler and WFC chapters.
- [Geometry Dash Editor Guide: Auto-Build System](https://static.wikia.nocookie.net/geometry-dash/images/8/83/GDEditor-v2.2.pdf/revision/latest) — native template workflow.
- [Geometry Dash Creator School: Custom Objects & Autobuild](https://github.com/GDCreatorSchool/gdcs2/blob/main/content/docs/guides/the-editor/custom-objects-autobuild.md) — practical template and variation concepts.
