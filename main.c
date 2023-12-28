#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 81

struct Node
{
    int value;
    bool isEdit;
};

struct Node *initNode(int value, bool isEdit)
{
    struct Node *new = (struct Node *)malloc(sizeof(struct Node));
    if (new == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    new->value = value;
    new->isEdit = isEdit;
    return new;
}

void getArray(char *puzzle, struct Node sudoku[MAX_LENGTH])
{
    for (int i = 0; i < MAX_LENGTH; i++)
    {
        int val = puzzle[i] - '0';
        if (val == 0)
        {
            sudoku[i].value = val;
            sudoku[i].isEdit = false;
        }
        else
        {
            sudoku[i].value = val;
            sudoku[i].isEdit = true;
        }
    }
}

void printSudoku(struct Node sudoku[MAX_LENGTH])
{
    for (int i = 0; i < MAX_LENGTH; i++)
    {
        printf("%d ", sudoku[i].value);
        if((i+1)%9 == 0)
            printf("\n");
    }
}

int main()
{

    char puzzle[MAX_LENGTH];
    printf("Enter the puzzle string:\n");
    scanf("%81s", puzzle);
    if (strlen(puzzle) != 81)
    {
        fprintf(stderr, "Invalid puzzle string length.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("You entered: %s\n", puzzle);
    }

    struct Node sudoku[MAX_LENGTH];
    getArray(puzzle, sudoku);
    printSudoku(sudoku);

    return 0;
}