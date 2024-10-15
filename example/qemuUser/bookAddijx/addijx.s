.globl get_x
.globl addijx
.text
addijx:
    addi sp, sp, -4 # save the
    sw ra, (sp) # return address
    jal get_x # invoke the get_x routine
    lw a1, 4(sp) # load i from the program stack
    lw a2, 8(sp) # load j from the program stack
    add a0, a0, a1 # a0 := get_x() + i
    add a0, a0, a2 # a0 := get_x() + i + j
    lw ra, (sp) # restore the
    addi sp, sp, 4 # return address
    ret # return