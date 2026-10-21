# Changes made during standalone extraction (October 2026)

Extracted from the `c-projects-portfolio` collection repo. Only the project's
real source files and its working login file (`users.csv`) were carried
over — Visual Studio files (`.sln`, `.vcxproj`) were left behind.

**No code changes were needed.** The original code compiles cleanly with
`gcc -std=c11 -Wall -Wextra` (zero errors, zero warnings). Scripted test
runs verified: a failed login is rejected; admin login; adding a water
heater; inventory display; a low-stock alert firing (quantity 3 < threshold
5); scheduling and viewing an installation; staging a tank; an installer
logging in and seeing exactly that staged tank under "View My Staged
Tanks"; and admin-only actions correctly returning "Access Denied!" for an
installer.

## Data files not carried over — and why

- **`staging.csv` (original) — left behind, proven incompatible.** The file
  in the original repo has a header row plus an extra leading serial-number
  column and **no tank-type column** (8 fields per row), while the code
  reads and writes 7 fields (`houseNumber, streetName, city, postalCode,
  scheduledDate, crewName, tankType`). Tested with the original file in
  place: an installer whose tank had just been staged was told "No tanks
  staged for installation assigned to you," because the legacy rows throw
  the parser out of alignment. Tested again without it: staging and viewing
  work correctly. The file was not converted, because converting it would
  require inventing the missing tank types. The original file remains in
  the source repo.
- **`data.csv` and `installation.csv` — empty (0 bytes) in the original.**
  The program creates both on first use, so nothing was lost by leaving
  them behind.
- **`tank_inventory.csv`, `staged_jobs.csv`, `user_info.csv` — not
  referenced by any code** (they use different schemas and appear to be
  leftovers from earlier iterations). Left behind; `users.csv` is the
  login file the code actually reads.
