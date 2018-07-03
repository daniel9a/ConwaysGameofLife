/*
 * coordinate.h
 * Daniel Andrade 913211982
 * A data structure modeling 2D integer Cartesian Coordinates
 */


#include "coordinate.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Input:
 * 	int x, an x-coordinate
 * 	int y, a y-coordinate
 * Output;
 * 	A coordinate
 * Summary:
 * 	Initializes a Coordinate to (x, y)
 */

Coordinate ConstructCoordinate(int x, int y) {

	Coordinate output;

	output.x = x;
	output.y = y;
	
	return output; 
}


/*
 * Input:
 * 	Coordinate C1, a coordinate
 * 	Coordinate C2, another coordinate
 * Output:
 * 	true if C2 is a neighbor of C1, false otherwise
 * Summary:
 * 	Checks if C1 and C2 are neighbors, that is, if they
 * 	are in adjacent squares (including squares that are
 * 	diagonally adjacent) and not equal
 */

int IsNeighbor(Coordinate C1, Coordinate C2) {

	int distance;
		
	distance = sqrt(pow((C1.x - C2.x), 2) + pow((C1.y - C2.y), 2));


	if(distance <= sqrt(2) && distance != 0){
		return 1;
	}
	else{
		return 0;
	}
}

/*
 * Input:
 *      Coordinate* C, a pointer to a Coordinate
 * Summary:
 *      Swaps the entries of the Coordinate pointed to by C
 */

void SwapCoordinates(Coordinate* C) {

	int temp;
	temp = C->x;
	C->x = C->y;
	C->y = temp;	
}
