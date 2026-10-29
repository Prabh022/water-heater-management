# Water Heater Management System (C)

A modular command-line management system written in C for a small
water-heater business workflow: tank inventory, installation scheduling, and
staging tanks for installers — behind a login with two access levels.

## Features

- Login system with role-based access, checked against `users.csv`:
  - **Admin (level 1):** add inventory, schedule installations, stage tanks
  - **Installer (level 2):** view inventory/schedule and see the tanks
    staged for their own crew name
- Inventory: add a water heater (brand validated against a fixed list),
  display inventory, search inventory by brand (case-insensitive partial
  match), update an inventory item's quantity by serial number (Admin),
  low-stock restocking alerts (quantity below 5)
- Installations: schedule an installation and view the schedule
- Staging: stage a tank for an address/crew and view your staged tanks
- Data stored in plain CSV files in the working directory

## Sample logins (from the bundled `users.csv`)

| Username         | Password    | Role      |
|------------------|-------------|-----------|
| admin1           | password123 | Admin     |
| installer_john   | johnpass    | Installer |

(These are demo credentials for a learning project — passwords are stored
in plain text in `users.csv`. Other sample accounts are in the same file.)

## Build

Requires a C compiler (developed with gcc):

```
gcc -std=c11 -Wall -Wextra main.c inventory.c installation.c staging.c users.c -o water_heater_mgmt
```

## Run

```
./water_heater_mgmt
```

Log in with one of the sample accounts, then use the menu:

```
1. Add Water Heater            (Admin)
2. Display Inventory
3. Check Restocking Alerts
4. Schedule Installation       (Admin)
5. View Installation Schedule
6. Stage Tanks for Installation (Admin)
7. View My Staged Tanks        (Installer)
8. Search Inventory by Brand
9. Update Inventory Quantity   (Admin)
10. Exit
```

The program creates its data files as needed: `data.csv` (inventory),
`installation.csv` (installations), and `staging.csv` (staged tanks) appear
in the working directory the first time you add records. Only `users.csv`
(the login list) ships with the project.

## Sample output (trimmed from an actual run)

```
Login Successful! Welcome, admin1.

Inventory:
Brand | Type | Serial Number | Quantity
GSW | Gas | SN001 | 3

Low stock: GSW (Gas) - Only 3 left!

Staged Tanks for Installation (Assigned to: installer_john)
House No | Street | City | Postal Code | Date | Tank Type
42 | Main Street | Brampton | L6X1A1 | 2026-02-01 | Gas
```

## Project structure

```
main.c          Entry point, login loop, and menu
inventory.c/.h  Add/display/search water heaters, update quantity, restocking alerts
installation.c/.h  Schedule and display installations
staging.c/.h    Stage tanks and list a crew's staged tanks
users.c/.h      Login authentication and access levels
users.csv       Sample user accounts (username,password,accessLevel)
```

## Notes

- This project was extracted from a C projects collection repo; features
  added after extraction are listed in CHANGES.md.
- The original repo's `staging.csv` used an older, incompatible layout and
  was deliberately **not** carried over — see CHANGES.md for the tested
  reason. The program creates a fresh `staging.csv` in its own format the
  first time a tank is staged.
