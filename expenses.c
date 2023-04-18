#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NMAX 100
#define LMAX 100

//struct that stores all the aspects of a date.
typedef struct Date{
    int day;
    int month;
    int year;
}TDate;

//sruct that stores all the aspects of an expense.
typedef struct Expense{
    char name[LMAX];
    char description[LMAX];
    TDate date;
    int amount;
    int type;
}TExpense;

//struct that stores the array of expenses and the actual elements of the array.
typedef struct Data{
    TExpense expenses[NMAX];
    int elements;
}TData;

//profile of every function used in the program.
bool isEmpty(TData* data);
bool isFull(TData* data);
void newExpense(TData* data, TDate* date);
void modifyExpense(TData* data, int index);
void deleteExpense(TData* data, int index);
void showExpenses(TData* data);
int monthlyExpenses(TData* data, int month);
int fixedExpenses(TData* data, int month);
int variableExpenses(TData* data, int month);

TData data;
TDate date;

int main() {
    int option;
    int index;
    int month;

    printf("\nInput today's day: ");
    scanf("%d", &date.day);
    printf("Input today's month: ");
    scanf("%d", &date.month);
    printf("Input today's year: ");
    scanf("%d", &date.year);

    do{
        //menu that will be displayed everytime the user runs the program
        printf("\n-----------------------------------\n");
        printf("New expense (1)\n");
        printf("Modify an expense (2)\n");
        printf("Delete an expense (3)\n");
        printf("Show expenses (4)\n");
        printf("Monthly expenses (5)\n");
        printf("Show fixed expense's names and amount spended in a given month (6)\n");
        printf("Show variable expense's names and amount spended in a given month (7)\n");
        printf("Save and exit (8)");
        printf("\n-----------------------------------\n");
        printf("Input an option: ");
        fflush(stdout); fflush(stdin);
        scanf("%d", &option);
        fflush(stdin);

        switch (option){
            case 1:
                newExpense(&data, &date);    
                break;

            case 2:
                printf("\nInput the index in which the desired expense to be modified is: ");
                scanf("%d", &index);
                modifyExpense(&data, index);
                break;

            case 3:
                printf("\nInput the index in which the desired expense to be deleted is: ");
                scanf("%d", &index);
                deleteExpense(&data, index);
                break;

            case 4: 
                showExpenses(&data);
                break;

            case 5:
                printf("\nInput a month (between 1 and 12): ");
                scanf("%d", &month);
                printf("\nAmount spended in month %d: $%d", month, monthlyExpenses(&data, month));
                break;

            case 6:
                printf("\nInput a month (between 1 and 12): ");
                scanf("%d", &month);
                printf("\nAmount spended in these fixed expenses at month %d: $%d\n", month, fixedExpenses(&data, month));
                break;

            case 7:
                printf("\nInput a month (between 1 and 12): ");
                scanf("%d", &month);
                printf("\nAmount spended in these variable expenses at month %d: $%d\n", month, variableExpenses(&data, month));
                break;

            case 8:
                return 0;
                break;
            
            default: // option is not between 1 and 9.
                printf("\nInvalid option.\n");
                break;
        }
    } while (1);
}

bool isEmpty(TData* data){
    // if the amount of elements in the array is equal to 0, it returns True.
    if ((*data).elements == 0){
        return true;
    }else{
        return false;
    }
}

bool isFull(TData* data){
    // if the amount of elements in the array is equal to NMAX, it returns True.
    if ((*data).elements == NMAX){
        return true;
    }else{
        return false;
    }
}

