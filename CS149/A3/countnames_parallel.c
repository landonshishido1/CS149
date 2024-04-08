#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ENTRIES 100
#define NAME_BUF_SIZE 31

typedef struct {
    char entryName[NAME_BUF_SIZE];
    int occurrences;
} EntryCounter;

void processFileEntries(char *filePath, int pipeWriteEnd);

int updateOrAddEntry(EntryCounter entries[], int *currentSize, const char *entryName, int occurrenceCount);

//read files

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: ./entry_counter file1 [file2 ...]\n");
        return 1;
    }
//initiliaze
    int fileCount = argc - 1;
    int entryPipes[fileCount][2];

    //pipe error

    for (int i = 0; i < fileCount; i++) {
        if (pipe(entryPipes[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < fileCount; i++) {
        pid_t procId = fork();
        if (procId == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (procId == 0) {
            close(entryPipes[i][0]);
            processFileEntries(argv[i + 1], entryPipes[i][1]);
            close(entryPipes[i][1]);
            exit(EXIT_SUCCESS);
        } else {
            close(entryPipes[i][1]);
        }
    }

    EntryCounter allEntries[MAX_ENTRIES] = {0};
    int totalEntries = 0;

    for (int i = 0; i < fileCount; i++) {
        int procStatus;
        waitpid(-1, &procStatus, 0);

        EntryCounter readEntry;
        while (read(entryPipes[i][0], &readEntry, sizeof(EntryCounter)) == sizeof(EntryCounter)) {
            updateOrAddEntry(allEntries, &totalEntries, readEntry.entryName, readEntry.occurrences);
        }
        close(entryPipes[i][0]);
    }

    for (int i = 0; i < totalEntries; i++) {
        printf("%s: %d\n", allEntries[i].entryName, allEntries[i].occurrences);
    }

    return 0;
}

void processFileEntries(char *filePath, int pipeWriteEnd) {
    FILE *fileStream = fopen(filePath, "r");
    if (!fileStream) {
        fprintf(stderr, "Error: cannot open file %s\n", filePath);
        exit(1);
    }

    EntryCounter entries[MAX_ENTRIES] = {0};
    int currentSize = 0;
    char nameBuffer[NAME_BUF_SIZE];

    while (fgets(nameBuffer, NAME_BUF_SIZE, fileStream)) {
        nameBuffer[strcspn(nameBuffer, "\n")] = 0;
        if (strlen(nameBuffer) > 0) {
            updateOrAddEntry(entries, &currentSize, nameBuffer, 1);
        }
    }

    if (write(pipeWriteEnd, entries, currentSize * sizeof(EntryCounter)) != currentSize * sizeof(EntryCounter)) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    fclose(fileStream);
}

//insert
int updateOrAddEntry(EntryCounter entries[], int *currentSize, const char *entryName, int occurrenceCount) {
    for (int i = 0; i < *currentSize; i++) {
        if (strcmp(entries[i].entryName, entryName) == 0) {
            entries[i].occurrences += occurrenceCount;
            return i;
        }
    }
//while not full
    if (*currentSize < MAX_ENTRIES) {
        strncpy(entries[*currentSize].entryName, entryName, NAME_BUF_SIZE - 1);
        entries[*currentSize].entryName[NAME_BUF_SIZE - 1] = '\0';
        entries[*currentSize].occurrences = occurrenceCount;
        (*currentSize)++;
        return *currentSize - 1;
    }

    fprintf(stderr, "Error: Maximum number of unique entries exceeded.\n");
    exit(EXIT_FAILURE);
}
