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

## Week 0 — Scratch
No code, since Scratch is a drag-and-block visual editor, not a text language. scratch_project.md is a design spec for a small arcade game ("Catch the Falling Stars") — sprites, variables, and the event/broadcast logic — written so it could be built directly in the Scratch editor later. This week is really about learning event-driven programming (loops, conditionals, variables) without syntax getting in the way.

## Week 1 — C basics
Introduces C's compile-run cycle, variables, loops, and functions.

hello.c — reads a name, prints a greeting. The "hello world" of the course.
mario_less.c / mario_more.c — print a half/double pyramid of # using nested loops (outer loop = row, inner loops = spaces then hashes). "More comfortable" version factors the row-printing into a function and mirrors it for the double pyramid.
cash.c — classic greedy-algorithm problem: given change owed, work out the fewest US coins (25¢, 10¢, 5¢, 1¢) needed by repeatedly taking the largest coin that fits.
credit.c — validates a credit card number using Luhn's algorithm: double every second digit from the right, subtract 9 if it's over 9, sum everything, and it's valid if the total is divisible by 10. Then the card length and leading digits determine AMEX/VISA/MASTERCARD.

## Week 2 — Arrays & strings
scrabble.c — sums letter values (like the board game) for two words and declares a winner; teaches indexing into a lookup table by character.
readability.c — computes the Coleman-Liau index (a reading-grade-level formula based on letters/words/sentences per 100 words) by walking the string once and counting character classes.
caesar.c — classic substitution cipher: shifts each letter by a key (mod 26), preserving case and leaving non-letters untouched. Takes the key as a command-line argument, which is what actually differs from week1 (argv handling).
Week 3 — Algorithms (voting systems)
These all model real-world voting methods as data structures + algorithms:

plurality.c — simplest: tally votes per candidate, print whoever has the most.
runoff.c — Instant Runoff Voting: voters rank all candidates; count first-choice votes, and if no one has a majority, eliminate the last-place candidate and recount, repeating until someone wins or there's a tie.
tideman.c — Ranked Pairs: builds a graph of pairwise "X beats Y" preferences, sorts pairs by margin of victory strongest-first, and locks each pair into the graph unless doing so would create a cycle (checked via recursive graph traversal). The winner is the "source" node with no incoming locked edges. This is the most algorithmically involved problem in the set — it's really a graph/cycle-detection exercise wearing a voting-theory costume.
Week 4 — Memory (pointers & binary file formats)
This week is about manipulating raw bytes via pointers, not just types the language checks for you.

volume.c — reads a WAV file byte-for-byte, copies the 44-byte header unchanged, then multiplies every 16-bit audio sample by a volume factor.
filter.c (+ bmp.h) — image processing on 24-bit BMP files: grayscale (average RGB), sepia (weighted RGB formula), reflect (flip pixels horizontally), box blur (average each pixel with its neighbors). bmp.h defines the packed BMP header structs matching the real Windows format.
recover.c — digital forensics: scans a raw memory-card image in 512-byte blocks looking for the JPEG magic-byte signature (ff d8 ff Ex), and writes each contiguous run of blocks out as its own numbered .jpg file.
Since I don't have CS50's actual test images/audio/memory-card dump, I added make_wav.c, make_bmp.c, make_card.c — small generators that synthesize valid test fixtures, so each program is actually runnable and was verified against real (if synthetic) data rather than just reading correct on paper.

## Week 5 — Data Structures (Speller)
dictionary.c/.h + speller.c — a spell-checker built on a hash table with chaining: each word hashes to one of ~4000 buckets, collisions form a linked list. load() reads a dictionary file into the table, check() does a case-insensitive lookup, unload() frees it all. speller.c reads a text file word-by-word (handling apostrophes like "don't"), flags anything not found, and times each phase. This is the week's core lesson: same problem (word lookup) as week 2's linear approach, but O(1)-ish instead of O(n) thanks to the data structure.
dictionaries/small.txt (635 words) and sample.txt (with 5 deliberate typos) are the test fixtures — verified it caught exactly those 5.

## Week 6 — Python
Same four problems as week 1/2 (Mario, Cash, Credit, Readability), reimplemented in Python. The point of this week is contrasting languages: no manual memory/types, built-in string methods, list comprehensions — same logic, far less code. I cross-checked outputs against the C versions (e.g. same card numbers → same VISA/MASTERCARD/INVALID results) to confirm the port was faithful.

## Week 7 — SQL
movies_*.sql — a small relational schema (people, movies, stars, directors, ratings) with sample data, plus queries demonstrating joins (who starred in a movie), subqueries (movies sharing a cast member with another movie), and filtering/sorting. This mirrors CS50's real IMDb-based dataset, just scaled down since I don't have their actual multi-hundred-thousand-row database.
songs_*.sql — a Spotify-style songs table with audio features (danceability, energy, valence, tempo), with queries for ranking/filtering/aggregating (ORDER BY, AVG).

## Week 8 — HTML/CSS/JavaScript
week8/homepage/ — a personal portfolio page (navbar, About/Projects/Contact) built with Bootstrap for layout, custom CSS for styling, and vanilla JS for two real interactions: a mobile nav toggle and client-side form validation (checks required fields and email format, shows inline error/success states) — no backend involved, this week is purely client-side.

## Week 9 — Flask (server-side web)
week9/app/ — a small Flask app (app.py) backed by SQLite (init_db.py creates the birthdays table) that renders a form + table via a Jinja2 template, and handles POST /add and POST /delete/<id> to mutate the database and redirect back to /. This is the first "full stack" week: a server holding state in a real database rather than everything living in memory or a browser.

On verification: everything was actually compiled/run/tested, not just written and assumed correct — I compiled all C with -Wall -Wextra and ran each against real inputs myself (catching, e.g., that a "known" test credit-card number I picked wasn't actually Luhn-valid — turned out to be my error, not the code's), and the three background agents independently built and ran their own test fixtures (synthetic BMP/WAV/raw-card files, a live Flask server test, a speller run against planted typos) before reporting back.