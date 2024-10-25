# Expense tracker
This **C** program will help you to manage your **expenses**, offering plenty of commands to better understand your spendings:
- _Cargar gasto_ (Register expense): this option adds a new expense.
- _Modificar gasto_ (Modify expense): it allows you to modify a given expense.
- _Elminar gasto_ (Delete expense): deletes an expense.
- _Listar gastos_ (Show expenses): shows all the saved expenses.
- _Gastos menusales_ (Monthly expenses): given a month, it shows the total spendings.
- _Gastos fijos_ (Fixed costs): shows all the fixed costs.
- _Gastos variables_ (Variable costs): shows all the variable costs.
- _Guardar expensas en arhivo_ (Save expenses in file): saves the expenses in a file.

To give this program a try on Linux:
- Install gcc with this command:
  ```
  sudo apt update
  sudo apt install build-essential
  ```
  or if you are on mac using Homebrew:
  ```
  brew update && brew upgrade
  brew install gcc
  ```
- Check C compiler version to verify a successful installation:
  ```
  gcc --version
  ```
- Compile the program:
  ```
  gcc -o expenses expenses.c
  ```
- Run the program:
  ```
  ./expenses
  ```
