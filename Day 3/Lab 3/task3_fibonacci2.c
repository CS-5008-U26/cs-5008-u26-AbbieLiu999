/* Opening comment here
*/
#include <stdio.h>
#include <time.h>

int fibonacci(int num, int oldResult, int oldOldResult) {
    if (num == 1 || num == 2) {
        return 1;
    }
    return oldResult + oldOldResult;
}

int main () {
    char s[100];
    clock_t start_time = clock(); // Start the timer
    int num = 1;
    int result = 0;
    int oldResult = 1; // F(2)
    int oldOldResult = 1; // F(1)
    while (1) {
        result = fibonacci(num, oldResult, oldOldResult);
        oldOldResult = oldResult;
        oldResult = result;
        printf("%d\n", result);
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