void newExpense(TData* data, TDate* date){
    char name[LMAX];
    char description[LMAX];
    int amount;
    int type;

    if (isFull(data)){
        printf("The list is full.");
    }else{
        //data is asked to the user and stored in local variables.
        printf("\nNew expenses's name: ");
        scanf(" %s", name);
        printf("New expense's description: ");
        scanf(" %s", description);
        printf("Amount spended: ");
        scanf("%d", &amount);
        printf("Expense type (1 is fixed, 0 is variable): ");
        scanf("%d", &type);
        
        //if the type is 1 (that is, the expense is fixed...).
        if (type == 1){
            int j;
            //I shift every element forward to make room for the new expense.
            for (j = (*data).elements; j > 0; j--){
                (*data).expenses[j] = (*data).expenses[j - 1];
            }
            //store the data in the empty place
            strcpy((*data).expenses[j].name, name);
            strcpy((*data).expenses[j].description, description);
            (*data).expenses[0].date.day = (*date).day;
            (*data).expenses[0].date.month = (*date).month;
            (*data).expenses[0].date.year = (*date).year;
            (*data).expenses[j].amount = amount;
            (*data).expenses[j].type = type;
            
            (*data).elements++;
            printf("\nNew expense added successfully!\n");
        }else{
            int i, pos;
            //this loop will traverse the array until it founds the first variable expense.
            for (i = 0; i < NMAX; i++){
                if ((*data).expenses[i].type != 1){
                    break;
                }    
            }
            pos = i;
            //I shift every element forward to make room for the new expense.
            for (int j = (*data).elements; j >= pos; j--){
                (*data).expenses[j] = (*data).expenses[j - 1];
            }
            //store the data in the empty place
            strcpy((*data).expenses[pos].name, name);
            strcpy((*data).expenses[pos].description, description);
            (*data).expenses[pos].date.day = (*date).day;
            (*data).expenses[pos].date.month = (*date).month;
            (*data).expenses[pos].date.year = (*date).year;
            (*data).expenses[pos].amount = amount;
            (*data).expenses[pos].type = type;
            
            (*data).elements++;
            printf("\nNew expense added successfully!\n");
        }
    }
}

void modifyExpense(TData* data, int index){
    char name[LMAX];
    char description[LMAX];
    int amount;

    if (isEmpty(data)){
        printf("The list is empty.");
    }else{
        index--;
        printf("\nNew expense's name: ");
        scanf("%s", name);
        printf("New expense's description: ");
        scanf("%s", description);
        printf("New expense's amount: ");
        scanf("%d", &amount);
    
        strcpy((*data).expenses[index].name, name);
        strcpy((*data).expenses[index].description, description);
        (*data).expenses[index].amount = amount;
        printf("\nThe expense at index %d was modified successfully!\n", ++index);
    }
}

void deleteExpense(TData* data, int index){
    
    if (isEmpty(data)){
        printf("The list is empty.");
    }else{
        index--;
        int i = index;
    
        for (; i < (*data).elements; i++){
            (*data).expenses[i] = (*data).expenses[i + 1];
        }
        (*data).elements--;
        printf("\nExpense at index %d was deleted successfully!\n", ++index);
    }
}

void showExpenses(TData* data){
    
    if (isEmpty(data)){
        printf("The list is empty.");
    }else{
        printf("\nExpenses:");
        for (int i = 0; i < (*data).elements; i++){
            printf("\n-----------------------------------\n");
            printf("Name: %s\n", (*data).expenses[i].name);
            printf("Description: %s\n", (*data).expenses[i].description);
            printf("Date: %d/%d/%d \n", (*data).expenses[i].date.day, (*data).expenses[i].date.month, (*data).expenses[i].date.year);
            printf("Amount: $%d\n", (int) (*data).expenses[i].amount);
            printf("Type (1 is fixed, 0 is variable): %d\n", (int) (*data).expenses[i].type);
            printf("-----------------------------------\n");
        }
    }
}

int monthlyExpenses(TData* data, int month){
    
    if (isEmpty(data)){
        printf("The list is empty.");
    }else{
        int counter = 0;

        for (int i = 0; i < (*data).elements; i++){
            if ((*data).expenses[i].date.month == month){
                counter += (*data).expenses[i].amount; 
            }else{
                continue;
            }
        }
        return counter;
    }   
}

int fixedExpenses(TData* data, int month){
    
    if (isEmpty(data)){
        printf("The list is empty.");
    }else{
        int counter = 0;
    
        for (int i = 0; i < (*data).elements; i++){
            if ((*data).expenses[i].type == 1 && (*data).expenses[i].date.month == month){
                counter += (*data).expenses[i].amount;
                showExpenses(data);
            }
        }
        return counter;
    }
}

int variableExpenses(TData* data, int month){
    
    if (isEmpty(data)){
        printf("The list is empty.");
    }else{
        int counter = 0;

        for (int i = 0; i < (*data).elements; i++){
            if ((*data).expenses[i].type == 0 && (*data).expenses[i].date.month == month){
                counter += (*data).expenses[i].amount;
                showExpenses(data);
            }    
        }
        return counter;
    }
}
