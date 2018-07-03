/*
 * binary_matrix_driver.c
 * Name / StudentID
 * A driver for binary_matrix.h
 * Reads a BinaryMatrix from stdin and prints it out
 */

#include <stdio.h>
#include <stdlib.h>

#include "binary_matrix.h"

int main() {
    int num_rows, num_cols, status, row, col, content;
    BinaryMatrix* M;

    printf("Testing ConstructBinaryMatrix and PrintMatrix\n");
    printf("Enter the number of rows: ");
    scanf("%d", &num_rows);
    printf("Enter the number of cols: ");
    scanf("%d", &num_cols);
    M = ConstructBinaryMatrix(num_rows, num_cols);
    do {
        printf("Enter the row, column, and content to modify the matrix (any other input to quit): ");
        status = scanf("%d", &row);
        status *= scanf("%d", &col);
        status *= scanf("%d", &content);
        UpdateEntry(M, row, col, content);   
    } while (status == 1);
    printf("Your matrix:\n");
    PrintMatrix(M);
    printf("Done testing ConstructBinaryMatrix and PrintMatrix\n");

    printf("Testing UpdateEntry\n");
    int new_value = (M->data[0][0] + 1) % 2;
    UpdateEntry(M, 0, 0, new_value);
    if (M->data[0][0] != new_value) {
        printf("Error testing UpdateEntry: value has not changed\n");
    }
    printf("Done testing UpdateEntry.\n");

    printf("Testing IsMatrixIndex\n");
    if (IsMatrixIndex(M, num_rows, num_cols)) {
        /* Testing out of bounds */
        printf("Error testing IsMatrixIndex: (%d,%d) should be out of bounds\n", row, col);
    }
    if (!IsMatrixIndex(M, 0, 0)) {
        /* Testing in bounds */
        printf("Error testing IsMatrixIndex: (0,0) should be in bounds\n");
    }
    printf("Done testing IsMatrixIndex.\n");
    
    printf("Testing DeleteBinaryMatrix\n");
    DeleteBinaryMatrix(M);
    printf("Done testing DeleteBinaryMatrix. You may wish to check this with valgrind as well.\n");    

    printf("Done running binary_matrix_driver. This does not gaurantee full points or that your code is bug-free.\n");
    return EXIT_SUCCESS;
}
