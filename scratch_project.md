# CS50 Week 0 — Scratch

CS50's Week 0 problem set is a Scratch project (a `.sb3` file built visually in the
Scratch editor at https://scratch.mit.edu/projects/editor/), not text-based code, so
it can't be authored as a source file the way the other weeks can. This file records
the project design instead, to build later directly in the Scratch editor.

## Project: "Catch the Falling Stars"

A simple arcade game.

**Sprites**
- `Basket` — controlled by left/right arrow keys (or drag), stays within the stage
  bounds (`if x < -220 then set x to -220`, mirrored on the right edge).
- `Star` — spawns at a random x position at the top of the stage, falls at increasing
  speed as the score rises, and on reaching the bottom either:
  - touches `Basket` → play a "collect" sound, `change score by 1`, reset to top at a
    new random x, increase fall speed slightly.
  - misses `Basket` → play a "miss" sound, `change lives by -1`, reset to top.
- `Backdrop` — starry background; switches to a "game over" backdrop when `lives = 0`.

**Variables**: `score` (for all sprites), `lives` (for all sprites, starts at 3).

**Broadcasts**: `game start` (green flag → reset score/lives, start Star's fall loop),
`game over` (when `lives = 0` → stop all, switch backdrop, show final score).

**Logic sketch (pseudocode for the Star sprite's forever loop)**

```
when green flag clicked
set lives to 3
set score to 0
broadcast [game start]

when I receive [game start]
go to x: (pick random -220 to 220) y: 170
forever
  change y by (-2 - score / 5)
  if touching [Basket]:
    play sound [collect]
    change score by 1
    go to x: (pick random -220 to 220) y: 170
  if y position < -170:
    change lives by -1
    go to x: (pick random -220 to 220) y: 170
    if lives = 0:
      broadcast [game over]
      stop [this script]
```

This is enough of a spec to build the project directly in the Scratch editor when
picking it back up — the actual `.sb3` isn't something that can be produced here.
