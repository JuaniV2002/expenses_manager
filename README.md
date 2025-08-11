# Expense Tracker

This C program helps you manage expenses with a simple terminal UI. Add, edit, delete, list, and persist expenses; also see monthly totals and breakdowns by type.

## Features

- Add expense: name, description, amount, type (Fixed/Variable), and date.
- Modify expense: update any field of a selected expense.
- Delete expense: with confirmation prompt.
- Show expenses: color-coded output (Fixed = blue, Variable = green) with indices.
- Monthly expenses total: sum of all expenses for a given month.
- Fixed expenses total: sum of fixed expenses for a given month.
- Variable expenses total: sum of variable expenses for a given month.
- Save to file / Load from file: persist your data to expenses.txt.

## Improvements

- Indexed display to select items for edit/delete easily.
- Basic input validation for expense type.
- File persistence for saving and loading.

## Getting started (macOS/Linux)

Ensure you have a C compiler installed.

- macOS (Homebrew):
	- brew update
	- brew install gcc
- Linux (Debian/Ubuntu):
	- sudo apt update
	- sudo apt install build-essential

Verify the compiler is available:

```bash
gcc --version
```

### Compile

```bash
gcc -o expenses expenses.c
```

### Run

```bash
./expenses
```