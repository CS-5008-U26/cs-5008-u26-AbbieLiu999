/* printCsv.c
 *
 * CS-5008 Summer 2026
 * Dan Liu
 * 
 * The program prompts the user for a filename, reads the file line by line, and prints 
 * each line along with its fields. The fields are separated by commas in the CSV file.
 */

#include <stdio.h>
#include <string.h>

/*
 * Removes the newline character from the end of a string if it exists.
 *
 * @param str The string to process.
 */
void killNewline(char *str) {
    if (strlen(str) >= 1 && str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }
}

/*
 * Gets the data up to the separator character, copying that into a buffer, 
 * and returns the pointer to the rest of the string.
 * 
 * @param start The string to process.
 * @param separator The character that separates fields in the CSV.
 * @param out The buffer to copy the field into.
 * @return A pointer to the next field in the string, or NULL if there are no more fields.
 */
char *getNextField(char *start, char separator, char *out) {
    
    // When there are no more fields, return NULL
    if (*start == '\0') {
        return NULL;
    }

    // Find the next separator character in the string
    char *sepPointer = strchr(start, separator);

    // When processing the last field, return the pointer to the end-of-string character
    if (sepPointer == NULL) {
        strcpy(out, start);
        return start + strlen(start);
    }
    
    // Copy the field into the output buffer
    int fieldLength = sepPointer - start;
    strncpy(out, start, fieldLength);
    out[fieldLength] = '\0'; // Null-terminate the output string
    return sepPointer + 1; // Return the pointer to the next field
}

/*
 * Main function to read and print the contents of a CSV file.
 */
int main() {

    // Prompt the user for a filename and read it into a buffer
    char buffer[1000];
    printf("Enter the filename: ");
    fgets(buffer, 1000, stdin);
    killNewline(buffer);

    // Open the file for reading
    FILE *fp = fopen(buffer, "r");
    if (fp == NULL) {
        printf("Cannot open file %s\n", buffer);
        return 1; 
    } else {
        char inputLine[1000];
        char nextField[1000];
        
        // Read each line of the file, print it, and then print each field in the line
        while (fgets(inputLine, 1000, fp) != NULL) {

            // Remove the newline character from the end of the line and print it
            killNewline(inputLine);
            printf(">%s<\n", inputLine);

            // Process the line to extract and print each field
            char *p = inputLine;
            while (p != NULL) {
                p = getNextField(p, ',', nextField); // Get the next field in the line
                if (p != NULL) { 
                    printf("  >%s<\n", nextField); 
                }
            }
        }

        // Close the file and return success
        fclose(fp);
        return 0;
    }
}