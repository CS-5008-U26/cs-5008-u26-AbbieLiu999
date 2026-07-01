/* primes.c
 *
 * CS-5008 Summer 2026
 * Dan Liu
 * 
 * More efficient way to print prime numbers up to 100
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct intNode {
    long long value;
    struct intNode *next;
} node;

node* createNode(long long x) {
    node* newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    newNode->value = x;
    newNode->next = NULL;
    return newNode;
}

int main() {
    long long lastPrime = 2;
    long long candidate = 3;
    node* primes = createNode(lastPrime); // Initialize the linked list with the first prime number
    node* tail = primes; // Keep track of the last node for efficient insertion
    long long countPrimes = 1;
    double time_taken;
    clock_t start_time = clock(); // Start the timer
    while (1) {
        int is_prime = 1; // Assume candidate is prime
        for (node* prime = primes; prime != NULL; prime = prime->next) {
            if (prime->value * prime->value > candidate) {
                break;
            }
            if (candidate % prime->value == 0) {
                is_prime = 0; // candidate is not prime
                break; // No need to check further
            }
        }
        if (is_prime) {
            lastPrime = candidate;
            node* newNode = createNode(candidate);
            tail->next = newNode; // Append to the end of the list
            tail = newNode; // Update the tail to the new last node
            countPrimes++;
            
            clock_t end_time = clock(); // Stop the timer
            time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC; 
            if (time_taken > 0.5) {
                printf("%3lld\n", lastPrime);
                break;
            }
        }
        candidate += 2; // Check only odd numbers
    }

    // free memory allocated to the list
    node* temp;
    while (primes) {
        temp = primes->next;
        free(primes);
        primes = temp;
    }

    return 0;
}