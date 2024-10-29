.global _start
.section .text._start

_start:
    la sp, _stack_top    /* Load stack pointer */
    call main            /* Call the main function */
    j custom_exit        /* Jump to exit when main returns */
