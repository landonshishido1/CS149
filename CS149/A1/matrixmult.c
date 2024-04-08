/**
 * Description: This module implements matrix operations on matrices and vectors.... It returns a vector...
 * Author names: Landon Shishido
 * Author emails: landonbusiness1@gmail.com
 * Last modified date:2/14/2024
 * Creation date: 2/10/2024
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define A_ROWS 1
#define A_COLS 3
#define W_ROWS 3
#define W_COLS 5
#define B_ROWS 1
#define B_COLS 5

//methods to read, multiply, add, and print
void readMatrix(const char *filename, int rows, int cols, int matrix[rows][cols]);

void matrixMult(int rows, int cols, int matrix[rows][cols], int rows2, int cols2, int matrix2[rows2][cols2],
                int result[rows][cols2]);

void matrixAdd(int rows, int cols, int matrix[rows][cols], int matrix2[rows][cols], int result[rows][cols]);

void printMatrix(int rows, int cols, int matrix[rows][cols]);

int main(int argc, char *argv[]) {
    //if there is != 4 arguments, result in error
    if (argc != 4) {
        fprintf(stderr, "error: expecting exactly 3 files as input\n");
        printf("Terminating, exit code 1.\n");
        return 1;
    }

    //Create Blank Matrices with the predetermined size, all values start as 0
    int A[A_ROWS][A_COLS] = {0};
    int W[W_ROWS][W_COLS] = {0};
    int B[B_ROWS][B_COLS] = {0};

    //Read the matrix values into the created matrices
    readMatrix(argv[1], A_ROWS, A_COLS, A);
    readMatrix(argv[2], W_ROWS, W_COLS, W);
    readMatrix(argv[3], B_ROWS, B_COLS, B);

//multiply A and W and store into multResult
    int multResult[A_ROWS][W_COLS] = {0};
    matrixMult(A_ROWS, A_COLS, A, W_ROWS, W_COLS, W, multResult);

    //add multResult and B into addResult
    int addResult[B_ROWS][B_COLS] = {0};
    matrixAdd(B_ROWS, B_COLS, B, multResult, addResult);

    //print result and return 0
    printf("Result of %s*%s+%s = [", argv[1], argv[2], argv[3]);
    printMatrix(B_ROWS, B_COLS, addResult);
    printf("]\n");
    return 0;
}

void readMatrix(const char *filename, int rows, int cols, int matrix[rows][cols]) {
    //read the file, if not return an error message
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "error: cannot open file %s\n", filename);
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    char *token;
    int i = 0, j = 0;

    // Initialize the matrix with 0s
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            matrix[i][j] = 0;
        }
    }
//read in all tokens(ints)
    i = 0;
    while (fgets(line, sizeof(line), file)) {
        j = 0;
        token = strtok(line, " \t\n");
        while (token != NULL && j < cols) {
            matrix[i][j++] = atoi(token);
            token = strtok(NULL, " \t\n");
        }
        i++;
        if (i >= rows) break; // Stop if we have read enough rows
    }

}

void printMatrix(int rows, int cols, int matrix[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
    }
}

void matrixMult(int rows, int cols, int matrix[rows][cols], int rows2, int cols2, int matrix2[rows2][cols2],
                int result[rows][cols2]) {
    // Initialize the result matrix with 0
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols2; j++) {
            result[i][j] = 0;
        }
    }

    //multiplication
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols2; j++) {
            for (int k = 0; k < cols; k++) {
                result[i][j] += matrix[i][k] * matrix2[k][j];
            }
        }
    }
}

void matrixAdd(int rows, int cols, int matrix[rows][cols], int matrix2[rows][cols], int result[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix[i][j] + matrix2[i][j];
        }
    }
}