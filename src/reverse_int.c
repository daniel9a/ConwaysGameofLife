/*
 * reverese_int.c
 * Daniel Andrade 913211892
 * User is prompted to enter a number
 * Number is reveresed and given back to user
 * If not a number then user is prompted error
 */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



int main()
{
    //User prompted to enter a number  
    printf("Enter a number to reverse: ");

    //declared variables
    char user_int[100], reversed[100];
    int length, reverse = 0;
    int reversed_integer, initial=0;

    //adds characters to the user input
    while((user_int[length] = getchar()) != '\n'){
        length++;
    }
    
    //if the user inputs nothing then an error is prompted to the user
    if (user_int[0] == '\n'){
        printf("Error: no digits have been read. \n");
        exit(EXIT_FAILURE);}
    
    //position starts at 0
    for(int q=0; q<length; q++){
        
	//if it is not a negative it checks each character to see if it is a digit 
        if(user_int[q] != '-' && !(isdigit(user_int[q]))) {
                
		//if there is a non-digit than error code is given to the user
                printf("Error: non-digit character entered\n");
                exit(EXIT_FAILURE);}
                }
    
    //if the first entry is a negative then it enters a negative at the beginning
    if (user_int[initial] == '-'){
        printf("-");
        }
    
    //going from end to 0
    while (initial<=length){
        
	//array is copied backwards and reversed into new array
        reversed[reverse] = user_int[length-1];
        ++reverse;
        --length;}
    
    //makes it into an integer
    sscanf(reversed, "%d", &reversed_integer);
    
    //prints the number in reverse
    printf("%d\n", reversed_integer);
    return(EXIT_SUCCESS);
}

