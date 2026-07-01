#include<stdio.h>
#include<stdlib.h>


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

void printList(node* h) {
    node* current = h;
    while (current != NULL) {
        printf("%lld\n", current->value);
        current = current->next;
    }
}

int main() {
    long long lastPrime = 2;
    long long candidate = 3;
    node* primes = createNode(lastPrime); // Initialize the linked list with the first prime number
    node* tail = primes; // Keep track of the last node for efficient insertion
    long long countPrimes = 1;
    while (countPrimes < 100) {
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
            countPrimes++;
            lastPrime = candidate;
            node* newNode = createNode(candidate);
            tail->next = newNode; // Append to the end of the list
            tail = newNode; // Update the tail to the new last node
        }
        candidate += 2; // Check only odd numbers
    }

    // Now make a new linked list that has only those prime numbers whose second digit is bigger 
    // than the first digit.  Print this new list.
    node* newHead = NULL; 
    node* newTail = NULL;
    long long countPrimesWithSecondDigitBigger = 0;
    for (node* prime = primes; prime != NULL; prime = prime->next) {
        long long value = prime->value;
        while (value >= 100) {
            value /= 10; // Reduce to two digits
        }
        if (prime->value >= 10) { // Ensure it's at least two digits
            int firstDigit = (int) (value / 10);
            int secondDigit = (int) (value % 10);
            if (secondDigit > firstDigit) {
                node* newNode = createNode(prime->value);
                if (newHead == NULL) {
                    newHead = newNode;
                    newTail = newNode;
                } else {
                    newTail->next = newNode;
                    newTail = newNode;
                }
                countPrimesWithSecondDigitBigger++;
            }
        }
    }
    printList(newHead); // Print the new list
    printf("Count of primes with second digit bigger than first digit: %lld\n", countPrimesWithSecondDigitBigger);

    //----------- Reverse the new linked list -----------
    node* prev = NULL;
    node* current = newHead;
    node* nextNode = newHead;
    long long countReversedPrimes = 0;
    while (current) {
        nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
        countReversedPrimes++;
    }
    printList(prev); // Print the reversed list
    printf("Count of reversed primes: %lld\n", countReversedPrimes);

    // Free the memory allocated for the linked lists
    node* temp;
    while (primes) {
        temp = primes->next;
        free(primes);
        primes = temp;
    }

    while (prev) {
        temp = prev->next;
        free(prev);
        prev = temp;
    }

    return 0;
}