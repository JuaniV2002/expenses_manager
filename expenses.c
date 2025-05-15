// Expense Manager with Basic Improvements
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
} TDate;

typedef struct Expense {
    char name[LMAX];
    char description[LMAX];
    TDate date;
    int amount;
    int type; // 1 para fijo, 0 para variable
} TExpense;

typedef struct Data {
    TExpense expenses[NMAX];
    int elements;
} TData;

bool isEmpty(TData* data);
bool isFull(TData* data);
void newExpense(TData* data, TDate* date);
void modifyExpense(TData* data, int index);
void deleteExpense(TData* data, int index);
void showExpenses(TData* data);
int monthlyExpenses(TData* data, int month);
int fixedExpenses(TData* data, int month);
int variableExpenses(TData* data, int month);
void saveExpensesToFile(TData* data, const char* filename);
void loadExpensesFromFile(TData* data, const char* filename);
int inputExpenseType();

int main() {
    TData data = { .elements = 0 };
    TDate date;
    int option, index, month;

    printf("\nIngrese el d\u00eda de hoy: ");
    scanf("%d", &date.day);
    printf("Ingrese el mes de hoy: ");
    scanf("%d", &date.month);
    printf("Ingrese el a\u00f1o de hoy: ");
    scanf("%d", &date.year);

    do {
        printf("\n-----------------------------------\n");
        printf("Nuevo gasto (1)\n");
        printf("Modificar un gasto (2)\n");
        printf("Eliminar un gasto (3)\n");
        printf("Mostrar gastos (4)\n");
        printf("Gastos mensuales (5)\n");
        printf("Mostrar gastos fijos y monto en un mes (6)\n");
        printf("Mostrar gastos variables y monto en un mes (7)\n");
        printf("Guardar gastos en archivo (8)\n");
        printf("Cargar gastos desde archivo (9)\n");
        printf("Salir (10)\n");
        printf("-----------------------------------\n");
        printf("Ingrese una opci\u00f3n: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                newExpense(&data, &date);
                break;
            case 2:
                printf("Ingrese el \u00edndice del gasto a modificar: ");
                scanf("%d", &index);
                modifyExpense(&data, index);
                break;
            case 3:
                printf("Ingrese el \u00edndice del gasto a eliminar: ");
                scanf("%d", &index);
                deleteExpense(&data, index);
                break;
            case 4:
                showExpenses(&data);
                break;
            case 5:
                printf("Ingrese un mes (1-12): ");
                scanf("%d", &month);
                printf("Total gastado en mes %d: $%d\n", month, monthlyExpenses(&data, month));
                break;
            case 6:
                printf("Ingrese un mes (1-12): ");
                scanf("%d", &month);
                printf("Gastos fijos en mes %d: $%d\n", month, fixedExpenses(&data, month));
                break;
            case 7:
                printf("Ingrese un mes (1-12): ");
                scanf("%d", &month);
                printf("Gastos variables en mes %d: $%d\n", month, variableExpenses(&data, month));
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
                printf("Opci\u00f3n inv\u00e1lida.\n");
                break;
        }
    } while (1);
}

bool isEmpty(TData* data) {
    return data->elements == 0;
}

bool isFull(TData* data) {
    return data->elements == NMAX;
}

int inputExpenseType() {
    int type;
    do {
        printf("Tipo de gasto (1 = Fijo, 0 = Variable): ");
        scanf("%d", &type);
    } while (type != 0 && type != 1);
    return type;
}

void newExpense(TData* data, TDate* date) {
    if (isFull(data)) {
        printf("La lista est\u00e1 llena.\n");
        return;
    }

    TExpense new_expense;
    printf("\nNombre del nuevo gasto: ");
    scanf(" %99[^\n]", new_expense.name);
    printf("Descripci\u00f3n del nuevo gasto: ");
    scanf(" %99[^\n]", new_expense.description);
    printf("Monto gastado: ");
    scanf("%d", &new_expense.amount);
    new_expense.type = inputExpenseType();
    new_expense.date = *date;

    int pos = 0;
    if (new_expense.type == 1) {
        for (int j = data->elements; j > 0; j--) {
            data->expenses[j] = data->expenses[j - 1];
        }
    } else {
        for (pos = 0; pos < data->elements; pos++) {
            if (data->expenses[pos].type != 1) break;
        }
        for (int j = data->elements; j > pos; j--) {
            data->expenses[j] = data->expenses[j - 1];
        }
    }
    data->expenses[pos] = new_expense;
    data->elements++;
    printf("Nuevo gasto a\u00f1adido con \u00e9xito!\n");
}

