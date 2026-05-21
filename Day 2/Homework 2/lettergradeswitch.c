/* lettergradeswitch.c
 *
 * CS-5008 Summer 2026
 * Dan Liu
 * 
 * Asks for a number score from 1 to 10.
 * Prints the corresponding letter grade (A-F).
 * Print an error message if the user enters a number greater than 10 or less than 1.
 * Use a switch statement.
 */

#include <stdio.h>

int main() {
    char s[100];
    int score;

    // Ask the user for a number score from 1 to 10
    printf("Enter the number score: ");
    scanf("%d", &score);
    fgets(s, 100, stdin); // Clear the input buffer

    // Determine the letter grade based on the number score using a switch statement
    switch (score) {
        case 10:
        case 9:
            printf("Your grade is A\n");
            break;
        case 8:
            printf("Your grade is B\n");
            break;
        case 7:
            printf("Your grade is C\n");
            break;
        case 6:
            printf("Your grade is D\n");
            break;
        case 5: 
        case 4:
            printf("Your grade is E\n");
            break;
        case 3:
        case 2:
        case 1:
            printf("Your grade is F\n");
            break;
        default:
            printf("Error: Please enter a number between 1 and 10.\n");
    }

    // Wait for user input before exiting
    fgets(s, 100, stdin);
}