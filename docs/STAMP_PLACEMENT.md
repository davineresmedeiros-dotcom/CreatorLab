# Stamp Placement — Safe Placement Contract

## Intended behavior

Stamp placement is a non-destructive operation in the Geometry Dash editor.

- The current editor selection defines the target rectangle (the minimum/maximum X and Y positions of the selected objects).
- A stamp is placed only when its complete captured bounds fit inside that rectangle.
- Placement translates the stamp to the center of the target rectangle. It does not scale, stretch, rotate, or rearrange the stamp to force it to fit.
- If the stamp does not fit, placement is cancelled with a clear message and no objects are created.
- Existing selected objects are used only to define the area. They are not moved, edited, deleted, regrouped, or recolored.
- The placement operation must not assign or alter group IDs, color channels, editor layers, triggers, or other unrelated object properties.
- New stamp objects should use the stamp's captured object ID and transform data only. Any additional object properties are left at the game's defaults unless a later, explicitly designed stamp format supports them.
- Placement should be undoable through the normal editor undo system.

## Important limitation

The current Stamp Capture prototype stores object ID, relative X/Y, rotation, and scale. It does not capture full object property data or sprite bounds. The current Stamp Browser only lists saved filenames.

This document defines the safe behavior for the upcoming placement implementation. It does not claim that stamp placement is implemented yet.
