/* task3_prime.c
 *
 * CS-5008 Summer 2026
 * Dan Liu
 * 
 * Prints prime numbers up to 100
 * Prints the time taken to compute the prime numbers
 */
#include <stdio.h>
#include <time.h>

int main() {
    double time_taken;
    clock_t start_time = clock(); // Start the timer
    for (int i = 2; i <= 100; i++) {
        int is_prime = 1; // Assume i is prime
        for (int j = 2; j < i; j++) {
            if (i % j == 0) {
                is_prime = 0; // i is not prime
                break; // No need to check further
            }
        }
        if (is_prime) {
            printf("%3d\n", i);
        }
    }
    clock_t end_time = clock(); // Stop the timer
    time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000; // Convert to milliseconds
    printf("Time taken is %lf milliseconds\n", time_taken);
}
