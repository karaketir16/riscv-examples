#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>

int array[10];

extern int addijx(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);

int get_x(){
    return 7;
}


int main() {
    int res = addijx(0,0,0,0,0,0,0,0,5,2);

    printf("result: %d\n", res);

    return 0;
}


//from https://stackoverflow.com/a/32774047
int gen_random_int() {
    const int BITS_PER_RAND = (int)(log2(RAND_MAX/2 + 1) + 1.0); /* Or log(RAND_MAX + 1) / log(2) with older language standards */
    int ret = 0;
    for (int i = 0; i < sizeof(int) * CHAR_BIT; i += BITS_PER_RAND) {
        ret <<= BITS_PER_RAND;
        ret |= rand();
    }
    return ret;
}
