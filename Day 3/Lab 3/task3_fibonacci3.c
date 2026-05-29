#include <stdio.h>
#include <time.h>

int fibonacci(int num) {
    int oldOldResult = 1; // F(1)
    int oldResult = 1; // F(2)
    if (num == 1 || num == 2) {
        return 1;
    }
    for (int i = 3; i <= num; i++) {
        int result = oldResult + oldOldResult;
        oldOldResult = oldResult;
        oldResult = result;
    }
    return oldResult;
}
int main() {
    char s[100];
    clock_t start = clock(); //Start the timer
    int num = 1;
    int result = 0;
    while (1) {
        result = fibonacci(num);
        printf("%d\n", result);
        double eclipsed = (double)(clock() - start) / CLOCKS_PER_SEC; //Calculate the eclapsed time
        if (eclipsed > 5.0) {
            break;
        }
        num++;
    }
    printf("The highest Fibonacci number generated in 5 seconds is %d\n", result);
    printf("The number of terms generated in 5 seconds is %d\n", num);
    fgets(s,100,stdin);
}