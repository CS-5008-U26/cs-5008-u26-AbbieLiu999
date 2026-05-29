/* Opening comment here
*/
#include <stdio.h>
#include <time.h>

int fibonacci(int num) {
    if (num == 2 || num == 1) {
        return 1;
    }
    return fibonacci(num - 1) + fibonacci(num - 2);
}

int main () {
    char s[100];
    clock_t start_time = clock(); // Start the timer
    int num = 1;
    int result = 0;
    while (1) {
        // printf("%d\n", fibonacci(num));
        result = fibonacci(num);
        double time_taken = (double)(clock() - start_time) / CLOCKS_PER_SEC; 
        if (time_taken > 5.0) {
            break;
        } 
        num++;
    }
    printf("The highest Fibonacci number generated in 5 seconds is %d\n", result);
    printf("The number of terms generated in 5 seconds is %d\n", num);
    fgets(s, 100, stdin);
}