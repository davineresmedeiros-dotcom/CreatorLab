# Stamp Capture Prototype

## Current behavior

The editor has a **Stamp** button. With objects selected, it writes a JSON file under CreatorLab's save directory in the `stamps` folder.

The first prototype records:
- object ID;
- position relative to the first selected object (anchor);
- rotation;
- X and Y scale.

Each capture uses a timestamp-based filename so a new capture does not intentionally overwrite an earlier one.

## Not captured yet

This prototype does not yet preserve:
- color channels / HSV;
- flip flags;
- groups and editor layers;
- object-specific extra fields;
- connection ports or Neon Circuit graph data.

It also does not yet provide a stamp browser, thumbnail, preview, or stamp placement/import.

## Testing

This source change has not been compiled or tested in Geometry Dash yet. The build workflow remains manual-only. Before relying on it, run a manual Android64 build and test capture with a small selection in a disposable level.
