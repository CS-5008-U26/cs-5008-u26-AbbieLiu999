#include <stdio.h>
/*
 * A Third C Program - for Homework 1
 * Put your name here: Dan Liu
 * CS-5008 Summer 2026
 */
int main() {
    char t[100];
    int x; // x will be the year the user was born
    int y; // y will be the user's age in 2026
    char s[100];

    printf ("What is your name? ");
    scanf("%s", t);
    fgets(s,100,stdin);
    printf("%s? That's a funny name!\n",t);

    printf("What year were you born? "); // ask the user for their birth year
    scanf("%d", &x); // read the birth year from the console
    fgets(s,100,stdin); // remove the \n that scanf leaves in stdin
    y = 2026 - x; // calculate the user's age in 2026
    printf("Wow, you are %d years old!\n", y); // tell the user their age in 2026

    fgets(s,100,stdin); 
}

