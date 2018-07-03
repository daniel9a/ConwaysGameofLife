/*
 * comways_game_of_life.h
 * Name / StudentID
 * A data structure moedling 2D integer Carteresian Coordinate
 */

#ifndef _CONWAYS_GAME_OF_LIFE_H_
#define _CONWAYS_GAME_OF_LIFE_H_ 


#include <stdio.h>
#include <stdlib.h>

#include "binary_matrix.h"
//#include "coordinate.h"
#include "list.h"

BinaryMatrix* FirstGeneration(int num_rows, int num_cols, List* seed_cells); 

//BinaryMatrix* FirstGeneration(int num_rows, int num_cols, List* seed_cells); 

BinaryMatrix* NextGeneration(BinaryMatrix* generation);

int Live(BinaryMatrix* generation, Coordinate coord);

List* NeighboringCells(Coordinate coord, BinaryMatrix* generation);

int LivingNeighbors(BinaryMatrix* generation, List* neighbors);

void PrintGeneration(BinaryMatrix* generation, FILE* fp);

#endif /*CONWAYS_GAME_OF_LIFE_H_*/
