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

void getArray(char *puzzle, struct Node sudoku[MAX_LENGTH])
{
    for (int i = 0; i < MAX_LENGTH; i++)
    {
        int val = puzzle[i] - '0';
        if (val == 0)
        {
            sudoku[i].value = val;
            sudoku[i].isEdit = true;
        }
        else
        {
            sudoku[i].value = val;
            sudoku[i].isEdit = false;
        }
    }
}

void printSudoku(struct Node sudoku[MAX_LENGTH])
{
    for (int i = 0; i < MAX_LENGTH; i++)
    {
        printf("%d ", sudoku[i].value);
        if ((i + 1) % 9 == 0)
            printf("\n");
    }
}

bool checkRow(int value, int index, struct Node sudoku[MAX_LENGTH])
{

    int row_length = 9;
    if (value > row_length || value < 0 || index > MAX_LENGTH - 1 || index < 0)
    {
        fprintf(stderr, "Invalid potential value.\n");
        exit(EXIT_FAILURE);
    }
    int start = (index / row_length) * row_length;
    // printf("start %d\n", start);
    for (int i = start; i < start + row_length - 1; i++)
    {
        if (i == index)
            continue;
        if (sudoku[i].value == value)
            return false;
    }
    return true;
}

bool checkCol(int value, int index, struct Node sudoku[MAX_LENGTH])
{

    int col_length = 9;
    if (value > col_length || value < 0 || index > MAX_LENGTH - 1 || index < 0)
    {
        fprintf(stderr, "Invalid potential value.\n");
        exit(EXIT_FAILURE);
    }
    int col_position = index % col_length;
    for (int i = col_position; i < MAX_LENGTH; i += col_length)
    {
        if (i == index)
            continue;
        if (sudoku[i].value == value)
            return false;
    }

    return true;
}

bool checkBox(int value, int index, struct Node sudoku[MAX_LENGTH])
{

    int box_size = 9;
    int box_edge = 3;
    if (box_size > 9 || value < 0 || index > MAX_LENGTH - 1 || index < 0)
    {
        fprintf(stderr, "Invalid potential value.\n");
        exit(EXIT_FAILURE);
    }
    int row_position = index % box_size;
    int col_position = index / box_size;
    int box_row_start = (row_position / box_edge) * box_edge;
    int box_col_start = (col_position / box_edge) * box_edge;
    int start = (box_col_start * box_size) + box_row_start;

    for (int i = start; i < start + (box_size * box_edge); i += box_size)
    {
        int current_edge = i + box_edge;
        for (int j = i; j < current_edge; j++)
        {
            // printf("%d ", sudoku[j].value);
            if (j == index)
                continue;
            if (sudoku[j].value == value)
                return false;
        }
        // printf("\n");
    }
    return true;
}

void checkSudoku(struct Node sudoku[MAX_LENGTH])
{

    for (int i = 0; i < MAX_LENGTH; i++)
    {
        if (!sudoku[i].isEdit)
        {
            if (!checkRow(sudoku[i].value, i, sudoku) || 
                !checkCol(sudoku[i].value, i, sudoku) || 
                !checkBox(sudoku[i].value, i, sudoku))
            {
                fprintf(stderr, "Entered sudoku is invalid.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

void solve(struct Node sudoku[MAX_LENGTH])
{

    int max_value = 9;
    for (int i = 0; i < MAX_LENGTH; i++)
    {
        // printf("start: index %d value %d\n", i, sudoku[i].value);
        // printSudoku(sudoku);
        if (i < 0)
        {
            fprintf(stderr, "Puzzle is not solvable.\n");
            exit(EXIT_FAILURE);
        }
        if (sudoku[i].isEdit)
        {
            // printf("isEdit: index %d value %d\n", i, sudoku[i].value);
            bool value_found = false;
            if (sudoku[i].value == 0)
                sudoku[i].value = 1;
            for (int j = sudoku[i].value; j <= max_value; j++)
            {
                // printf("Incrementing: index %d value %d\n", i, j);
                // printf("checkRow %s checkCol %s checkBox %s\n", checkRow(j, i, sudoku) ? "true" : "false", checkCol(j, i, sudoku) ? "true" : "false", checkBox(j, i, sudoku) ? "true" : "false");
                if (checkRow(j, i, sudoku) && checkCol(j, i, sudoku) && checkBox(j, i, sudoku))
                {
                    sudoku[i].value = j;
                    value_found = true;
                    break;
                }
            }
            if (!value_found)
            {
                sudoku[i].value = 0;
                i--;
                while (!sudoku[i].isEdit)
                {
                    if (i < 0)
                    {
                        fprintf(stderr, "Puzzle is not solvable.\n");
                        exit(EXIT_FAILURE);
                    }
                    i--;
                }
                sudoku[i].value++;
                i--;
            }
        }
    }
}

void match(struct Node sudoku[MAX_LENGTH], char solution[MAX_LENGTH]){



}

int main()
{

    char puzzle[MAX_LENGTH+1];
    char solution[MAX_LENGTH+1];

    const char *filename = "test.txt";

    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        fprintf(stderr, "File could not be opened.\n");
        exit(EXIT_FAILURE);
    }

   while (fgets(puzzle, sizeof(puzzle), file) != NULL) {
        //printf("%s", puzzle);
        fgets(solution, sizeof(solution), file);
        //printf("%s", solution);
    }

    //printf("Enter the puzzle string:\n");
    //scanf("%81s", puzzle);
    // if (strlen(puzzle) != 81)
    // {
    //     fprintf(stderr, "Invalid puzzle string length.\n");
    //     exit(EXIT_FAILURE);
    // }
    // else
    // {
    //     printf("You entered: %s\n", puzzle);
    // }

    struct Node sudoku[MAX_LENGTH];
    struct Node sudoku_solution[MAX_LENGTH];
    getArray(puzzle, sudoku);
    printSudoku(sudoku);
    checkSudoku(sudoku);
    //printf("Initial Puzzle:\n");
    //printSudoku(sudoku);
    solve(sudoku);
    //printf("Solved Puzzle:\n");
    //printSudoku(sudoku);
    match(sudoku, solution);

    return 0;
}