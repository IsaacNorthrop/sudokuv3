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

bool checkRow(int value, int index, struct Node sudoku[MAX_LENGTH]){

    int row_length = 9;
    if(value > row_length || value < 0 || index > MAX_LENGTH-1 || index < 0){
        fprintf(stderr, "Invalid potential value.\n");
        exit(EXIT_FAILURE);
    }    
    int start = (index / row_length)*row_length;
    printf("start %d\n", start);
    for(int i = start; i<start+row_length-1; i++){
        if(sudoku[i].value ==  value)
            return false;
    }
    return true;

}

bool checkCol(int value, int index, struct Node sudoku[MAX_LENGTH]){

    int col_length = 9;
    if(value > col_length || value < 0 || index > MAX_LENGTH-1 || index < 0){
        fprintf(stderr, "Invalid potential value.\n");
        exit(EXIT_FAILURE);
    }
    int col_position = index % col_length;
    for(int i = col_position; i<MAX_LENGTH; i+=col_length){
        if(sudoku[i].value ==  value)
        return false;
    }

    return true;

}

bool checkBox(int value, int index, struct Node sudoku[MAX_LENGTH]){

    int box_size = 9;
    int box_edge = 3;
    if(box_size > 9 || value < 0 || index > MAX_LENGTH-1 || index < 0){
        fprintf(stderr, "Invalid potential value.\n");
        exit(EXIT_FAILURE);
    }
    int row_position = index % box_size;
    int col_position = index / box_size;
    int box_row_start = (row_position / box_edge)*box_edge;
    int box_col_start = (col_position / box_edge)*box_edge;
    int start = (box_col_start*box_size)+box_row_start;

    for(int i = start; i<start+(box_size*box_edge); i+=box_size){
        int current_edge = i + box_edge;
        for(int j = i; j<current_edge; j++){
            printf("%d ", sudoku[j].value);
            if(sudoku[j].value ==  value)
            return false;
        }
        printf("\n");
    }
    return true;

}

void solve(struct Node sudoku[MAX_LENGTH]){

    if(checkBox(4, 40, sudoku) == false){
        printf("fuck\n");
    } else {
        printf("shit\n");
    }
    //checkCol();
    //checkBox();

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
    printf("Initial Puzzle:\n");
    printSudoku(sudoku);
    solve(sudoku);

    return 0;
}