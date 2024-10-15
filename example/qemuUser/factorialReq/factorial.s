.globl factorial
.text
factorial:
    addi sp, sp, -16 
    sw ra, (sp) 
    bne a0, zero, req
    li a0, 1 
    j done
req:
    mv t0, a0
    addi a0, a0, -1;
    sw t0, 4(sp)
    jal factorial  # jump to target and save position to ra
    lw ra, 0(sp)
    lw t0, 4(sp)
    mul a0, a0, t0
done:
    addi sp, sp, 16
    ret 
    
    

