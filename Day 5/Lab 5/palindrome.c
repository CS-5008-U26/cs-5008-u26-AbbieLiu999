#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
 * This function takes a string and converts all alphabetic characters to lowercase,
 * while removing all non-alphabetic characters. The resulting string is stored in 
 * the output buffer.
 * 
 * @param in: The input string to be processed.
 * @param out: The output buffer where the processed string will be stored.
 */  
void condition(char *in, char *out) {
    while (*in) {
        if (isalpha(*in)) {
            *out = tolower(*in);
            out++;
        }
        in++;
    }
    *out = '\0'; // Null-terminate the output string
}

/*
 * This function will take a string, condition it, and then 
 * return TRUE if it is a palindrome, and FALSE if it is not.
 * 
 * @param in: The input string to be checked for palindrome properties.
 * @return: 1 if the processed string is a palindrome, 0 otherwise. 
*/
int palindrome(char *in) {
    char out[200];
    condition(in, out);
    char *left = out;
    char *right = out + strlen(out) - 1;
    while (left < right) {
        if (*left != *right) {
            return 0; // Not a palindrome
        }
        left++;
        right--;
    }
    return 1; // Is a palindrome
}

int main(int argc, char **argv) {
    if (argc < 2) {
        char inputBuffer[200];

        inputBuffer[0] = 'X'; // Initialize the input buffer
        while (inputBuffer[0] != '\n') {
            // print "Enter a string: " onto the console
            printf("Enter a string: ");

            // read one line from the console into inputBuffer
            fgets(inputBuffer, 200, stdin);

            if (inputBuffer[0] != '\n') {

                if (palindrome(inputBuffer)) {
                    printf("%s\n", inputBuffer);
                }
            }
        } 
    } else {
        FILE *fp = fopen(argv[1], "r");
        if (fp == NULL) {
            printf("Could not open filename %s", argv[1]);
            return 1;   
        }
        char buffer[2000];
        while (fgets(buffer, 2000, fp) != NULL) {
            if (palindrome(buffer)) {
                printf("%s\n", buffer);
            }
        }
        fclose(fp);    
    }
    return 0;
}