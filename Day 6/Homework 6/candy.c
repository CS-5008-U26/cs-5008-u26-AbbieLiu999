/* candy.c
 * 
 * CS-5008 Summer 2026
 * Dan Liu
 * 
 * This program reads in candy-data.csv file and fulfills the following tasks:
 * 
 * Task 1: Print the name of each candy
 * Task 2: Print the name of each chocolate candy, with those with caramel in uppercase 
 *         and those without in lowercase. Also print the percentage of chocolate candies 
 *         that contain caramel.
 * Task 3: Print summary information (average sugar percent, price percent, and win percent) 
 *         about the candies:
 *         - By attribute
 *         - For candies with sugar percent higher than average
 *         - For candies with price percent higher than average 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Struct definition */
typedef struct candyStruct {
    char *competitorname; // heap-allocated candy name
    int chocolate;
    int fruity;
    int caramel;
    int peanutalmondy;
    int nougat;
    int crispedricewafer;
    int hard;
    int bar;
    int pluribus;
    double sugarpercent;
    double pricepercent;
    double winpercent;
} Candy;

/* 
 * Helper method: parses a line from the CSV file,
 * and returns a pointer to a new heap-allocated Candy struct
 */
Candy *parseCandy(char *line) {
    Candy *c = malloc(sizeof(Candy));
    if (!c) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL; 
    }
    
    // tokenize the line 
    char *token = strtok(line, ",");
    if (!token) {// If the line is empty or malformed
        fprintf(stderr, "Error parsing line\n");
        free(c);
        return NULL;
    }

    // store candy name on the heap
    c->competitorname = strdup(token);
    if (!c->competitorname) {
        fprintf(stderr, "Memory allocation failed\n");
        free(c);
        return NULL;
    }

    // parse the rest of the attributes
    for (int i = 0; i < 12; i++) {
        token = strtok(NULL, i == 11 ? ",\n\r" : ",");
        if (!token) {
            fprintf(stderr, "Error parsing line\n");
            free(c->competitorname);
            free(c);
            return NULL;
        }
        switch (i) {
            case 0: c->chocolate = atoi(token); break;
            case 1: c->fruity = atoi(token); break;
            case 2: c->caramel = atoi(token); break;
            case 3: c->peanutalmondy = atoi(token); break;
            case 4: c->nougat = atoi(token); break;
            case 5: c->crispedricewafer = atoi(token); break;
            case 6: c->hard = atoi(token); break;
            case 7: c->bar = atoi(token); break;
            case 8: c->pluribus = atoi(token); break;
            case 9: c->sugarpercent = atof(token); break;
            case 10: c->pricepercent = atof(token); break;
            case 11: c->winpercent = atof(token); break;
        }
    }
    return c;
}

/*
 * Helper method to read a file and return an array of pointers to Candy structs.
 */
Candy **readCandyList(char *filename, int *count) {
    *count = 0;
    // open file
    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return NULL;
    }

    // skip the header line
    char line[1000];
    if (!fgets(line, 1000, f)) {
        fprintf(stderr, "Error: empty file %s\n", filename);
        fclose(f);
        return NULL;
    }

    // array of pointers to Candy structs
    Candy **candies = malloc(200 * sizeof(Candy *)); 
    if (!candies) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(f);
        return NULL;
    }
    
    // read each line of the file, parse it, and store the pointer to 
    // the new Candy struct in the array
    while (fgets(line, 1000, f)) {

        // skip empty lines 
        if (line[0]=='\n' || line[0]=='\0') {
            continue;
        }
        
        // parse the line and store the pointer to the new Candy struct in the array
        Candy *c = parseCandy(line);
        if (!c) {
            continue;  // skip bad lines
        }
        candies[*count] = c;
        (*count)++;
    }
    
    // close the file after reading
    fclose(f); 
    return candies; 
}

/*
 * Helper method: converts a string to lowercase
 */
void lowercase(char *in, char *out) {
    while (*in) {
        *out = tolower(*in);
        in++;
        out++;
    }
    *out = '\0'; 
}

/*
 * Helper method: converts a string to uppercase
 */
void uppercase(char *in, char *out) {
    while (*in) {
        *out = toupper(*in);
        in++;
        out++;
    }
    *out = '\0'; 
}

/*
 * Task 2: prints chocolate candies with caramel in uppercase and those without
 * in lowercase, and prints the percentage of chocolate candies with caramel.
 */
void printChocolateCandies(Candy **candies, int count) {
    int chocCount = 0;
    int chocCaramelCount = 0;
    
    // Loop through candies and print chocolate ones in uppercase if 
    // they contain caramel, lowercase if not
    for (int i = 0; i < count; i++) {
        if (candies[i]->chocolate) {
            chocCount++;
            char out[strlen(candies[i]->competitorname) + 1]; 
            if (candies[i]->caramel) {
                chocCaramelCount++;
                uppercase(candies[i]->competitorname, out);
                printf("%s\n", out);
            } else {
                lowercase(candies[i]->competitorname, out);
                printf("%s\n", out);
            }
        }
    } 
    printf("\nPercentage of chocolate candies that contain caramel: %.1f%%\n",
       chocCount > 0 ? (double)chocCaramelCount / chocCount * 100 : 0.0);
}

