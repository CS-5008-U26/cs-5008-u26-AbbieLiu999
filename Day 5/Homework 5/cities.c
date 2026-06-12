/* cities.c
 *
 * CS-5008 Summer 2026
 * Dan Liu
 * 
 * This program reads in uscities.csv file and prints the sum of the populations of the 
 * 20 largest cities, and also print the name of the northernmost of these 20 cities.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Removes all double-quote characters from the input string
 * and copies the result into the output string.
 */
void stripQuotes(char *in, char *out) {
    while (*in) {
        if (*in != '"') {
            *out = *in;
            out++;
        }
        in++;
    }
    *out = '\0'; // Null-terminate the output string
}

/*
 * Main function to read the CSV file and calculate the required values.
 */
int main() {

    // Open the CSV file for reading
    FILE *fp = fopen("../../Resources/uscities.csv", "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    char line[10000];

    // Read the header line and ignore it
    fgets(line, 10000, fp);

    long populationSum = 0;
    char northernCity[200];
    double northernLatitude = -90.0; // Start with the lowest possible latitude

    // Read the next 20 lines of the file
    for (int i = 0; i < 20; i++) {
        if (fgets(line, 10000, fp) == NULL) {
            fprintf(stderr, "Error reading line from file.\n");
            fclose(fp);
            return 1;
        }
        
        char cityName[200];
        double latitude;
        long population;

        // Parse the line to extract the population and latitude
        char *token = strtok(line, ","); 
        int column = 1; // Start from the first column
        while (column <= 9 && token != NULL) { // We only need up to the 9th column
            char temp[200];
            stripQuotes(token, temp); // Strip quotes from the token
            if (column == 2) {
                strcpy(cityName, temp); // Copy the city name and strip quotes
            }
            if (column == 7) {
                latitude = atof(temp); // Convert latitude to a double
            }
            if (column == 9) {
                population = atol(temp); // Convert population to a long integer
            }
            token = strtok(NULL, ","); // Move to the next token
            column++; 
        }
        
        // Update the population sum
        populationSum += population;
        // Check if this city is the northernmost so far
        if (latitude > northernLatitude) {
            northernLatitude = latitude;
            strcpy(northernCity, cityName);   
        }
    }

    fclose(fp); // Close the file
    printf("Sum of the populations: %ld\n", populationSum);
    printf("Northernmost city is: %s\n", northernCity);
    return 0;
}