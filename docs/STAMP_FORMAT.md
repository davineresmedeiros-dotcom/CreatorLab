# CreatorLab Decoration Stamp Format — v1 draft

This draft defines how CreatorLab will describe reusable decoration stamps. It is a **CreatorLab data format**, not a native Geometry Dash level file and not yet loaded by the mod.

## Goals

- Keep object positions relative to a stable stamp anchor.
- Describe compatible connection ports for modular designs such as Neon Circuit.
- Support rotation and mirroring without breaking port directions.
- Store authored object properties while keeping the level untouched until apply.
- Validate bounds and connections before creating editor objects.

## Proposed JSON structure

```json
{
  "format": "creatorlab-stamp",
  "format_version": 1,
  "id": "neon-circuit-straight",
  "name": "Neon Circuit — Straight",
  "style": "neon-circuit",
  "category": "trace",
  "tags": ["circuit", "straight", "connectable"],
  "anchor": { "x": 0, "y": 0 },
  "bounds": { "min_x": -15, "min_y": -3, "max_x": 15, "max_y": 3 },
  "ports": [
    { "id": "west", "x": -15, "y": 0, "direction": "W", "type": "trace" },
    { "id": "east", "x": 15, "y": 0, "direction": "E", "type": "trace" }
  ],
  "transforms": {
    "rotate": true,
    "flip_x": true,
    "flip_y": false
  },
  "objects": [],
  "variants": [],
  "rules": {
    "must_stay_inside_selection": true,
    "allow_overlap": false,
    "require_matching_ports": true
  }
}
```

The empty `objects` array is intentional: the real object records must come from selected Geometry Dash editor objects and be captured by a future CreatorLab stamp tool. Do not treat this example as an importable decoration.

## Field meanings

- `anchor`: origin used to calculate relative object positions.
- `bounds`: stamp's local bounding rectangle.
- `ports`: connection points. Directions are N, E, S, W.
- `transforms`: allowed transformations; port directions and coordinates must transform together.
- `objects`: captured object records. Each record will preserve its object ID and required editable properties.
- `variants`: alternative stamps with the same role or compatible ports.
- `rules`: safety and placement constraints checked before preview/apply.

## Validation rules

1. Reject unknown format names or unsupported versions.
2. Reject non-finite coordinates and invalid bounds.
3. Every port must lie on or within the declared bounds.
4. A transformed stamp must transform port positions and directions consistently.
5. Connected ports must have compatible types, coincide within the placement tolerance, and face each other.
6. Reject placement outside the selected region when the stamp requires containment.
7. Never mutate the level during preview; apply only after confirmation.
8. Applying a batch should be undoable as one operation.

## Neon Circuit connection model

A port has a `type` (for example `trace`) and a cardinal `direction`. Two ports connect when:
- their types are compatible;
- their world positions match within the configured tolerance;
- their directions are opposite.

Straight stamps have two opposite ports. Corners have two perpendicular ports. T-junctions have three ports. Crosses have four. Terminal nodes intentionally have one port.

## Status

Draft v1 for implementation planning. Parsing, editor-object capture, preview, and placement are not implemented yet. The format may change before the first functional stamp exporter is shipped.