/*
 * Helper method: print summary stats
 */
void printSummary(Candy **candies, int count, int *markers) {
    double sugarSum = 0;
    double priceSum = 0;
    double winSum = 0;
    int total = 0;

    for (int i = 0; i < count; i++) {
        if (markers[i]) {
            sugarSum += candies[i]->sugarpercent;
            priceSum += candies[i]->pricepercent;
            winSum += candies[i]->winpercent;
            total++;
        }
    }

    if (total == 0) {
        printf("No candies found with the specified criteria.\n");
        return;
    }

    printf("  - Average Sugar Percent: %.2f\n  - Average Price Percent: %.2f\n  - Average Win Percent: %.2f\n\n",
        sugarSum / total, priceSum / total, winSum / total);
}

/*
 * Helper method: frees the memory allocated for an array of pointers to Candy structs.
 */
void freeCandyList(Candy **candies, int count) {
    for (int i = 0; i < count; i++) {
        free(candies[i]->competitorname);
        free(candies[i]);
    }
    free(candies);
}

/* Main function */
int main(int argc, char *argv[]) {

    // read file and store candy data in an array of pointers to Candy structs
    char *filename = "../../Resources/candy-data.csv";
    if (argc > 1) {
        filename = argv[1];
    }
    
    int count = 0;
    Candy **candies = readCandyList(filename, &count);
    if (!candies) {
        fprintf(stderr, "Error reading candy list from file %s\n", filename);
        return 1;
    }
    
    /* =======================================================
     *   TASK 1 - Print all candy names         
     * ======================================================= */
    
    printf("=== Task 1: All Candies (%d total) ===\n", count);
    for (int i = 0; i < count; i++) {
        printf("%s\n", candies[i]->competitorname);
    }
    printf("\n");  

    /* =======================================================
     *   TASK 2 - Chocolate candies
     * ======================================================= */
    printf("=== Task 2: Chocolate Candies ===\n");
    printChocolateCandies(candies, count);

    /* =======================================================
     *   TASK 3 - Summary Information
     * ======================================================= */
    printf("\n=== Task 3: Summary Information ===\n");

    const char *attributes[] = {"chocolate", "fruity", "caramel", "peanutalmondy", 
                                "nougat", "crispedricewafer", "hard", "bar", "pluribus"};
    int numAttributes = sizeof(attributes) / sizeof(attributes[0]);
    int *markers = calloc(count, sizeof(int)); // array to flag which candies match the current criteria
    if (!markers) {
        fprintf(stderr, "Memory allocation failed\n");
        freeCandyList(candies, count);
        return 1;
    }
    
    // Loop through each attribute and print summary stats
    for (int j = 0; j < numAttributes; j++) {
        for (int i = 0; i < count; i++) {
            int val = 0;
            switch (j) {
                case 0: val = candies[i]->chocolate; break;
                case 1: val = candies[i]->fruity; break;
                case 2: val = candies[i]->caramel; break;
                case 3: val = candies[i]->peanutalmondy; break;
                case 4: val = candies[i]->nougat; break;
                case 5: val = candies[i]->crispedricewafer; break;
                case 6: val = candies[i]->hard; break;
                case 7: val = candies[i]->bar; break;
                case 8: val = candies[i]->pluribus; break;
            }
            markers[i] = val;
        }
        printf("Attribute %s:\n", attributes[j]);
        printSummary(candies, count, markers);     
    }

    // Print summary for all candies with sugar percent higher than average
    double totalSugar = 0;
    for (int i = 0; i < count; i++) {
        totalSugar += candies[i]->sugarpercent;
    }
    double averageSugar = totalSugar / count;
    printf("Candies with sugar percent higher than average (%.2f):\n", averageSugar);
    for (int i = 0; i < count; i++) {
        markers[i] = candies[i]->sugarpercent > averageSugar ? 1 : 0;
    }
    printSummary(candies, count, markers);

    // Print summary for all candies with price percent higher than average
    double totalPrice = 0;
    for (int i = 0; i < count; i++) {
        totalPrice += candies[i]->pricepercent;
    }
    double averagePrice = totalPrice / count;
    printf("Candies with price percent higher than average (%.2f):\n", averagePrice);
    for (int i = 0; i < count; i++) {
        markers[i] = candies[i]->pricepercent > averagePrice ? 1 : 0;
    }
    printSummary(candies, count, markers);  

    // free allocated memory
    free(markers);
    freeCandyList(candies, count);

    return 0;
}