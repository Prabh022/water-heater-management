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

## 2026-10-23 — Search inventory by brand

- Added menu option 8, "Search Inventory by Brand" (Exit moved to 9):
  `searchInventory()` in `inventory.c` prompts for a brand term and prints
  every inventory row whose brand contains it, using a case-insensitive
  substring match. Available to both access levels, like Display Inventory.
  Prints "No water heaters matched" when nothing fits.
- Verified: compiled with `gcc -std=c11 -Wall -Wextra` (zero warnings).
  Scripted run as admin against a 3-row inventory (GSW / Rheem / Rinnai):
  search "rhe" matched only the Rheem row; "rin" matched only Rinnai;
  "ZZZ" printed the no-match message; Display Inventory unchanged.

## 2026-10-29 — Update inventory quantity by serial number

- Added menu option 9, "Update Inventory Quantity" (Admin only; Exit
  moved to 10): `updateInventoryQuantity()` in `inventory.c` prompts for
  a serial number and a new quantity, then rewrites `data.csv` through a
  temporary file, changing only the matching row. A negative quantity is
  rejected before any file is touched; an unknown serial number reports
  "No water heater found" and leaves the data file untouched. The README
  menu — which still showed the pre-search numbering — is corrected to
  the current 1–10 menu.
- Verified: compiled with `gcc -std=c11 -Wall -Wextra` (zero warnings).
  Scripted run as admin against a 3-row inventory (GSW/SN001 qty 3,
  Rheem/SN002 qty 8, Rinnai/SN003 qty 2): updating SN002 to 12 changed
  only that row; updating unknown serial SN999 changed nothing and
  printed the no-match message; a negative quantity was rejected with
  the file unchanged; Display Inventory and restocking alerts still
  worked afterwards.
