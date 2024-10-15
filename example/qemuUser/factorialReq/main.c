#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>

extern int factorial(int n);

int main() {
    int res = factorial(4);

    printf("result: %d\n", res);

    return 0;
}

