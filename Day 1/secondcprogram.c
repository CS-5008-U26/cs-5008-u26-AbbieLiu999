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
    char s[100];
    char t[100];
    printf ("What is your name? ");
    scanf("%s", t);
    fgets(s,100,stdin);
    printf("%s? That's a funny name!\n",t);
    fgets(s,100,stdin);
}
