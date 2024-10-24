.option norvc
.section .data
.section .text.init
.global _start

_start:
    # Set up PMP to allow S-mode and U-mode full access to memory
    li      t5, 0x1F               # NAPOT + R/W/X permissions
    csrw    pmpcfg0, t5            # Write to pmpcfg0
    li      t6, -1                 # All ones to cover entire address space
    csrw    pmpaddr0, t6           # Write to pmpaddr0


    li      t0, 0x1800
    csrc    mstatus, t0
    li      t0, 0x802
    csrs    mstatus, t0
    li      t0, 0xa0 
    csrs    mie, t0
    li      t0, 0x20
    csrs    mideleg, t0
    la      t0, mtrap
    csrw    mtvec, t0
    li      t0, 0xa000
    li      t1, 0x2004000
    sw      t0, 0(t1)
    la      t1, supervisor
    csrw    mepc, t1
    mret

mtrap:
    mv t5, t0
    mv t6, t1
    # Check if the interrupt was a timer interrupt (from mip)
    li      t0, 0x80            # 0x80 corresponds to the MTIP (Machine Timer Interrupt Pending) bit
    csrr    t3, mip 
    and     t1, t0, t3         # Check if the timer interrupt is pending
    beqz    t1, other_interrupt # If it's not a timer interrupt, handle other interrupts

    # Handle timer interrupt
    li      t0, 0x200BFF8
    lw      t0, 0(t0)
    li      t1, 0x20000
    add     t0, t0, t1      # Load next timer value (for example, 0xb000 cycles later)
    li      t1, 0x2004000       # Memory-mapped address of mtimecmp
    sw      t0, 0(t1)           # Reset mtimecmp with a new future value
    
    #mret                         # Return to the previous mode (S-mode)
    li      t0, 0x20
    csrs    mip, t0

    j       m_trap_ret

other_interrupt:
    # Handle other types of interrupts here (e.g., software interrupt)
    csrr    t0, mcause
    li      t1, 0x9
    beq     t0, t1, reset_sip; # if t0 == t1 then target
not_expected:
    j       not_expected

reset_sip:
    li      t0, 0x20
    csrc    mip, t0
    csrr    t0, mepc
    addi    t0, t0, 4
    csrw    mepc, t0
    j       m_trap_ret

m_trap_ret:
    mv t0, t5
    mv t1, t6
    mret

supervisor:
    li      t0, 20
    la      t0, strap
    csrw    stvec, t0
    j       spin

strap:
    ecall
    sret

spin:
    li      t0, 0x200BFF8
    lw      t0, 0(t0)
    li      t1, 0x2004000
    lw      t1, 0(t1)
    j       spin
