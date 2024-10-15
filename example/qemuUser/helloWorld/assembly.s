.section .text
.globl my_asm_function

my_asm_function:
    li a0, 42      # Load immediate 42 into register a0
    ret            # Return with the value in a0
