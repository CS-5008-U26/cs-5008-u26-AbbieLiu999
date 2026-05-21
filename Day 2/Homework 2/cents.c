/* cents.c
 *
 * CS-5008 Summer 2026
 * Dan Liu
 * 
 * Asks the user for an integer number of cents between 1 and 100.
 * Prints the number of quarters, dimes, nickels, and pennies needed for that number of cents.
 * Use the largest denominations of coins possible.
 */
#include <stdio.h>
int main() {
    char s[100];
    int cents;
    int quarters;
    int dimes;
    int nickels;
    int pennies;

    // Ask the user to input an integer number of cents
    printf("Enter a number of cents: ");
    scanf("%d", &cents);
    fgets(s, 100, stdin); // Clear the input buffer
    
    // Validate the input cents
    if (cents < 1 || cents > 100) {
        printf("Error: Please enter a number between 1 and 100.\n");
        return 1; // Exit with an error code
    }

    // Calculate the number of quarters, dimes, nickels, and pennies needed
    quarters = cents / 25;
    cents %=25;
    dimes = cents / 10;
    cents %= 10;
    nickels = cents / 5;
    cents %= 5;
    pennies = cents;

    // Print the number of quarters, dimes, nickels, and pennies needed
    printf("That requires");
    if (quarters > 0) {
        if (quarters == 1) {
            printf(" %d quarter", quarters);
        } else {
            printf(" %d quarters", quarters);
        }
    }
    if (dimes > 0) {
        if (dimes == 1) {
            printf(" %d dime", dimes);
        } else {
            printf(" %d dimes", dimes);
        }
    }
    if (nickels > 0) {
        if (nickels == 1) {
            printf(" %d nickel", nickels);
        } else {
            printf(" %d nickels", nickels);
        }
    }
    if (pennies > 0) {
        if (pennies == 1) {
            printf(" %d penny", pennies);
        } else {
            printf(" %d pennies", pennies);
        }
    }
    printf(".\n");

    // Wait for user input before exiting
    fgets(s, 100, stdin);
}