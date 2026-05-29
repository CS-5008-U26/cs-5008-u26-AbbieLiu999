/* Opening comment here
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count(int p, int q, int r) {
    // Validate parameters
    if (p <= 0 || q <= 0 || r <= 0) {
        return -1;
    }
    int count = 0;
    for (int i = 0; i < p; i++) {
        int randomNumber = rand() % (q + 1); // Generate a random number between 0 and q
        if (randomNumber <= r) {
            count++;
        } 
    }
    return count;
}


int main () {
    char s[100];
    int p, q, r;
    // Seed the random number generator with the current time
    srand((unsigned int)time(NULL));
    while (1) {
        printf("Enter p (number of trials, 0 to quit): \n");
        if (scanf("%d", &p) != 1) {
            printf("Error:Invalid input. Exiting.\n");
            break;
        }
        if (p == 0) {
            printf("Exiting the program.\n");
            break;
        }

        printf("Enter q (upper bound for random numbers): \n");
        if (scanf("%d", &q) != 1) {
            printf("Error: Invalid input. Exiting.\n");
            break;
        }

        printf("Enter r (threshold for counting): \n");
        if (scanf("%d", &r) != 1) {
            printf("Error: Invalid input. Exiting.\n");
            break;
        }

        int result = count(p, q, r);
        if (result == -1) {
            printf("Error: p, q, and r must be positive integers.\n");
        } else {
            printf("Result: %d of %d random numbers in [0, %d] are in [0, %d].\n",
                result, p, q, r);
        }
        fgets(s,100,stdin);
    }
}