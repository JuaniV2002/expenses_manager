// Expense Manager with Basic Improvements (English UI)
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NMAX 100
#define LMAX 100
#define BLUE "\033[1;34m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

typedef struct Date {
    int day;
    int month;
    int year;
} Date;

typedef enum {
    EXPENSE_VARIABLE = 0,
    EXPENSE_FIXED = 1
} ExpenseType;

typedef struct Expense {
    char name[LMAX];
    char description[LMAX];
    Date date;
    int amount;
    ExpenseType type; // 1 = Fixed, 0 = Variable
} Expense;

typedef struct ExpenseData {
    Expense expenses[NMAX];
    int elements;
} ExpenseData;

bool isEmpty(ExpenseData* data);
bool isFull(ExpenseData* data);
void newExpense(ExpenseData* data, Date* date);
void modifyExpense(ExpenseData* data, int index);
void deleteExpense(ExpenseData* data, int index);
void showExpenses(ExpenseData* data);
int monthlyExpenses(ExpenseData* data, int month);
int fixedExpenses(ExpenseData* data, int month);
int variableExpenses(ExpenseData* data, int month);
void saveExpensesToFile(ExpenseData* data, const char* filename);
void loadExpensesFromFile(ExpenseData* data, const char* filename);
ExpenseType inputExpenseType(void);

int main(void) {
    ExpenseData data = { .elements = 0 };
    Date date;
    int option, index, month;

    printf("\nEnter today's day: ");
    scanf("%d", &date.day);
    printf("Enter today's month: ");
    scanf("%d", &date.month);
    printf("Enter today's year: ");
    scanf("%d", &date.year);

    do {
        printf("\n-----------------------------------\n");
        printf("Add expense (1)\n");
        printf("Modify an expense (2)\n");
        printf("Delete an expense (3)\n");
        printf("Show expenses (4)\n");
        printf("Monthly expenses total (5)\n");
        printf("Show fixed expenses and total for a month (6)\n");
        printf("Show variable expenses and total for a month (7)\n");
        printf("Save expenses to file (8)\n");
        printf("Load expenses from file (9)\n");
        printf("Exit (10)\n");
        printf("-----------------------------------\n");
        printf("Enter an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                newExpense(&data, &date);
                break;
            case 2:
                printf("Enter the index of the expense to modify: ");
                scanf("%d", &index);
                modifyExpense(&data, index);
                break;
            case 3:
                printf("Enter the index of the expense to delete: ");
                scanf("%d", &index);
                deleteExpense(&data, index);
                break;
            case 4:
                showExpenses(&data);
                break;
            case 5:
                printf("Enter a month (1-12): ");
                scanf("%d", &month);
                printf("Total spent in month %d: $%d\n", month, monthlyExpenses(&data, month));
                break;
            case 6:
                printf("Enter a month (1-12): ");
                scanf("%d", &month);
                printf("Fixed expenses in month %d: $%d\n", month, fixedExpenses(&data, month));
                break;
            case 7:
                printf("Enter a month (1-12): ");
                scanf("%d", &month);
                printf("Variable expenses in month %d: $%d\n", month, variableExpenses(&data, month));
                break;
            case 8:
                saveExpensesToFile(&data, "expenses.txt");
                break;
            case 9:
                loadExpensesFromFile(&data, "expenses.txt");
                break;
            case 10:
                return 0;
            default:
                printf("Invalid option.\n");
                break;
        }
    } while (1);
}

bool isEmpty(ExpenseData* data) {
    return data->elements == 0;
}

bool isFull(ExpenseData* data) {
    return data->elements == NMAX;
}

ExpenseType inputExpenseType(void) {
    int type;
    do {
        printf("Expense type (1 = Fixed, 0 = Variable): ");
        scanf("%d", &type);
    } while (type != 0 && type != 1);
    return type == 1 ? EXPENSE_FIXED : EXPENSE_VARIABLE;
}

void newExpense(ExpenseData* data, Date* date) {
    if (isFull(data)) {
        printf("The list is full.\n");
        return;
    }

    Expense new_expense;
    printf("\nName of the new expense: ");
    scanf(" %99[^\n]", new_expense.name);
    printf("Description of the new expense: ");
    scanf(" %99[^\n]", new_expense.description);
    printf("Amount spent: ");
    scanf("%d", &new_expense.amount);
    new_expense.type = inputExpenseType();
    new_expense.date = *date;

    int pos = 0;
    if (new_expense.type == EXPENSE_FIXED) {
        for (int j = data->elements; j > 0; j--) {
            data->expenses[j] = data->expenses[j - 1];
        }
    } else {
        for (pos = 0; pos < data->elements; pos++) {
            if (data->expenses[pos].type != EXPENSE_FIXED) break;
        }
        for (int j = data->elements; j > pos; j--) {
            data->expenses[j] = data->expenses[j - 1];
        }
    }
    data->expenses[pos] = new_expense;
    data->elements++;
    printf("New expense added successfully!\n");
}

