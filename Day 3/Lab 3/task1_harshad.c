/* Opening comment here
*/

#include <stdio.h>
/*
 * Function to check if a number is a Harshad number
 */
int isHarshad(int n) {
    int sum = 0;
    int temp = n;
    while (temp > 0) {
        sum += temp % 10; // Add the last digit to the sum
        temp /= 10; // Remove the last digit
    }
    return (n % sum == 0); // Check if n is divisible by the sum of its digits
}

int main() {
    char s[100];
    for (int i = 10; i <= 99; i++) {
        if (isHarshad(i)) {
            printf("%d is a Harshad number.\n", i);
        }
    }
    fgets(s,100,stdin);
}