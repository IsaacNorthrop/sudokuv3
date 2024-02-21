#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sudoku
{

    char *id;
    char *puzzle;
    char *solution;
    char *clues;
    char *difficult;
};

int main()
{

    const char *filename = "sudoku-3m.csv";
    const char *new_file = "right.csv";

    FILE *file = fopen(filename, "r");
    FILE *new = fopen(new_file, "a");

    if (file == NULL)
    {
        fprintf(stderr, "File could not be opened.\n");
        exit(EXIT_FAILURE);
    }

    char buffer[179];
    const char *delimiter = ",";
    char *token;

    fgets(buffer, sizeof(buffer), file);

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        token = strtok(buffer, delimiter);
        token = strtok(NULL, delimiter);
        int length = strlen(token);

        // printf("%s\n", token);
        for (int i = 0; i < length; i++)
        {
            if (token[i] == '.')
            {
                token[i] = '0';
            }
        }
        fprintf(new, "%s\n", token);

        token = strtok(NULL, delimiter);
        fprintf(new, "%s\n", token);
    }

    fclose(file);

    return 0;
}
