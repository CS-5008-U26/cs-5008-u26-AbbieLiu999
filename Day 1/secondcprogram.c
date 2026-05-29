#include <stdio.h>
/*
 * A Second C Program - for Homework 1
 * Put your name here: Dan Liu
 * CS-5008 Summer 2026
 * fixes I made:
 * 1. I changed the address of scanf from s to t, because we want to read the name into t, not s.
 * 2. I added a newline character to the end of the printf statement, so there is no trailing % in the output.
 * 3. I added a fgets statement to keep the console open so we can see the output before it vanishes.
 */
int main() {
    // Buffers: s is used to pause the program, t holds the user's name
    char s[100];
    char t[100];

    // Prompt the user and read their name from standard input
    printf ("What is your name? ");
    scanf("%s", t);

    // Consume the leftover newline from scanf so it doesn't interfere later
    fgets(s,100,stdin);

    // Print the silly response, using the name the user entered
    printf("%s? That's a funny name!\n",t);

    // Wait for user input before exiting, so we can see the output
    fgets(s,100,stdin);

    return 0;
}
