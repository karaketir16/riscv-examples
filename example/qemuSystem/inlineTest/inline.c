void supervisor()
{
    volatile int x,y,z,t,a,b,c,d;
}

void is_same()
{

}

int main(){
    while(1){
        asm volatile ("addi t0, t0, 1"
            : /* no output */
            : /* no input */
            : "t0", "memory");

        asm volatile ("call %[svisor]"
            : /* no output */
            : /* no input */ [svisor] "i"(supervisor)
            : );
        
        asm volatile (
            "mv t0, %0\n"
            "la t1, %1\n"
            "bne t0, t1, cont\n"
            "call is_same\n"
            "cont:"
            : /* no output */
            : /* no input */ "r"(supervisor), "i"(supervisor)
            : );
    }



}

void custom_exit() {
    while (1);             /* Hang here when main returns */
}