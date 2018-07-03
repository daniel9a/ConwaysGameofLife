/*
 * binary_matrix.c
 * Daniel Andrade 913211982
 * An implementation of a Binary Matrix
 */


#include "binary_matrix.h"

#include <stdio.h>
#include <stdlib.h>

/*
 * Input:
 *      int num_rows, the number of rows of matrix
 *      int num_cols, the number of cols of matrix
 * Output:
 *      Return a BinaryMatrix*
 * Summary:
 *      Creates a Matrix
 */

BinaryMatrix *ConstructBinaryMatrix(int num_rows, int num_cols) {

	BinaryMatrix *result = (BinaryMatrix *) malloc(sizeof(BinaryMatrix));

	result->num_rows = num_rows;
	result->num_cols = num_cols;
	result->data = (int **) malloc(sizeof(int *) * num_rows);

	int i, j;
	for (i = 0; i < num_rows; i++) {
		result->data[i] = (int *) malloc(num_rows * sizeof(int));
		for (j = 0; j < num_cols; j++) {
			result->data[i][j] = 0;
		}
	}

	if (!(num_rows > 0) && !(num_cols > 0)) {
		printf("Error in CreateMatrix: number of rows and columns must be positive");
		exit(EXIT_FAILURE);
	}

	return result;
}

 
/*
 * Input:
 *      num_rows
 * Output:
 *      Free everything
 * Summary:
 *      Deallocates the memory used for *M
 */

void DeleteBinaryMatrix(BinaryMatrix * M)
{

	for (int i = 0; i < M->num_rows; i++) {
		free(M->data[i]);
	}
	free(M->data);	
	free(M);
}


/*
 * Input:
 *      int row
 *      int col
 *      int content
 * Output:
 *      If row and col are not valid indicies for *M return error message and exit program
 *      If content is not a 0 or 1 return error message and exit program
 * Summary:
 *      Updates (row, col) entry with content
 */

void UpdateEntry(BinaryMatrix * M, int row, int col, int content)
{
	if (!(IsMatrixIndex(M, row, col))) {
		printf("Error in UpdateEntry: index out of bounds\n");
		exit(EXIT_FAILURE);
	}
	if (!(content == 0 || content == 1)) {
		printf("Error in UpdateEntry: content must be 0 or 1\n");
		exit(EXIT_FAILURE);
	}

	M->data[row][col] = content;
}


/*
 * Input:
 *      BinaryMatrix* M
 *      int row
 *      int col
 *      int content
 * Output:
 *      Returns true if row and col are valid indicies for *M and false otherwise
 *      Checks that *M is not NULL and if it is print error message
 * Summary:
 *      Reads if else statements
 */

int IsMatrixIndex(BinaryMatrix * M, int row, int col)
{
	if (M == NULL) {		
		printf("IsMatrixIndex Error: NULL parameter passed\n");
		exit(EXIT_FAILURE);
	}

	if (!(col <= M->num_cols - 1)) {
		return 0;
	}
	if (!(row <= M->num_rows - 1)) {
		return 0;
	}
	if (col < 0) {
		return 0;
	}
	if (row < 0) {
		return 0;
	}
	return 1;
}


/*
 * Input:
 *      BinaryMatrix* M
 * Output:
 *      Prints entry
 * Summary:
 *      Prints entries of *M
 */

void PrintMatrix(BinaryMatrix * M)
{

	int i, j;
	for (i = 0; i < M->num_rows; i++) {
		for (j = 0; j < M->num_cols; j++) {
			printf("%d", (M->data[i][j]));
		}
		printf("\n");
	}
}
