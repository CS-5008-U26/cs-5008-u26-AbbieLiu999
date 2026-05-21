/* lettergrade2.c
 *
 * CS-5008 Summer 2026
 * Dan Liu
 * 
 * Asks for a number score from 0 to 100.
 * Prints the corresponding letter grade (A-F).
 * If the number score is between 61 and 100, after the letter grade, print +, -, or nothing 
 * based on the last digit of the number score. eg. 1-3 = -, 4-7 = nothing, 8-0 = +.
 * Print an error message if the user enters a number greater than 100 or less than 0.
 */
#include <stdio.h>

int main() {
    char s[100];
    int score;
    char grade[100];

    // Ask the user to input number score from 0 to 100
    printf("Enter the number score: ");
    scanf("%d", &score);
    fgets(s, 100, stdin); // Clear the input buffer

    // Determine the letter grade based on the number score
    if (score > 90 && score <= 100) {
        grade[0] = 'A';
        if (score % 10 >= 8 || score % 10 == 0) {
            grade[1] = '+';
            grade[2] = '\0';
        } else if (score % 10 >= 1 && score % 10 <= 3) {
            grade[1] = '-';
            grade[2] = '\0';
        } else {
            grade[1] = '\0';
        }
    } else if (score > 80 && score <= 90) {
        grade[0] = 'B';
        if (score % 10 >= 8 || score % 10 == 0) {
            grade[1] = '+';
            grade[2] = '\0';
        } else if (score % 10 >= 1 && score % 10 <= 3) {
            grade[1] = '-';
            grade[2] = '\0';
        } else {
            grade[1] = '\0';        
        } 
    } else if (score > 70 && score <= 80) {
        grade[0] = 'C';
        if (score % 10 >= 8 || score % 10 == 0) {
            grade[1] = '+';
            grade[2] = '\0';
        } else if (score % 10 >= 1 && score % 10 <= 3) {
            grade[1] = '-';
            grade[2] = '\0';
        } else {
            grade[1] = '\0';    
        }
    } else if (score > 60 && score <= 70) {
        grade[0] = 'D';
        if (score % 10 >= 8 || score % 10 == 0) {
            grade[1] = '+';
            grade[2] = '\0';    
        } else if (score % 10 >= 1 && score % 10 <= 3) {
            grade[1] = '-';
            grade[2] = '\0';
        } else {
            grade[1] = '\0';
        }
    } else if (score >= 0 && score <= 60) {
        grade[0] = 'F';
        grade[1] = '\0';    
    } else {
        printf("Error: Please enter a number between 0 and 100.\n");
    }
    if (score >= 0 && score <= 100) {
        printf("Your grade is %s\n", grade);
    }
    
    // Wait for user input before exiting
    fgets(s, 100, stdin);
}