void modifyExpense(ExpenseData* data, int index) {
    if (isEmpty(data)) {
        printf("The list is empty.\n");
        return;
    }
    if (index < 1 || index > data->elements) {
        printf("Index out of range.\n");
        return;
    }
    index--;
    Expense* expense = &data->expenses[index];
    printf("New expense name: ");
    scanf(" %99[^\n]", expense->name);
    printf("New expense description: ");
    scanf(" %99[^\n]", expense->description);
    printf("New expense amount: ");
    scanf("%d", &expense->amount);
    expense->type = inputExpenseType();
    printf("Expense modified successfully!\n");
}

void deleteExpense(ExpenseData* data, int index) {
    if (isEmpty(data)) {
        printf("The list is empty.\n");
        return;
    }
    if (index < 1 || index > data->elements) {
        printf("Index out of range.\n");
        return;
    }
    index--;
    printf("Are you sure you want to delete '%s'? (y/n): ", data->expenses[index].name);
    char confirm;
    scanf(" %c", &confirm);
    if (confirm != 'y' && confirm != 'Y') {
        printf("Deletion canceled.\n");
        return;
    }
    for (int i = index; i < data->elements - 1; i++) {
        data->expenses[i] = data->expenses[i + 1];
    }
    data->elements--;
    printf("Expense deleted successfully!\n");
}

void showExpenses(ExpenseData* data) {
    if (isEmpty(data)) {
        printf("The list is empty.\n");
        return;
    }
    printf("\nExpenses:\n");
    for (int i = 0; i < data->elements; i++) {
        Expense* e = &data->expenses[i];
        const char* color = e->type == EXPENSE_FIXED ? BLUE : GREEN;
        printf("\n%s[%d]%s\n", color, i + 1, RESET);
        printf("Name: %s\n", e->name);
        printf("Description: %s\n", e->description);
        printf("Date: %02d/%02d/%04d\n", e->date.day, e->date.month, e->date.year);
        printf("Amount: $%d\n", e->amount);
        printf("Type: %s\n", e->type == EXPENSE_FIXED ? "Fixed" : "Variable");
    }
}

int monthlyExpenses(ExpenseData* data, int month) {
    int total = 0;
    for (int i = 0; i < data->elements; i++) {
        if (data->expenses[i].date.month == month) {
            total += data->expenses[i].amount;
        }
    }
    return total;
}

int fixedExpenses(ExpenseData* data, int month) {
    int total = 0;
    for (int i = 0; i < data->elements; i++) {
        if (data->expenses[i].type == EXPENSE_FIXED && data->expenses[i].date.month == month) {
            total += data->expenses[i].amount;
        }
    }
    return total;
}

int variableExpenses(ExpenseData* data, int month) {
    int total = 0;
    for (int i = 0; i < data->elements; i++) {
        if (data->expenses[i].type == EXPENSE_VARIABLE && data->expenses[i].date.month == month) {
            total += data->expenses[i].amount;
        }
    }
    return total;
}

void saveExpensesToFile(ExpenseData* data, const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < data->elements; i++) {
        Expense e = data->expenses[i];
        fprintf(f, "%s\n%s\n%d %d %d\n%d\n%d\n",
            e.name, e.description,
            e.date.day, e.date.month, e.date.year,
            e.amount, e.type);
    }
    fclose(f);
    printf("Expenses saved successfully to %s\n", filename);
}

void loadExpensesFromFile(ExpenseData* data, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Could not open file.\n");
        return;
    }
    data->elements = 0;
    while (!feof(f) && data->elements < NMAX) {
        Expense* e = &data->expenses[data->elements];
        if (fgets(e->name, LMAX, f) == NULL) break;
        e->name[strcspn(e->name, "\n")] = 0;
        fgets(e->description, LMAX, f);
        e->description[strcspn(e->description, "\n")] = 0;
        fscanf(f, "%d %d %d", &e->date.day, &e->date.month, &e->date.year);
        fscanf(f, "%d", &e->amount);
        int t;
        fscanf(f, "%d\n", &t);
        e->type = (t == 1) ? EXPENSE_FIXED : EXPENSE_VARIABLE;
        data->elements++;
    }
    fclose(f);
    printf("Expenses loaded from %s\n", filename);
}
