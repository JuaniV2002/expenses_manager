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
bool inputDate(Date* out, const char* promptPrefix, const Date* defaultDate, bool allowDefault);
void printExpense(const Expense* e, int index);
void searchExpenses(ExpenseData* data);
void showExpensesSortedByAmountDesc(ExpenseData* data);
void monthlyReport(ExpenseData* data);
void exportExpensesToCSV(ExpenseData* data, const char* filename);
void importExpensesFromCSV(ExpenseData* data, const char* filename);
static int ci_strstr(const char* haystack, const char* needle);

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
        printf("Search expenses by keyword (10)\n");
        printf("Show expenses sorted by amount (desc) (11)\n");
        printf("Monthly report (total/fixed/variable) (12)\n");
        printf("Export to CSV (13)\n");
        printf("Import from CSV (14)\n");
        printf("Exit (15)\n");
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
                searchExpenses(&data);
                break;
            case 11:
                showExpensesSortedByAmountDesc(&data);
                break;
            case 12:
                monthlyReport(&data);
                break;
            case 13:
                exportExpensesToCSV(&data, "expenses.csv");
                break;
            case 14:
                importExpensesFromCSV(&data, "expenses.csv");
                break;
            case 15:
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

void newExpense(ExpenseData* data, Date* today) {
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
    if (!inputDate(&new_expense.date, "Expense date", today, true)) {
        printf("Invalid date. Aborting add.\n");
        return;
    }

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
    char ch;
    printf("Change date? (y/n): ");
    scanf(" %c", &ch);
    if (ch == 'y' || ch == 'Y') {
        Date current = expense->date;
        if (!inputDate(&expense->date, "New expense date", &current, false)) {
            printf("Invalid date. Keeping previous date.\n");
        }
    }
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
        printExpense(&data->expenses[i], i);
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

bool inputDate(Date* out, const char* promptPrefix, const Date* defaultDate, bool allowDefault) {
    if (allowDefault && defaultDate) {
        printf("Use today's date (%02d/%02d/%04d)? (y/n): ", defaultDate->day, defaultDate->month, defaultDate->year);
        char c; scanf(" %c", &c);
        if (c == 'y' || c == 'Y') {
            *out = *defaultDate;
            return true;
        }
    }
    int d, m, y;
    printf("%s - day (1-31): ", promptPrefix);
    if (scanf("%d", &d) != 1 || d < 1 || d > 31) return false;
    printf("%s - month (1-12): ", promptPrefix);
    if (scanf("%d", &m) != 1 || m < 1 || m > 12) return false;
    printf("%s - year (>=1900): ", promptPrefix);
    if (scanf("%d", &y) != 1 || y < 1900) return false;
    out->day = d; out->month = m; out->year = y;
    return true;
}

void printExpense(const Expense* e, int index) {
    const char* color = e->type == EXPENSE_FIXED ? BLUE : GREEN;
    printf("\n%s[%d]%s\n", color, index + 1, RESET);
    printf("Name: %s\n", e->name);
    printf("Description: %s\n", e->description);
    printf("Date: %02d/%02d/%04d\n", e->date.day, e->date.month, e->date.year);
    printf("Amount: $%d\n", e->amount);
    printf("Type: %s\n", e->type == EXPENSE_FIXED ? "Fixed" : "Variable");
}

static int ci_strstr(const char* haystack, const char* needle) {
    if (!*needle) return 1;
    size_t nlen = strlen(needle);
    for (const char* h = haystack; *h; ++h) {
        size_t i = 0;
        while (i < nlen) {
            char c1 = h[i];
            char c2 = needle[i];
            if (!c1) return 0;
            if (c1 >= 'A' && c1 <= 'Z') c1 = (char)(c1 - 'A' + 'a');
            if (c2 >= 'A' && c2 <= 'Z') c2 = (char)(c2 - 'A' + 'a');
            if (c1 != c2) break;
            i++;
        }
        if (i == nlen) return 1;
    }
    return 0;
}

void searchExpenses(ExpenseData* data) {
    if (isEmpty(data)) {
        printf("The list is empty.\n");
        return;
    }
    char keyword[LMAX];
    printf("Enter keyword to search (name/description): ");
    scanf(" %99[^\n]", keyword);
    int found = 0;
    for (int i = 0; i < data->elements; i++) {
        Expense* e = &data->expenses[i];
        if (ci_strstr(e->name, keyword) || ci_strstr(e->description, keyword)) {
            printExpense(e, i);
            found++;
        }
    }
    if (!found) printf("No expenses matched your search.\n");
}

static int cmp_amount_desc(const void* a, const void* b) {
    const Expense* ea = (const Expense*)a;
    const Expense* eb = (const Expense*)b;
    if (ea->amount < eb->amount) return 1;
    if (ea->amount > eb->amount) return -1;
    return 0;
}

void showExpensesSortedByAmountDesc(ExpenseData* data) {
    if (isEmpty(data)) {
        printf("The list is empty.\n");
        return;
    }
    Expense temp[NMAX];
    for (int i = 0; i < data->elements; i++) temp[i] = data->expenses[i];
    qsort(temp, data->elements, sizeof(Expense), cmp_amount_desc);
    printf("\nExpenses (sorted by amount desc):\n");
    for (int i = 0; i < data->elements; i++) {
        printExpense(&temp[i], i);
    }
}

void monthlyReport(ExpenseData* data) {
    if (isEmpty(data)) {
        printf("The list is empty.\n");
        return;
    }
    int month;
    printf("Enter a month (1-12): ");
    scanf("%d", &month);
    int total = monthlyExpenses(data, month);
    int fixed = fixedExpenses(data, month);
    int variable = variableExpenses(data, month);
    printf("\nMonthly report for month %d\n", month);
    printf("Total: $%d\n", total);
    printf("Fixed: $%d\n", fixed);
    printf("Variable: $%d\n", variable);
}

void exportExpensesToCSV(ExpenseData* data, const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Error opening CSV file.\n");
        return;
    }
    fprintf(f, "name,description,day,month,year,amount,type\n");
    for (int i = 0; i < data->elements; i++) {
        const Expense* e = &data->expenses[i];
        // Note: simple CSV, commas in text will break
        fprintf(f, "%s,%s,%d,%d,%d,%d,%s\n",
                e->name,
                e->description,
                e->date.day, e->date.month, e->date.year,
                e->amount,
                e->type == EXPENSE_FIXED ? "Fixed" : "Variable");
    }
    fclose(f);
    printf("Expenses exported to %s\n", filename);
}

