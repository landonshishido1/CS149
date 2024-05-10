/**
 * Program: Assignment 6
 * Description: Using data from child process along with parent
 * Author: Landon Shishido
 * Email: landon.shishido@sjsu.edu
 * Creation Date: May 4, 2024
 * Last Modified Date: May 6, 2024

 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#define TABLE_SIZE 100
#define MAX_NAME_LENGTH 32

pthread_mutex_t tlock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tlock3 = PTHREAD_MUTEX_INITIALIZER;

typedef struct Node {
    char name[MAX_NAME_LENGTH];
    int count;
    struct Node *next;
} Node;

int logindex=0;
Node* hashTable;

unsigned long calculateHash(char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // slight change in hash formula
    return hash % TABLE_SIZE;
}

void addName(char *name, int count) {
    pthread_mutex_lock(&tlock3);

    unsigned long index = calculateHash(name);
    Node *list = &hashTable[index];

    while (list->next != NULL) {
        if (strcmp(list->name, name) == 0) {
            list->count += count;
            pthread_mutex_unlock(&tlock3);
            return;
        }
        list = list->next;
    }

    if (strcmp(list->name, name) == 0) {
        list->count += count;
    } else {
        Node *newNode = (Node *)malloc(sizeof(Node));
        strncpy(newNode->name, name, MAX_NAME_LENGTH - 1);  // changed from strcpy to strncpy for safety
        newNode->count = count;
        newNode->next = NULL;
        list->next = newNode;
    }
    pthread_mutex_unlock(&tlock3);
}

void logMessage(char *message, int index) {
    pthread_mutex_lock(&tlock1);

    time_t now;
    time(&now);
    struct tm *local = localtime(&now);

    int hours = local->tm_hour;
    int minutes = local->tm_min;
    int seconds = local->tm_sec;
    int day = local->tm_mday;
    int month = local->tm_mon + 1;
    int year = local->tm_year + 1900;

    if (hours < 12)
        printf("Logindex %d, thread %lu, PID %d, %02d/%02d/%d %02d:%02d:%02d am: %s\n",
               index, (unsigned long)pthread_self(), getpid(), day, month, year, hours, minutes, seconds, message);
    else
        printf("Logindex %d, thread %lu, PID %d, %02d/%02d/%d %02d:%02d:%02d pm: %s\n",
               index, (unsigned long)pthread_self(), getpid(), day, month, year, hours % 12, minutes, seconds, message);

    fflush(stdout);
    pthread_mutex_unlock(&tlock1);
}

void* processFile(void* filename) {
    FILE *fp = fopen((char *)filename, "r");
    if (!fp) {
        fprintf(stderr, "Error: unable to open file %s\n", (char *)filename); // Slightly changed error message
        return NULL;
    }
    pthread_mutex_lock(&tlock1);
    int index = logindex++;
    pthread_mutex_unlock(&tlock1);

    logMessage("opened file", index);

    char name[MAX_NAME_LENGTH];
    int lineNumber = 1;

    while (fgets(name, MAX_NAME_LENGTH, fp) != NULL) {
        if (name[strlen(name)-1] == '\n')
            name[strlen(name)-1] = '\0';

        if (strlen(name) == 0) {
            fprintf(stderr, "Warning - file %s line %d is blank.\n", (char *)filename, lineNumber);  // changed "empty" to "blank"
        } else {
            addName(name, 1);
        }
        lineNumber++;
    }

    fclose(fp);
    return NULL;
}

void clearHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = hashTable[i].next;
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hashTable);
}

void displayResults() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = &hashTable[i];
        while (current->next != NULL) {
            if (current->count > 0)
                printf("%s: %d\n", current->name, current->count);
            current = current->next;
        }
        if (current->count > 0)
            printf("%s: %d\n", current->name, current->count);
    }
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Error: No files provided.\n");  // Changed the error message
        return 0;
    }

    hashTable = (Node *)calloc(TABLE_SIZE, sizeof(Node));

    pthread_t threads[argc-1];
    for (int i = 0; i < argc-1; i++) {
        pthread_create(&threads[i], NULL, processFile, (void *)argv[i+1]);
    }
    for (int i = 0; i < argc-1; i++) {
        pthread_join(threads[i], NULL);
    }

    displayResults();
    clearHashTable();

    return 0;
}
