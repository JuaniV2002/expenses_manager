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
- Save to CSV / Load from CSV: persist your data to expenses.csv.

### New enhancements

- Per-expense date input with a shortcut to use “today’s” date captured at startup.
- Search expenses by keyword (name or description).
- Show expenses sorted by amount (descending) for quick scanning of top spend.
- Monthly report showing total, fixed, and variable subtotals in one view.
- CSV export/import (expenses.csv) for portability and editing in spreadsheets. The app now uses CSV by default for Save/Load.

Notes:
- The CSV format is simple; commas inside fields aren’t escaped.
- CSV import replaces the current in-memory list with the file contents.

## Improvements

- Indexed display to select items for edit/delete easily.
- Basic input validation for expense type.
- File persistence for saving and loading.

## Getting started (macOS/Linux)

Ensure you have a C compiler installed.

- macOS (Homebrew):
```sh
brew update && brew install gcc
```
- Linux (Debian/Ubuntu):
```sh
sudo apt update && sudo apt install build-essential
```

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

### Starter data

This repo includes a sample expenses.csv with dummy data so you can explore the features immediately. Use:

- Menu option 9 (Load expenses from CSV) to load the sample.
- Menu option 8 (Save expenses to CSV) to persist your changes.
