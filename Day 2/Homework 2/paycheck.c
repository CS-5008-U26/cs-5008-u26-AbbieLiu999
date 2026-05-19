/* paycheck.c
 * 
 * CS-5008 Summer 2026
 * Dan Liu
 * 
 * Reads hourly rate and hours worked, prints pay due.
 * Overtime (hours > 40) paid at 1.5x rate.
 * Exits when either input is <= 0.
 */
#include <stdio.h>

int main () {
    char s[100];
    double hourly_rate;
    double working_hours;
    double paycheck;
    
    while (1) {
        // Ask the user for the hourly rate 
        printf("Enter an hourly rate: ");
        scanf("%lf", &hourly_rate);
        fgets(s, 100, stdin);
        if (hourly_rate <= 0) {
            break; // Exit the loop if the hourly rate is zero or negative
        }

        // Ask the user for the number of hours worked
        printf("Enter the number of hours worked: ");
        scanf("%lf", &working_hours);
        fgets(s, 100, stdin);
        if (working_hours <= 0) {
            break; // Exit the loop if the working hours is zero or negative
        }
        
        // Calculate the paycheck and print the result
        if (working_hours > 40) {
            // Calculate overtime pay, excess hours are paid at 1.5 x the hourly rate.
            paycheck = (40 * hourly_rate) + ((working_hours - 40) * hourly_rate * 1.5);
        } else {
            paycheck = hourly_rate * working_hours;
        }
        printf("You should be paid: %.2f\n", paycheck);
    }
    return 0;
}