void importExpensesFromCSV(ExpenseData* data, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Could not open CSV file.\n");
        return;
    }
    char line[LMAX * 3];
    // skip header
    if (!fgets(line, sizeof(line), f)) {
        fclose(f);
        printf("CSV file is empty.\n");
        return;
    }
    int count = 0;
    while (fgets(line, sizeof(line), f) && count < NMAX) {
        // naive CSV split by comma
        char* tokens[7];
        int t = 0;
        char* p = strtok(line, ",\n");
        while (p && t < 7) { tokens[t++] = p; p = strtok(NULL, ",\n"); }
        if (t < 7) continue;
        Expense e;
        strncpy(e.name, tokens[0], LMAX - 1); e.name[LMAX - 1] = '\0';
        strncpy(e.description, tokens[1], LMAX - 1); e.description[LMAX - 1] = '\0';
        e.date.day = atoi(tokens[2]);
        e.date.month = atoi(tokens[3]);
        e.date.year = atoi(tokens[4]);
        e.amount = atoi(tokens[5]);
        if (tokens[6][0] == 'F' || tokens[6][0] == 'f') e.type = EXPENSE_FIXED; else e.type = EXPENSE_VARIABLE;
        data->expenses[count++] = e;
    }
    data->elements = count;
    fclose(f);
    printf("Imported %d expenses from %s\n", count, filename);
}
