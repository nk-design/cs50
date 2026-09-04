# CS50

Personal solutions to Harvard's CS50x problem sets, built for practice — not
submitted anywhere for credit or a certificate.

## What this is

Each week of the course lives on its own branch instead of its own folder.
This branch (`main`) is intentionally just this README — it's the front door
to the repo, not a place to stash code.

| Branch | Week | Topic | Language(s) |
|---|---|---|---|
| `week_0` | 0 | Scratch | design spec (Scratch isn't text code) |
| `week_1` | 1 | C basics | C |
| `week_2` | 2 | Arrays & strings | C |
| `week_3` | 3 | Algorithms (voting systems) | C |
| `week_4` | 4 | Memory (binary file formats) | C |
| `week_5` | 5 | Data Structures (spell-checker) | C |
| `week_6` | 6 | Python | Python |
| `week_7` | 7 | SQL | SQL / SQLite |
| `week_8` | 8 | HTML, CSS, JavaScript | HTML/CSS/JS |
| `week_9` | 9 | Flask | Python (Flask) + SQLite |

## Why branches instead of folders

Keeps each week isolated and self-contained — checking out `week_4` gives a
clean working directory with only that week's files, no need to `cd` past
nine other weeks' worth of code to find anything. It also mirrors how the
weeks were actually built: independently, and in several cases in parallel.

## How this was built

For each week, I reimplemented the classic CS50 problem set(s) from scratch
in the original language(s) the course uses, without depending on CS50's own
libraries (`cs50.h`, the `cs50` Python package) or its official starter
files/datasets — those aren't publicly redistributable, so anything that
normally depends on them (BMP/WAV headers, a spell-checker dictionary, a
movies/songs database) was rebuilt as a smaller, self-contained equivalent
instead.

Everything was actually compiled and run against real test input before
being considered done — not just written and assumed correct:

- All C compiles clean under `gcc -Wall -Wextra -std=c11` with zero warnings.
- Week 4 (Volume/Filter/Recover) ships small generator programs that
  synthesize test WAV/BMP/raw-card files, since no official test media was
  available — each filter's output was checked pixel-by-pixel against an
  independently computed expected result.
- Week 5's spell-checker was run against a sample text with planted typos
  and caught exactly those, with no false positives.
- Week 7's SQL queries were run against real (if small, hand-built) SQLite
  databases and the output was checked by hand.
- Week 9's Flask app was run with a live dev server and exercised with real
  HTTP requests (add/delete a birthday, confirm the SQLite row actually
  changed) before being called done.

## How to navigate the repo

Each week is a normal git branch — switch to it to see (and work on) that
week's files at the repository root:

```bash
git branch -a          # list all weeks
git switch week_4       # check out week 4
git switch main         # back to this README
```

Nothing here builds on anything else — each branch stands alone, so there's
no fixed order you have to check them out in.
