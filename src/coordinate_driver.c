/*
 * coordinate_driver.c
 * Name / StudentID
 * A driver for coordinate.h
 * Tests the various coordinate functions prototyped in coordinate.h and implemented in coordinate.c
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "coordinate.h"

int main() {
    int x, y, error = 0;
    Coordinate C, D;
    /* Test ConstructCoordinate */
    printf("Testing ConstructCoordinate. Enter a coordinate: ");
    if (scanf("%d %d", &x, &y) != 2) {
        printf("Error reading two digits. Aborting\n");
        exit(EXIT_FAILURE);
    }
    C = ConstructCoordinate(x, y);
    printf("The distance from the origin to your coordinate is %lf\n", sqrt(C.x*C.x + C.y*C.y));
    printf("Done testing ConstructCoordinate.\n");

    /* Test IsNeighbor */
    printf("Testing IsNeighbor.\n");
    if (IsNeighbor(C, C)) {
        /* A coordinate is not its own neighbor */
        printf("Error in IsNeighbor: a coordinate is not its own neighbor.\n");
        error = 1;
    }
    if (IsNeighbor(ConstructCoordinate(0, 0), ConstructCoordinate(2, 2))) {
        /* These coordinates are too far */
        printf("Error in IsNeighbor: (0,0) and (2,2) are not neighbors.\n");
        error = 1;
    }
    if (!IsNeighbor(ConstructCoordinate(0, 0), ConstructCoordinate(0, 1))) {
        /* Test neighbors */
        printf("Error in IsNeighbor: (0,0) and (0,1) are neighbors.\n");
        error = 1;
    }
    if (!IsNeighbor(ConstructCoordinate(0, 0), ConstructCoordinate(1, 1))) {
        /* Test diagonal neighbors */
        printf("Error in IsNeighbor: (0,0) and (1,1) are neighbors.\n");
        error = 1;
    }
    printf("Done testing IsNeighbor.\n");

    printf("Testing SwapCoordinates.\n");
    D = ConstructCoordinate(C.x, C.y);
    SwapCoordinates(&D);
    if (C.x != D.y || C.y != D.x) {
        printf("Error in SwapCoordinates, check your results.\n");
        error = 1;
    }
    printf("Done testing SwapCoordinates.\n");

    if (!error) {
        printf("No errors found. This does not gaurantee a full score, but you have passed all the tests in coordinate_driver. Congratulations!\n");
    }

    return EXIT_SUCCESS;
}
