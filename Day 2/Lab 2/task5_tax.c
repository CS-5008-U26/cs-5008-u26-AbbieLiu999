/* task5_tax.c
 *
 * CS-5008 Summer 2026
 * Dan Liu
 * 
 * Accepts a floating-point(double) number from the user as a price in dollars
 * Add 8% to the number for tax
 * Print the total price with tax, formatted to 2 decimal places
 */
#include <stdio.h>

int main() {
    char s[100];
    const double TAX_RATE = 0.08;
    double price;
    double total_price;

    while (1) {
        printf("Enter a price in dollars: ");
        scanf("%lf", &price);
        fgets(s, 100, stdin); // Clear the input buffer

        if (price == 0) {
            break;
        }

        total_price = price * (1.00 + TAX_RATE);
        printf("The value with tax is $%.2f\n", total_price);
    }
}