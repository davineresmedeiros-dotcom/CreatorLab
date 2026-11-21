# Stamp Stage — First Test Checklist

This checklist is for the first manual Android64 build and Geometry Dash test.

**Do not compile automatically.** The build and in-game test happen only when the project owner requests them.

## Build and launch
- [ ] Request/perform the manual build.
- [ ] Confirm CreatorLab appears and loads in Geode.
- [ ] Open a disposable level in the editor.

## Capture and manager
- [ ] Select a small set of decoration objects and press **Stamp**.
- [ ] Confirm a new JSON stamp is saved.
- [ ] Press **Stamps** and confirm the list is shown.
- [ ] Cycle selection and confirm the active filename marker changes.
- [ ] Confirm **Preview** reports the selected file and object count.

## Ghost
- [ ] Select area-marker objects and press **Ghost**.
- [ ] Check the cyan dots and rectangle appear in the correct editor location.
- [ ] Press **Ghost** again and confirm the overlay disappears.
- [ ] Confirm the preview did not edit or create level objects.

## Apply and safety
- [ ] Press **Apply** with a stamp that fits the selected area.
- [ ] Confirm new objects appear at the intended location.
- [ ] Confirm the selected area-marker objects remain unchanged.
- [ ] Confirm groups, colors, and triggers were not copied.
- [ ] Try a stamp that does not fit and confirm no objects are placed.

## Report and close the stage
Record any build error, Geode loading error, crash, wrong placement, or unexpected object modification. Fix and retest before marking the Stamp stage complete.

## Known limitations before the first test
- Stamp selection currently cycles with the **Stamps** button; direct click-to-select is not implemented.
- Ghost uses schematic dots, not actual object sprites.
- Fit validation uses object positions, not full visual/sprite bounds.
- Captured fields are limited to object ID, relative position, rotation, and scale.
- The source has not yet been compiled or tested in-game.
