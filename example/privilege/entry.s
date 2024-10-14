.section .text
.globl start

start:
    la      t0, supervisor         # Load address of 'supervisor' into t0
    csrw    mepc, t0               # Write t0 to mepc
    la      t1, m_trap             # Load address of 'm_trap' into t1
    csrw    mtvec, t1              # Write t1 to mtvec

    # Set up PMP to allow S-mode and U-mode full access to memory
    li      t5, 0x1f               # NAPOT + RWX
    csrw    pmpcfg0, t5            # Write to pmpcfg0
    li      t6, -1                 # All ones to cover entire address space
    csrw    pmpaddr0, t6           # Write to pmpaddr0

    # Correctly set MPP to Supervisor Mode
    csrr    t2, mstatus            # Read mstatus into t2
    li      t3, ~(0x3 << 11)       # Create mask to clear MPP bits
    and     t2, t2, t3             # Clear MPP bits
    li      t4, 0x1 << 11          # Set MPP to Supervisor Mode (0x1)
    or      t2, t2, t4             # Set MPP bits to 01
    csrw    mstatus, t2            # Write back to mstatus

    # Delegate ECALL from U-mode to S-mode
    li      t5, 0x100              # Exception code 8 (bit 8)
    csrs    medeleg, t5            # Delegate exception to S-mode

    mret                            # Return from machine mode to mepc


m_trap:
    csrr    t0, mepc
    csrr    t1, mcause
    la      t2, supervisor
    csrw    mepc, t2
    mret

supervisor:
    # Disable virtual memory by setting satp to zero
    csrw    satp, x0               # Write zero to satp

    la      t0, user               # Load address of 'user' into t0
    csrw    sepc, t0               # Write t0 to sepc
    la      t1, s_trap             # Load address of 's_trap' into t1
    csrw    stvec, t1              # Write t1 to stvec
    sret                            # Return from supervisor mode to sepc


s_trap:
    csrr    t0, sepc
    csrr    t1, scause
    ecall

user:
    csrr    t0, instret
    ecall