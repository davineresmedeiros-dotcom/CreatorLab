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

It includes a paged Stamp Manager and an Apply prototype. The manager displays six saved `.json` filenames per page, marks the active file, and lets the user click a filename to select it. Use the left/right page controls when more than six stamps exist. The chosen filename is held for the current editor UI session; press **Apply** to place it. If no selection is set or the selected file is no longer present, Apply falls back to the newest file. Apply treats selected object positions as the target rectangle, rejects stamps whose captured position bounds do not fit, and creates new objects at the rectangle center using only object ID, position, rotation, and scale. It does not change selected objects or write group/color/trigger data. The fit check uses captured object-position bounds, not full sprite/visual bounds. The **Preview** button shows file/object/bounds information. The **Ghost** button draws a temporary cyan schematic: one dot per saved object position plus an outline of the selected area. Press Ghost again to clear it. This is not a render of the actual object sprites and does not place or edit objects. The anchor is based on object positions (not full sprite collision/visual bounds), so it is a useful layout center but not an exact rendered bounding box.

## Stage status

Stamp Capture is **not considered complete yet**. The first manual build and in-game test are still pending by user request; do not trigger compilation automatically. The build workflow remains manual-only.

## Testing

Use a disposable level for the first test. Check capture, file listing/selection, information preview, Ghost on/off, and Apply. Verify that selected area markers remain unchanged and that no groups, colors, or triggers are copied. Check that the Ghost is positioned correctly in editor coordinates and disappears when toggled off. Also test a stamp that does not fit and confirm Apply places nothing. Report any build or in-game error before closing this stage.
