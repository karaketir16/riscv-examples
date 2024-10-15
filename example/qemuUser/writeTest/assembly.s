.section .data

hello: 
.string "Hello World From Assembly" #25 len


.section .text
.globl main

strlen:
    li t0, 0
    mv t2, a0
loop:
    lbu t1, 0(a0) 
    beq zero, t1, done
    addi a0, a0, 1
    j loop
done:
    sub a0, a0, t2 # a0 = a0 - t2
    ret # return

write:
    addi sp, sp, -16    # allocate the stack frame
    sw ra, 12(sp)       # save the return address
    li a7, 64           # set the syscall code (64 = write)
    ecall               # invoke the operating system
    lw ra, 12(sp)       # restore the return address
    addi sp, sp, 16     # deallocate the stack frame
    ret # return

main:
    la a0, hello    
    jal strlen     
    mv a2, a0
    li a0, 1 # out
    la a1, hello
    jal write
wait:
    j wait
    
    