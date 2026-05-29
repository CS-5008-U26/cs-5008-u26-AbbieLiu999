/* relative.c
 *
 * CS-5008 Summer 2026
 * Dan Liu
 * 
 * Accepts an integer n, then prints the ET-function for each integer from 2 to n.
 * The ET-function int et(x) is the number of integers less than x, that are relatively prime with x. 
 * Two numbers are relatively prime if they have no factors in common other than 1. 
 */
#include <stdio.h>

/*
 * The helper function gcd(a, b) returns the greatest common divisor of a and b 
 * using the Euclidean algorithm.
 */
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

/*
 * The function et(x) returns the number of integers less than x 
 * that are relatively prime to x.
 */
int et(int x) {
    int count = 0;

    // For numbers less than x, find relatively prime numbers to x
    for (int num = 1; num < x; num++) {
        if (gcd(num, x) == 1) {
            count++; // Increment count if num is relatively prime to x
        }
    }
    return count;
}

/* Main function to run the program. */
int main() {
    char s[100];
    int n;

    // Ask the user to input an integer
    printf("Enter an integer: ");
    if (scanf("%d", &n) != 1) {
        printf("Error: Invalid input. Please enter an integer.\n");
        return 1; 
    }
    fgets(s, 100, stdin); // Clear the input buffer

    if (n < 2) {
        printf("Error: Please enter an integer greater than or equal to 2.\n");
        return 1; 
    }

    // Print the ET-function for each integer from 2 to n
    for (int i = 2; i <= n; i++) {
        printf("et(%d) = %d\n", i, et(i));
    }

    // Wait for user input before exiting
    fgets(s, 100, stdin); 
    return 0;
}