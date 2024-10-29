void supervisor()
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
        
        asm volatile ("mv t0, %[svisor]"
            : /* no output */
            : /* no input */ [svisor] "r"(supervisor)
            : );
    }
}

void custom_exit() {
    while (1);             /* Hang here when main returns */
}