#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>

int array[10];

extern int func(void);

extern int gen_random_int();

void checker(){
    unsigned int i = 0;
    while(1){
        int m = INT_MIN;
        for(int i = 0; i < 10; i++){
            array[i] = gen_random_int();
            m = (m < array[i] ? array[i] : m);
        }
        int result = func();

        if(m != result){
            printf("i: %d\n", i);
            printf("Arr: ");
            for(int i = 0; i < 10; i++){
                printf("%d, ", array[i]);
            }
            printf("\n");
            int result = func();
            printf("Result from assembly: %d\n", result);
            printf("Real result from C: %d\n", m);
            break;
        }

        i++;
        if(i % 10000 == 0){
            printf("All good for now %d\n", i);
            fflush(stdout);
        }
    }
}


int main() {
    
    srand(time(NULL));
    checker();

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
