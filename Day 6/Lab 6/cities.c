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

typedef struct cityStruct{
    char *cityName;
    char *cityNameAscii;
    char *stateId;
    char *stateName;
    char *countyFips;
    char *countyName;
    double latitude;
    double longitude;
    long population;
    } city;

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
 * Converts a line of text from the CSV file into a City struct.
 */
city* stringToCity (char *textLine) {
    city *newCity = malloc(sizeof(city));
    char *p = textLine; 
    char *token = strtok(p, ",");
    int column = 1; // Start from the first column
    while (column <= 9 && token != NULL) { // We only need up to the 9th column
        char temp[10000]; // Allocate a buffer for the temporary string
        stripQuotes(token, temp); // Strip quotes from the token
        switch (column) {
            case 1:
                newCity->cityName = strdup(temp); // Copy the city name and strip quotes
                break;
            case 2:
                newCity->cityNameAscii = strdup(temp); // Copy the city name ascii and strip quotes
                break;
            case 3:
                newCity->stateId = strdup(temp); // Copy the state ID and strip quotes
                break;
            case 4:
                newCity->stateName = strdup(temp); // Copy the state name and strip quotes
                break;
            case 5:
                newCity->countyFips = strdup(temp); // Copy the county FIPS code and strip quotes
                break;
            case 6:
                newCity->countyName = strdup(temp); // Copy the county name and strip quotes
                break;
            case 7:
                newCity->latitude = atof(temp); // Convert latitude to a double
                break;
            case 8:
                newCity->longitude = atof(temp); // Convert longitude to a double
                break;
            case 9:
                newCity->population = atol(temp); // Convert population to a long integer
                break;
        }
        token = strtok(NULL, ","); // Move to the next token
        column++; 
    }
    return newCity;
}

/*
 * Reads a list of cities from a CSV file.
 */
city** readCityList (char *filename) {
    // Open the CSV file for reading
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return NULL;
    }

    char line[10000];
    city **cityList = malloc(20 * sizeof(city*)); // Allocate memory for 20 city pointers

    // Read the header line and ignore it
    fgets(line, 10000, fp);

    // Read the next 20 lines of the file
    for (int i = 0; i < 20; i++) {
        if (fgets(line, 10000, fp) == NULL) {
            fprintf(stderr, "Error reading line from file.\n");
            fclose(fp);
            return NULL;
        }
        cityList[i] = stringToCity(line); // Convert the line to a City struct and store it in the list
    }

    fclose(fp); // Close the file
    return cityList; // Return the list of cities
}

/*
 * Frees the memory allocated for a City struct and its fields.
 */
void freeCity (city *c) {
    free(c->cityName);
    free(c->cityNameAscii);
    free(c->stateId);
    free(c->stateName);
    free(c->countyFips);
    free(c->countyName);
    free(c); // Free the city struct itself
}

/*
 * Main function to read the CSV file and calculate the required values.
 */
int main() {
    // Open the CSV file for reading
    city **cityList = readCityList("../../Resources/uscities.csv");
    if (cityList == NULL) {
        fprintf(stderr, "Error reading city list.\n");
        return 1;
    }

    for (int i = 0; i < 20; i++) {
        printf("City: %s, Population: %ld\n", cityList[i]->cityName, cityList[i]->population);
    }
    
    char buffer[1000];
    while (1) {
        printf("Enter a city number: ");
        fgets(buffer, 1000, stdin);
        if (buffer[0] == '\n') {
            fprintf(stderr, "No input provided.\n");
            break;
        }
        int cityNumber = atoi(buffer);
        if (cityNumber < 1 || cityNumber > 20) {
            fprintf(stderr, "Invalid city number. Please enter a number between 1 and 20.\n");
            break;
        }
        printf("%s", cityList[cityNumber - 1]->cityName); // Print the name of the selected city
        printf(" %s, ", cityList[cityNumber - 1]->stateId); // Print the state ID of the selected city
        printf("population %ld\n", cityList[cityNumber - 1]->population); // Print the population of the selected city
    }  

    // Free the memory allocated for the city list
    for (int i = 0; i < 20; i++) {
        freeCity(cityList[i]);
    }
    free(cityList); // Free the list of city pointers
    return 0; // Return success
}