/*
 * binary_matrix.h
 * Name / StudentID
 * An implementation of a Binary Matrix
 */

#ifndef _BINARY_MATRIX_H_
#define _BINARY_MATRIX_H_


typedef struct {
	int num_rows;
	int num_cols;
	int** data;
} BinaryMatrix;


BinaryMatrix* ConstructBinaryMatrix(int num_rows, int num_cols); 
 

void DeleteBinaryMatrix(BinaryMatrix* M); 


void UpdateEntry(BinaryMatrix* M, int row, int col, int content);


int IsMatrixIndex(BinaryMatrix* M, int row, int col); 


void PrintMatrix(BinaryMatrix* M); 

#endif /*_BINARY-MATRIX-H- */           
