.section .text
.globl start

# riscv64-unknown-elf-as -g entry.s -o entry.o && riscv64-unknown-elf-ld -T baremetal.ld entry.o -o entry
# qemu-system-riscv64 -machine virt -cpu sifive-u54 -smp 1 -s -S -nographic -bios none -kernel entry
# or 
# qemu-system-riscv64 -machine virt -cpu rv64 -smp 1 -s -S -nographic -bios none -kernel entry

start:
    # Load address of 'supervisor' into t0 and set mepc
    la      t0, supervisor
    csrw    mepc, t0

    # Load address of 'm_trap' into t1 and set mtvec
    la      t1, m_trap
    csrw    mtvec, t1

    # Set up PMP to allow S-mode and U-mode full access to memory
    li      t5, 0x1F               # NAPOT + R/W/X permissions
    csrw    pmpcfg0, t5            # Write to pmpcfg0
    li      t6, -1                 # All ones to cover entire address space
    csrw    pmpaddr0, t6           # Write to pmpaddr0

    # Correctly set MPP to Supervisor Mode
    csrr    t2, mstatus            # Read mstatus into t2
    li      t3, ~(0x3 << 11)       # Mask to clear MPP bits
    and     t2, t2, t3             # Clear MPP bits
    li      t4, (0x1 << 11)        # MPP = 01 (Supervisor Mode)
    or      t2, t2, t4             # Set MPP bits to 01
    csrw    mstatus, t2            # Write back to mstatus

    # Delegate ECALL from U-mode to S-mode
    li      t5, 0x100              # Exception code 8 (bit 8)
    csrs    medeleg, t5            # Delegate exception to S-mode

    mret                            # Return from M-mode to address in mepc

m_trap:
    csrr    t0, mepc               # Read mepc into t0
    csrr    t1, mcause             # Read mcause into t1
    la      t2, supervisor         # Load address of 'supervisor' into t2
    csrw    mepc, t2               # Write t2 to mepc
    mret                            # Return from M-mode to mepc

supervisor:
    # Disable virtual memory by setting satp to zero
    csrw    satp, x0               # Write zero to satp

    # Load address of 'user' into t0 and set sepc
    la      t0, user
    csrw    sepc, t0

    # Load address of 's_trap' into t1 and set stvec
    la      t1, s_trap
    csrw    stvec, t1

    sret                            # Return from S-mode to address in sepc

s_trap:
    csrr    t0, sepc               # Read sepc into t0
    csrr    t1, scause             # Read scause into t1
    ecall                          # Generate ECALL from S-mode (to M-mode)

user:
    csrr    t0, instret            # Read 'instret' into t0
    ecall                          # Generate ECALL from U-mode (to S-mode)