void modifyExpense(TData* data, int index) {
    if (isEmpty(data)) {
        printf("La lista est\u00e1 vac\u00eda.\n");
        return;
    }
    if (index < 1 || index > data->elements) {
        printf("\u00cdndice fuera de rango.\n");
        return;
    }
    index--;
    TExpense* expense = &data->expenses[index];
    printf("Nuevo nombre del gasto: ");
    scanf(" %99[^\n]", expense->name);
    printf("Nueva descripci\u00f3n del gasto: ");
    scanf(" %99[^\n]", expense->description);
    printf("Nuevo monto del gasto: ");
    scanf("%d", &expense->amount);
    expense->type = inputExpenseType();
    printf("El gasto fue modificado con \u00e9xito!\n");
}

void deleteExpense(TData* data, int index) {
    if (isEmpty(data)) {
        printf("La lista est\u00e1 vac\u00eda.\n");
        return;
    }
    if (index < 1 || index > data->elements) {
        printf("\u00cdndice fuera de rango.\n");
        return;
    }
    index--;
    printf("\u00bfEst\u00e1s seguro que quer\u00e9s eliminar '%s'? (s/n): ", data->expenses[index].name);
    char confirm;
    scanf(" %c", &confirm);
    if (confirm != 's' && confirm != 'S') {
        printf("Eliminaci\u00f3n cancelada.\n");
        return;
    }
    for (int i = index; i < data->elements - 1; i++) {
        data->expenses[i] = data->expenses[i + 1];
    }
    data->elements--;
    printf("Gasto eliminado con \u00e9xito!\n");
}

void showExpenses(TData* data) {
    if (isEmpty(data)) {
        printf("La lista est\u00e1 vac\u00eda.\n");
        return;
    }
    printf("\nGastos:\n");
    for (int i = 0; i < data->elements; i++) {
        TExpense* e = &data->expenses[i];
        const char* color = e->type == 1 ? BLUE : GREEN;
        printf("\n%s[%d]%s\n", color, i + 1, RESET);
        printf("Nombre: %s\n", e->name);
        printf("Descripci\u00f3n: %s\n", e->description);
        printf("Fecha: %02d/%02d/%04d\n", e->date.day, e->date.month, e->date.year);
        printf("Monto: $%d\n", e->amount);
        printf("Tipo: %s\n", e->type == 1 ? "Fijo" : "Variable");
    }
}

int monthlyExpenses(TData* data, int month) {
    int total = 0;
    for (int i = 0; i < data->elements; i++) {
        if (data->expenses[i].date.month == month) {
            total += data->expenses[i].amount;
        }
    }
    return total;
}

int fixedExpenses(TData* data, int month) {
    int total = 0;
    for (int i = 0; i < data->elements; i++) {
        if (data->expenses[i].type == 1 && data->expenses[i].date.month == month) {
            total += data->expenses[i].amount;
        }
    }
    return total;
}

int variableExpenses(TData* data, int month) {
    int total = 0;
    for (int i = 0; i < data->elements; i++) {
        if (data->expenses[i].type == 0 && data->expenses[i].date.month == month) {
            total += data->expenses[i].amount;
        }
    }
    return total;
}

void saveExpensesToFile(TData* data, const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    for (int i = 0; i < data->elements; i++) {
        TExpense e = data->expenses[i];
        fprintf(f, "%s\n%s\n%d %d %d\n%d\n%d\n",
            e.name, e.description,
            e.date.day, e.date.month, e.date.year,
            e.amount, e.type);
    }
    fclose(f);
    printf("Gastos guardados exitosamente en %s\n", filename);
}

void loadExpensesFromFile(TData* data, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    data->elements = 0;
    while (!feof(f) && data->elements < NMAX) {
        TExpense* e = &data->expenses[data->elements];
        if (fgets(e->name, LMAX, f) == NULL) break;
        e->name[strcspn(e->name, "\n")] = 0;
        fgets(e->description, LMAX, f);
        e->description[strcspn(e->description, "\n")] = 0;
        fscanf(f, "%d %d %d", &e->date.day, &e->date.month, &e->date.year);
        fscanf(f, "%d", &e->amount);
        fscanf(f, "%d\n", &e->type);
        data->elements++;
    }
    fclose(f);
    printf("Gastos cargados desde %s\n", filename);
}
