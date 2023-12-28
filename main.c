#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 81

struct Node{
    int value;
    struct Node* next;
    struct Node* prev;
    bool isEdit;

};

struct Node* initNode(int value, bool isEdit){
    struct Node* new = (struct Node*)malloc(sizeof(struct Node));
    if(new == NULL){
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    new->value = value;
    new->next = NULL;
    new->prev = NULL;
    new->isEdit = isEdit;
    return new;
}

struct Node* listify(char* puzzle){
    struct Node* head;

    for(int i = MAX_LENGTH-1; i>=0; i--){
        struct Node* new;
        int val = puzzle[i] - '0';
        if(val == 0){
            new = initNode(val, true);
        } else if(val < 0){
            fprintf(stderr, "Invalid entry.\n");
            exit(EXIT_FAILURE);
        } else{
            new = initNode(val, false);
        }
        struct Node* temp;
        temp = head;
        temp->prev = new;
        new->next = head;
        head = new;
    }

    return head;

}

void printList(struct Node** head){
    struct Node* curr = initNode(-1, false);
    curr = *head;
    for(int i = 0; i<MAX_LENGTH; i++){
        printf("%d", curr->value);
        curr = curr->next;
    }
    printf("\n");
}

void printSudoku(struct Node** head){
    struct Node* curr = initNode(-1, false);
    curr = *head;
    for(int j = 0; j<MAX_LENGTH/9; j++){
        for(int i = 0; i<MAX_LENGTH/9; i++){
            printf("%d ", curr->value);
            curr = curr->next;
        }
        printf("\n");
    }
}

void solve(struct Node** head){

    struct Node* curr = initNode(-1, false);
    curr = *head;
    while(curr->next != NULL){
        printf("%d", curr->value);
        curr = curr->next;
    }
    printf("\n");

}

int main(){

    char puzzle[MAX_LENGTH];
    printf("Enter the puzzle string:\n");
    scanf("%81s", puzzle);
    if(strlen(puzzle) != 81){
        fprintf(stderr, "Invalid puzzle string length.\n");
        exit(EXIT_FAILURE);
    } else {
        printf("You entered: %s\n", puzzle);
    }

    struct Node* head = listify(puzzle);
    printList(&head);
    printf("Starting Sudoku:\n");
    printSudoku(&head);
    solve(&head);
    printf("Solved Sudoku:\n");
    printSudoku(&head);

    return 0;
}