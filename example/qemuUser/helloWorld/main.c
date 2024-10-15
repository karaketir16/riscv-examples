#include <stdio.h>

extern int my_asm_function(void);

int main() {
    int result = my_asm_function();
    printf("Result from assembly:: %d\n", result);
    return 0;
}
