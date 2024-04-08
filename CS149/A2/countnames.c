4#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#define MAX_NAMES 100
#define MAX_NAME_LENGTH 31  // 30 characters + null terminator


//type structure
typedef struct {
    char name[MAX_NAME_LENGTH];
    int count;
} NameCount;

// Function prototypes
void countNames(char *filename);

int addOrUpdateName(NameCount names[], int *size, char *name);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "error: expecting exactly 1 file as input\n");
        return 1;
    }

    countNames(argv[1]);

    return 0;
}

void countNames(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(1);
    }

    NameCount names[MAX_NAMES] = {0};
    int size = 0;
    char buffer[MAX_NAME_LENGTH];
    int lineNum = 0;

    while (fgets(buffer, MAX_NAME_LENGTH, file)) {
        lineNum++;
        // Remove newline character, if present
        buffer[strcspn(buffer, "\n")] = 0;

        if (strlen(buffer) == 0) {
            fprintf(stderr, "Warning - Line %d is empty.\n", lineNum);
            continue;
        }

        addOrUpdateName(names, &size, buffer);
    }

    // Print the counts
    for (int i = 0; i < size; i++) {
        printf("%s: %d\n", names[i].name, names[i].count);
    }

    fclose(file);
}

int addOrUpdateName(NameCount names[], int *size, char *name) {
    for (int i = 0; i < *size; i++) {
        if (strcmp(names[i].name, name) == 0) {
            names[i].count++;
            return i;
        }
    }

    // If the name was not found, add it
    if (*size < MAX_NAMES) {
        strncpy(names[*size].name, name, MAX_NAME_LENGTH - 1);
        names[*size].name[MAX_NAME_LENGTH - 1] = '\0'; // Ensure null termination
        names[*size].count = 1;
        (*size)++;
    }

    return *size - 1;
}