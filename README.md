# Expense Tracker

This **C** program helps you manage your **expenses**, offering a variety of commands to better understand your spendings. It's ideal for personal use, small businesses, or budget-conscious teams.

## Features

- **_Cargar gasto_ (Register expense):** Add a new expense with description, amount, type, and date.
- **_Modificar gasto_ (Modify expense):** Modify any field of a selected expense.
- **_Eliminar gasto_ (Delete expense):** Delete an expense (with confirmation prompt).
- **_Listar gastos_ (Show expenses):** Display all expenses, showing their type (Fixed/Variable) with color-coded formatting.
- **_Gastos mensuales_ (Monthly expenses):** Show total expenses for a given month.
- **_Gastos fijos_ (Fixed costs):** List and sum all fixed expenses for a month.
- **_Gastos variables_ (Variable costs):** List and sum all variable expenses for a month.
- **_Guardar expensas en archivo_ (Save expenses to file):** Persist your expenses to a file.
- **_Cargar expensas desde archivo_ (Load expenses from file):** Load previously saved expenses.

## Improvements

- ✅ Indexed display: makes it easier to identify expenses when modifying or deleting.
- ✅ Input validation: ensures only valid types (fixed or variable) are accepted.
- ✅ Color-coded output: fixed = blue, variable = green.
- ✅ File persistence with both saving and loading capabilities.

## Getting Started

To give this program a try on **Linux**:

```bash
sudo apt update
sudo apt install build-essential
```
or if you are on mac using homebrew:
  
```bash
brew update
brew install gcc
```
Verify the compiler is available:
  
```bash
gcc --version
```

## Compile the program:
  
```bash
gcc -o expenses expenses.c
```

## Run the program:
  
```bash
./expenses
```