/* roman.c
 * 
 * CS-5008 Summer 2026
 * Dan Liu
 * 
 * Reads a number from the user between 1 and 4000, prints it in Roman numerals.
 * Print an error message when input is < 1 or > 4000.
 */
#include <stdio.h>
int main() {
    char s[100];
    int number;
    
    // Define the values and corresponding Roman numerals
    int values[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char *numerals[13] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    // Ask the user for a number between 1 and 4000
    printf("Enter a number between 1 and 4000: ");
    scanf("%d", &number);
    fgets(s, 100, stdin); // Clear the input buffer

    // Validate the input number
    if (number < 1 || number > 4000) {
        printf("Error: Please enter a number between 1 and 4000.\n");
        return 1; // Exit with an error code
    }
    
    printf("The Roman Numeral: ");
    // Convert the number to Roman numerals
    for (int i = 0; i < 13; i++) {
        while (number >= values[i]) {
            printf("%s", numerals[i]);
            number -= values[i];
        }
    }
    printf("\n");

    // Wait for user input before exiting
    fgets(s, 100, stdin);
}