/* primefactors2.c
 *
 * CS-5008 Summer 2026
 * Dan Liu
 * 
 * Asks the user for an integer and prints the prime factorization of that integer.
 * Factors should be printed in increasing order, separated by "*".
 * 
 * For example:
 *  Enter a number: 180
 *  The prime factors are 2 * 2 * 3 * 3 * 5
 * 
 * Uses a recursive function.
 */

#include <stdio.h>

/* 
 * Recursively prints the prime factors of number, separated by " * ". 
 * Each call finds the smallest prime factor of the current number, prints it, 
 * and recurses on the quotient.
 */
void printPrimeFactors(int number) {
    
    // Check for factors starting from 2 up to the square root of the number
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) {
            printf("%d", i);
            // If there is more to factor, print " * " and recurse
            if (number / i > 1) {
                printf(" * ");
                printPrimeFactors(number / i);
            }
            return; 
        }
    }
    
    // If no factors found, number is prime
    printf("%d", number); 
}

/* Main function to run the program */
int main() {
    char s[100];
    int number;

    // Ask the user to input an integer
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        printf("Error: Invalid input. Please enter an integer.\n");
        return 1; 
    }
    fgets(s, 100, stdin); // Clear the input buffer

    // Validate the input number
    if (number < 2) {
        printf("%d has no prime factors.\n", number);
        return 0;
    }

    // Call the recursive function to print prime factors
    printf("The prime factors are ");
    printPrimeFactors(number); 
    printf("\n");

    // Wait for user input before exiting
    fgets(s, 100, stdin); 
    return 0;          
}