#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 31 //name length max


//Definitions
void countNames(char *filename);
CommandNode* addName(CommandNode *head, char *name);
void printNames(CommandNode *head);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "error: expecting exactly 1 file as input\n");
        return 1;
    }

    countNames(argv[1]);

    return 0;
}

void countNames(char *filename) {

    //Check if file is openable
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(1);
    }


    //initialize list, create a buffer to temporarily hold lines, and a line number holder
    CommandNode *head = NULL;
    char buffer[MAX_NAME_LENGTH];
    int lineNum = 0;

    //keep going until all has been read
    while (fgets(buffer, MAX_NAME_LENGTH, file)) {
        lineNum++;
        //remove new line
        buffer[strcspn(buffer, "\n")] = 0;
        //prompt if line is empty, continue
        if (strlen(buffer) == 0) {
            fprintf(stderr, "Warning - Line %d is empty.\n", lineNum);
            continue;
        }

        head = addName(head, buffer);
    }

    printNames(head);
    fclose(file);

    // Free the allocated memory for the list
    CommandNode *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
}
//adds name/increases count
CommandNode* addName(CommandNode *head, char *name) {
        CommandNode *current = head;
        CommandNode *last = NULL;

        //while there is still a value/list ends
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            current->count++;
            return head;
        }
        last = current; // Keep track of the last node
        current = current->next;
    }

    // If the name was not found, add it
    CommandNode *newNode = (CommandNode *)malloc(sizeof(CommandNode));
    strcpy(newNode->name, name);
    newNode->count = 1;
    newNode->next = NULL;

    if (last == NULL) {
        return newNode; // List was empty, new node is now the head
    } else {
        last->next = newNode; // Append new node to the end
    }
    return head;
}

    //prints names
void printNames(CommandNode *head) {
    CommandNode *current = head;
    while (current != NULL) {
        printf("%s: %d\n", current->name, current->count);
        current = current->next;
    }
}
}
