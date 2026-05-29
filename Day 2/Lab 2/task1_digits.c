/* task_digits.c
 *
 * CS-5008 Summer 2026
 * Dan Liu
 * 
 * Reads a number from the user
 * Prints the sum of the digits of the number
 */

#include <stdio.h>

int main () {
    char s[100];
    int number;
    int sum = 0;

    printf("Enter a number: ");
    scanf("%d", &number);
    fgets(s, 100, stdin); // Clear the input buffer

    // Calculate the sum of the digits
    while (number > 0) {
        sum += (number % 10); // Add the last digit to the sum
        number /= 10; // Remove the last digit
    }

    printf("The sum of the digits is %d\n", sum);

    // Wait for user input before exiting
    fgets(s,100,stdin);
}