/* complement.c
 *
 * CS-5008 Summer 2026
 * Dan Liu
 * 
 * Asks for an integer and prints the 10's complement of that integer.
 * The 10's complement is defined by substituting for each digit, 9 - that digit.  
 * For example, the 10's complement of 123 is 876.
 * 
 * Uses a recursive function.
*/

#include <stdio.h>

/*
 * Calculates the 10's complement of a given integer using recursion.
 * @param number: The integer for which to calculate the complement.
 * @return: The 10's complement of the input integer.
 */
int complement(int number) {

    // Base case: single digit, the complement is 9 - that digit
    if (number < 10) {
        return 9 - number;
    } 

    // Recursive case: strip the rightmost digit, complement the rest,
    // then shift left and add the complement of the rightmost digit
    int rightMost = number % 10;
    int restComplement = complement(number / 10);
    int rightMostComplement = 9 - rightMost;
    return restComplement * 10 + rightMostComplement;
}

/*
 * Main function to run the program.
 */
int main () {
    char s[100];
    int number;

    // Ask the user to input an integer
    printf("Enter an integer: ");
    
    // Validate the input to ensure it's an integer
    if (scanf("%d", &number) != 1) {
        printf("Error: Invalid input. Please enter an integer.\n");
        return 1; // Exit with an error code
    }
    fgets(s, 100, stdin); // Clear the input buffer

    // Validate the input to ensure it's a non-negative integer
    if (number < 0) {
        printf("Error: Negative numbers are not supported.\n");
        return 1; // Exit with an error code
    }

    // Calculate and print the 10's complement
    printf("The complement is %d\n", complement(number));

    // Wait for user input before exiting
    fgets(s, 100, stdin);
    return 0; 
}