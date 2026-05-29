/* task2_printing.c
 *
 * CS-5008 Summer 2026
 * Dan Liu
 * 
 * Print all the numbers from 0 to 1500 that are multiples of 63.
 * Print them in a column, right-justified.
 */

#include <stdio.h>

int main () {
    for (int i = 0; i <= 1500; i += 63) {
        printf("%4d\n", i); // Print the number with a width of 4, right-justified
    }
}
    