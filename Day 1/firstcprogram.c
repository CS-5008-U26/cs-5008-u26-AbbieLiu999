/* A First C Program - for Homework 1
 *
 * This code will start you off.  Modify it as instructed in Homework 1.
 * 
 * Put your name here: Dan Liu
 * CS-5008 Summer 2026
 */

/* Standard Libraries */
#include <stdio.h>

/**** MAIN PROGRAM ****/

int main() {

    int x;                          // x will be the value entered by the user
    int y;                          // y will be another value entered by the user
    int z;                          // z will be the sum of x and y
    char s[100];                    // s is used to "pause" the console so it doesn't exit too quickly

    /* Ask for a number and print it out */
    printf("Enter a number: ");     // prompt the user
    scanf("%d", &x);                // read a number from the console ("stdin")
    fgets(s,100,stdin);             // sadly, we have to remove the \n that scanf leaves in stdin
   
    
    /* Ask for another number and print it out */
    printf("Enter another number: "); 
    scanf("%d", &y);                  
    fgets(s,100,stdin);                
    

    /* Calculate the sum of x and y */
    z = x + y;
    printf("Their sum is: %d\n", z); // tell the user the result

    /* Normally I would not put a comment on every line of code.
       I just did it above because you are learning C for the first time.
       I would only put a comment on a line if it was hard to understand or required that you
       know something that is not entirely obvious by looking at the code.
    */

    /* Pause the console so we can look at it before it vanishes */
    fgets(s,100,stdin);
}