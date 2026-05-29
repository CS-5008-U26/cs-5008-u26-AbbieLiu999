/* primefactors.c
 *
 * CS-5008 Summer 2026
 * Dan Liu
 * 
 * Asks the user for an integer and prints the prime factorization of that integer.
 * Factors should be printed in increasing order, separated by "*".
 * 
 * For example:
 *   Enter a number: 180
 *   The prime factors are 2 * 2 * 3 * 3 * 5
 * 
 * Uses iteration without any function calls.
 */

#include <stdio.h>

int main() {
    char s[100]; 
    int number; 

    // Ask the user to input an integer
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        printf("Error: Invalid input. Please enter an integer.\n");
        return 1; // Exit with an error code
    }
    fgets(s, 100, stdin); // Clear the input buffer
    
    // Validate the input number
    if (number < 2) {
        printf("%d has no prime factors.\n", number);
        return 0; 
    }
    
    printf("The prime factors are ");
    
    // Check for factors starting from 2 up to the square root of the number
    for (int i = 2; i * i <= number; i++) {
        while (number % i == 0) {
            printf("%d", i);
            number /= i; // Get the next number to factor
            if (number > 1) {
                printf(" * ");
            }
        }
    }

    // Print the last prime factor if it's greater than 1
    if (number > 1) {
        printf("%d", number); 
    }
    printf("\n");

    // Wait for user input before exiting
    fgets(s, 100, stdin); 
    return 0;          
}


    



   