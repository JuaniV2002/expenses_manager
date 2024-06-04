#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NMAX 100
#define LMAX 100

// Estructura que almacena todos los aspectos de una fecha.
typedef struct Date {
    int day;
    int month;
    int year;
} TDate;

// Estructura que almacena todos los aspectos de un gasto.
typedef struct Expense {
    char name[LMAX];
    char description[LMAX];
    TDate date;
    int amount;
    int type; // 1 para fijo, 0 para variable
} TExpense;

// Estructura que almacena el array de gastos y los elementos actuales del array.
typedef struct Data {
    TExpense expenses[NMAX];
    int elements;
} TData;

// Perfiles de todas las funciones utilizadas en el programa.
bool isEmpty(TData* data);
bool isFull(TData* data);
void newExpense(TData* data, TDate* date);
void modifyExpense(TData* data, int index);
void deleteExpense(TData* data, int index);
void showExpenses(TData* data);
int monthlyExpenses(TData* data, int month);
int fixedExpenses(TData* data, int month);
int variableExpenses(TData* data, int month);

int main() {
    TData data = { .elements = 0 };
    TDate date;
    int option, index, month;

    printf("Ingrese el día de hoy: ");
    scanf("%d", &date.day);
    printf("Ingrese el mes de hoy: ");
    scanf("%d", &date.month);
    printf("Ingrese el año de hoy: ");
    scanf("%d", &date.year);

    do {
        // Menú que se mostrará cada vez que se ejecute el programa
        printf("\n-----------------------------------\n");
        printf("Nuevo gasto (1)\n");
        printf("Modificar un gasto (2)\n");
        printf("Eliminar un gasto (3)\n");
        printf("Mostrar gastos (4)\n");
        printf("Gastos mensuales (5)\n");
        printf("Mostrar nombres de gastos fijos y monto gastado en un mes (6)\n");
        printf("Mostrar nombres de gastos variables y monto gastado en un mes (7)\n");
        printf("Salir (8)\n");
        printf("-----------------------------------\n");
        printf("Ingrese una opción: ");
        fflush(stdout); fflush(stdin);
        scanf("%d", &option);
        fflush(stdin);

        switch (option) {
            case 1:
                newExpense(&data, &date);    
                break;
            case 2:
                printf("Ingrese el índice del gasto a modificar: ");
                scanf("%d", &index);
                modifyExpense(&data, index);
                break;
            case 3:
                printf("Ingrese el índice del gasto a eliminar: ");
                scanf("%d", &index);
                deleteExpense(&data, index);
                break;
            case 4: 
                showExpenses(&data);
                break;
            case 5:
                printf("Ingrese un mes (entre 1 y 12): ");
                scanf("%d", &month);
                printf("Monto gastado en el mes %d: $%d\n", month, monthlyExpenses(&data, month));
                break;
            case 6:
                printf("Ingrese un mes (entre 1 y 12): ");
                scanf("%d", &month);
                printf("Monto gastado en gastos fijos en el mes %d: $%d\n", month, fixedExpenses(&data, month));
                break;
            case 7:
                printf("Ingrese un mes (entre 1 y 12): ");
                scanf("%d", &month);
                printf("Monto gastado en gastos variables en el mes %d: $%d\n", month, variableExpenses(&data, month));
                break;
            case 8:
                return 0;
            default: // Opción no válida.
                printf("Opción inválida.\n");
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

void newExpense(TData* data, TDate* date) {
    if (isFull(data)) {
        printf("La lista está llena.\n");
        return;
    }

    TExpense new_expense;
    printf("Nombre del nuevo gasto: ");
    scanf(" %99[^\n]", new_expense.name);
    printf("Descripción del nuevo gasto: ");
    scanf(" %99[^\n]", new_expense.description);
    printf("Monto gastado: ");
    scanf("%d", &new_expense.amount);
    printf("Tipo de gasto (1 es fijo, 0 es variable): ");
    scanf("%d", &new_expense.type);

    new_expense.date = *date;
    int pos = 0;
    if (new_expense.type == 1) {
        for (int j = data->elements; j > 0; j--) {
            data->expenses[j] = data->expenses[j - 1];
        }
    } else {
        for (pos = 0; pos < data->elements; pos++) {
            if (data->expenses[pos].type != 1) {
                break;
            }
        }
        for (int j = data->elements; j > pos; j--) {
            data->expenses[j] = data->expenses[j - 1];
        }
    }

    data->expenses[pos] = new_expense;
    data->elements++;
    printf("Nuevo gasto añadido con éxito!\n");
}

void modifyExpense(TData* data, int index) {
    if (isEmpty(data)) {
        printf("La lista está vacía.\n");
        return;
    }

    if (index < 1 || index > data->elements) {
        printf("Índice fuera de rango.\n");
        return;
    }

    index--;
    TExpense* expense = &data->expenses[index];
    printf("Nuevo nombre del gasto: ");
    scanf(" %99[^\n]", expense->name);
    printf("Nueva descripción del gasto: ");
    scanf(" %99[^\n]", expense->description);
    printf("Nuevo monto del gasto: ");
    scanf("%d", &expense->amount);

    printf("El gasto en el índice %d fue modificado con éxito!\n", index + 1);
}

void deleteExpense(TData* data, int index) {
    if (isEmpty(data)) {
        printf("La lista está vacía.\n");
        return;
    }

    if (index < 1 || index > data->elements) {
        printf("Índice fuera de rango.\n");
        return;
    }

    index--;
    for (int i = index; i < data->elements - 1; i++) {
        data->expenses[i] = data->expenses[i + 1];
    }
    data->elements--;
    printf("Gasto en el índice %d fue eliminado con éxito!\n", index + 1);
}

void showExpenses(TData* data) {
    if (isEmpty(data)) {
        printf("La lista está vacía.\n");
        return;
    }

    printf("\nGastos:");
    for (int i = 0; i < data->elements; i++) {
        TExpense* expense = &data->expenses[i];
        printf("\n-----------------------------------\n");
        printf("Nombre: %s\n", expense->name);
        printf("Descripción: %s\n", expense->description);
        printf("Fecha: %d/%d/%d\n", expense->date.day, expense->date.month, expense->date.year);
        printf("Monto: $%d\n", expense->amount);
        printf("Tipo (1 es fijo, 0 es variable): %d\n", expense->type);
        printf("-----------------------------------\n");
    }
}

int monthlyExpenses(TData* data, int month) {
    if (isEmpty(data)) {
        printf("La lista está vacía.\n");
        return 0;
    }

    int total = 0;
    for (int i = 0; i < data->elements; i++) {
        if (data->expenses[i].date.month == month) {
            total += data->expenses[i].amount;
        }
    }
    return total;
}

int fixedExpenses(TData* data, int month) {
    if (isEmpty(data)) {
        printf("La lista está vacía.\n");
        return 0;
    }

    int total = 0;
    for (int i = 0; i < data->elements; i++) {
        if (data->expenses[i].type == 1 && data->expenses[i].date.month == month) {
            total += data->expenses[i].amount;
        }
    }
    return total;
}

int variableExpenses(TData* data, int month) {
    if (isEmpty(data)) {
        printf("La lista está vacía.\n");
        return 0;
    }

    int total = 0;
    for (int i = 0; i < data->elements; i++) {
        if (data->expenses[i].type == 0 && data->expenses[i].date.month == month) {
            total += data->expenses[i].amount;
        }
    }
    return total;
}
