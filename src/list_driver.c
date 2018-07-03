/*
 * list_driver.c
 * Name / StudentID
 * A driver for list.h
 * Reads Coordinates from stdin into a List and prints them out
 */

#include <stdio.h>
#include <stdlib.h>

#include "coordinate.h"
#include "list.h"

int main() {
    int status;
    Coordinate C;
    List* list = ConstructList();
    printf("Enter a coordinate to add to the list, or a non-coordinate to quit: ");
    status = scanf("%d", &C.x);
    status *= scanf("%d", &C.y);
    while (status == 1) {
        PushFrontList(list, C);
        printf("Enter a coordinate to add to the list, or a non-coordinate to quit: ");
        status = scanf("%d", &C.x);
        status *= scanf("%d", &C.y);
    }
    PrintList(list);
    DeleteList(list);
    return EXIT_SUCCESS;
}
