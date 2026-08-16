English | [العربية](README.ar.md)

# Bank System — Login & Permissions — C++ Console App 🏦🔐

An evolution of the Bank System: the whole program now sits behind a login screen, and every action is gated by a role-based permission system — built in C++, with client and user data both persisted to text files.

> Project 1 of **Algorithms & Problem Solving Level 4** (Course 8 of Dr. Mohammed Abu-Hadhoud's programming roadmap).

## Features

- Everything from the Bank System Extension: client CRUD, deposits, withdrawals (never past the available balance), and a total-balances report
- **Login screen** — the program starts by asking for a username and password before showing any menu
- **Role-based permissions** — each user account is granted a specific combination of abilities (view clients, add, delete, update, find, transactions, manage users) or full access; anything outside a user's permissions is blocked with a clear "Access Denied" message
- **Manage Users menu** — add, list, find, update, and delete staff accounts, each with their own permission set, stored separately from client data

## First run — you need a seed admin account

`UserName.txt` starts empty, and creating a new user requires already being logged in with the Manage Users permission — so the very first account has to be added by hand before the program can be used.

Create `UserName.txt` next to the executable with one line, in the same `#//#`-separated format the program itself writes:

```
admin#//#admin123#//#-1
```

`-1` is the "full access" permission value. Change the username/password once you're in.

## Sample: Access Denied

```
____________________________________________________
Access Denied,
You do not have permission to do this;
Please contact your admin.
____________________________________________________
```

## How to Run

```bash
g++ main.cpp -o bank_system_auth
./bank_system_auth
```

> This program uses a Linux-specific system call (`system("clear")`) to clear the screen, so it runs best on Linux/macOS terminals.

## Concepts Practiced

- Bitmask permissions — each ability is its own power-of-two flag (1, 2, 4, 8, 16, 32, 64), combined with `+=` when granting access and checked with `&` when enforcing it — the same technique real access-control systems use
- An authentication gate in front of the whole program, with the logged-in user held in one global struct that every permission check reads from
- Reusing the same struct and the same `#//#` line format to persist two different kinds of records — clients and users — in two separate files
- Recursion for both menu navigation and for retrying a failed lookup

## Author

**Ahmad Slik** — 17 y/o self-taught AI builder, currently following Dr. Mohammed Abu-Hadhoud's programming roadmap.

- Portfolio: [ahmadslik.netlify.app](https://ahmadslik.netlify.app)
- GitHub: [@AhmadSlik](https://github.com/AhmadSlik)
