/* radius.c
 * 
 * CS-5008 Summer 2026
 * Dan Liu
 * 
 * Asks the user for a radius
 * Prints an integer approximation of the area of a circle with that radius.
 */

#include <stdio.h>
#include <math.h>

int main(){
    char s[100];
    int radius;
    int area;
    double pi = acos(-1);

    // Ask the user for a radius
    printf("Enter an integer radius: ");
    scanf("%d", &radius);
    fgets(s, 100, stdin); // Clear the input buffer
    
    // Validate the input radius
    if (radius < 0) {
        printf("Error: Radius cannot be negative.\n");
        return 1; // Exit with an error code
    }
    
    // Calculate the area of a circle with that radius
    area = (int)(pi * radius * radius);

    // Print an integer approximation of the circle area
    printf("For a circle of radius %d the area is %d\n", radius, area);

    // Wait for user input before exiting
    fgets(s, 100, stdin);
}