.globl array
.globl func
.text
func:
li a0, 0x80000000   # a0 for storing result, its saved from caller. 0x80000000 is min for signed int
la t0, array        # t0 for storing pointer to array
li t1, 10           # t1 is loop counter

loop:
    addi t1, t1, -1
    
    lw t2, 0(t0)       # get array elem from addr
    #compare
    blt t2, a0, less    
    mv  a0, t2      # current is greater
less:
    addi t0, t0, 4  # next array elem
    
    beqz t1, end    # done if zero
    j loop  
end:
ret
