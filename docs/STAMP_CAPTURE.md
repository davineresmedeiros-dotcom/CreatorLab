# Stamp Capture Prototype

## Current behavior

The editor has a **Stamp** button. With objects selected, it writes a JSON file under CreatorLab's save directory in the `stamps` folder.

The prototype currently records:
- object ID;
- position relative to the center of the selected objects' position bounds (anchor);
- the selection's relative min/max bounds, for future previews and placement checks;
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

It includes a Stamp Browser and an Apply prototype. The browser cycles through saved `.json` files in filename order: tap **Stamps** repeatedly to select the next file, then press **Apply**. The selected filename is held for the current editor UI session; if no selection is set or that file is no longer present, Apply falls back to the newest file. Apply treats selected object positions as the target rectangle, rejects stamps whose captured position bounds do not fit, and creates new objects at the rectangle center using only object ID, position, rotation, and scale. It does not change selected objects or write group/color/trigger data. The fit check uses captured object-position bounds, not full sprite/visual bounds. The **Preview** button shows file/object/bounds information. The **Ghost** button draws a temporary cyan schematic: one dot per saved object position plus an outline of the selected area. Press Ghost again to clear it. This is not a render of the actual object sprites and does not place or edit objects. The anchor is based on object positions (not full sprite collision/visual bounds), so it is a useful layout center but not an exact rendered bounding box.

## Testing

The Ghost overlay source has not been compiled or tested in Geometry Dash yet. The build workflow remains manual-only. Before relying on it, run a manual Android64 build and test the overlay in a disposable level.
