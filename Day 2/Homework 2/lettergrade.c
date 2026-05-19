/* lettergrade.c
 * 
 * CS-5008 Summer 2026
 * Dan Liu
 * 
 * Asks for a number score from 1 to 10
 * Prints the corresponding letter grade (A-F).
 * Print an error message if the user enters a number greater than 10 or less than 1.
 * Using if-else statements
 */

#include <stdio.h>

int main() {
    char s[100];
    int score;

    // Ask the user for a number score from 1 to 10
    printf("Enter the number score: ");
    scanf("%d", &score);
    fgets(s, 100, stdin); // Clear the input buffer

    // Determine the letter grade based on the number score
    if (score == 9 || score == 10) {
        printf("Your grade is A\n");
    } else if (score == 8) {
        printf("Your grade is B\n");
    } else if (score == 7) {
        printf("Your grade is C\n");
    } else if (score == 6) {
        printf("Your grade is D\n");
    } else if (score == 4 || score == 5) {
        printf("Your grade is E\n");
    } else if (score == 3 || score == 2 || score == 1) {
        printf("Your grade is F\n");
    } else {
        printf("Error: Please enter a number between 1 and 10.\n");
    }
}