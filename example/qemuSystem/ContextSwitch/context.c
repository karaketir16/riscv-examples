#include "riscv-interrupts.h"
#include "timer.h"
#include "vector_table.h"

#include "context.h"

// Define naked attribute for functions
#define NAKED __attribute__((naked))

// Function declarations for saving and restoring context
static inline void save_context() __attribute__((always_inline));
static inline void restore_context() __attribute__((always_inline));

static inline void save_current_task() __attribute__((always_inline));
static inline void restore_next_task() __attribute__((always_inline));

TaskContext tasks[MAX_TASKS];
int currentTaskID = 0;


#define UART_BASE 0x10000000

// Function to write a character to UART
static void uart_putchar(char c) {
    *((volatile char *)UART_BASE) = c;
}

// Function to print a string to UART
static void print(const char *str) {
    while (*str) {
        uart_putchar(*str++);
    }
}


#pragma GCC push_options
// Force the alignment for mtvec.BASE. A 'C' extension program could be aligned to bytes.
#pragma GCC optimize ("align-functions=4")


#define SWITCH_PERIOD 100

#define RISCV_MTVEC_MODE_VECTORED 1

void managerTask(){

    // Global interrupt disable
    csr_clr_bits_mstatus(MSTATUS_MIE_BIT_MASK);
    csr_write_mie(0);
    
    // Setup the IRQ handler entry point, set the mode to vectored
    csr_write_mtvec((uint_xlen_t) riscv_mtvec_table | RISCV_MTVEC_MODE_VECTORED);

    // Enable MIE.MTI
    csr_set_bits_mie(MIE_MTI_BIT_MASK);

    mtimer_set_raw_time_cmp(MTIMER_MSEC_TO_CLOCKS(SWITCH_PERIOD));

    // Global interrupt enable 
    set_with_csrrsi(mstatus, MSTATUS_MIE_BIT_MASK); // Without modifying any general purphose regsiters, but inportant in this case, we started it just
    
    while(1); //wait for other tasks
}

// The 'riscv_mtvec_mti' function is added to the vector table by vector_table.c
void riscv_mtvec_mti(void) {
    // Save context of the current task, storing a0 before calling save_context
    save_context();
    
    save_current_task();

    // Timer exception, re-program the timer for a one second tick.
    mtimer_set_raw_time_cmp(MTIMER_MSEC_TO_CLOCKS(SWITCH_PERIOD));

    // Move to the next task
    currentTaskID = (currentTaskID + 1) % (MAX_TASKS); 
    currentTaskID = (currentTaskID == 0) ? currentTaskID + 1 : currentTaskID; //NOT RETURN TO tasks[0] managerTask

    restore_next_task();

    // Restore context of the next task
    restore_context();

    __asm__ volatile (
        "mret"
        :
        :
        : "memory"
    );
}

// The 'riscv_mtvec_exception' function is added to the vector table by vector_table.c
// This function looks at the cause of the exception, if it is an 'ecall' instruction then increment a global counter.
void riscv_mtvec_exception(void) {
    uint_xlen_t val = csr_read_mstatus() & MSTATUS_MIE_BIT_MASK;
    uint_xlen_t this_cause = csr_read_mcause();
    uint_xlen_t this_pc    = csr_read_mepc();
    //uint_xlen_t this_value = csr_read_mtval();
    switch (this_cause) {
        case RISCV_EXCP_ENVIRONMENT_CALL_FROM_M_MODE:
            // Make sure the return address is the instruction AFTER ecall
            csr_write_mepc(this_pc + 4);
            break;
    }
}

// Save context in RISC-V
void save_context() {
    __asm__ volatile (
        // Store general-purpose registers
        "addi  sp, sp, -272    \n"
        "sw    ra, 252(sp)     \n"
        "sw    t0, 248(sp)     \n"
        "sw    t1, 244(sp)     \n"
        "sw    t2, 240(sp)     \n"
        "sw    s0, 236(sp)     \n"
        "sw    s1, 232(sp)     \n"
        "sw    a0, 228(sp)     \n"
        "sw    a1, 224(sp)     \n"
        "sw    a2, 220(sp)     \n"
        "sw    a3, 216(sp)     \n"
        "sw    a4, 212(sp)     \n"
        "sw    a5, 208(sp)     \n"
        "sw    a6, 204(sp)     \n"
        "sw    a7, 200(sp)     \n"
        "sw    t3, 196(sp)     \n"
        "sw    t4, 192(sp)     \n"
        "sw    t5, 188(sp)     \n"
        "sw    t6, 184(sp)     \n"
        // Store floating-point registers
        // "fsd   ft0, 176(sp)    \n"
        // "fsd   ft1, 168(sp)    \n"
        // "fsd   ft2, 160(sp)    \n"
        // "fsd   ft3, 152(sp)    \n"
        // "fsd   ft4, 144(sp)    \n"
        // "fsd   ft5, 136(sp)    \n"
        // "fsd   ft6, 128(sp)    \n"
        // "fsd   ft7, 120(sp)    \n"
        // "fsd   fa0, 112(sp)    \n"
        // "fsd   fa1, 104(sp)    \n"
        // "fsd   fa2, 96(sp)     \n"
        // "fsd   fa3, 88(sp)     \n"
        // "fsd   fa4, 80(sp)     \n"
        // "fsd   fa5, 72(sp)     \n"
        // "fsd   fa6, 64(sp)     \n"
        // "fsd   fa7, 56(sp)     \n"
        // "fsd   ft8, 48(sp)     \n"
        // "fsd   ft9, 40(sp)     \n"
        // "fsd   ft10, 32(sp)    \n"
        // "fsd   ft11, 24(sp)    \n"
        :
        :
        : "memory"
    );
}

void save_current_task()
{
    register uintptr_t sp asm("sp");
    tasks[currentTaskID].stackPointer = sp;
    tasks[currentTaskID].PC = csr_read_mepc();
}

// Restore context in RISC-V
void restore_context() {
    __asm__ volatile (
        // Restore general-purpose registers
        "lw    ra, 252(sp)     \n"
        "lw    t0, 248(sp)     \n"
        "lw    t1, 244(sp)     \n"
        "lw    t2, 240(sp)     \n"
        "lw    s0, 236(sp)     \n"
        "lw    s1, 232(sp)     \n"
        "lw    a0, 228(sp)     \n"
        "lw    a1, 224(sp)     \n"
        "lw    a2, 220(sp)     \n"
        "lw    a3, 216(sp)     \n"
        "lw    a4, 212(sp)     \n"
        "lw    a5, 208(sp)     \n"
        "lw    a6, 204(sp)     \n"
        "lw    a7, 200(sp)     \n"
        "lw    t3, 196(sp)     \n"
        "lw    t4, 192(sp)     \n"
        "lw    t5, 188(sp)     \n"
        "lw    t6, 184(sp)     \n"
        // Restore floating-point registers
        // "fld   ft0, 176(sp)    \n"
        // "fld   ft1, 168(sp)    \n"
        // "fld   ft2, 160(sp)    \n"
        // "fld   ft3, 152(sp)    \n"
        // "fld   ft4, 144(sp)    \n"
        // "fld   ft5, 136(sp)    \n"
        // "fld   ft6, 128(sp)    \n"
        // "fld   ft7, 120(sp)    \n"
        // "fld   fa0, 112(sp)    \n"
        // "fld   fa1, 104(sp)    \n"
        // "fld   fa2, 96(sp)     \n"
        // "fld   fa3, 88(sp)     \n"
        // "fld   fa4, 80(sp)     \n"
        // "fld   fa5, 72(sp)     \n"
        // "fld   fa6, 64(sp)     \n"
        // "fld   fa7, 56(sp)     \n"
        // "fld   ft8, 48(sp)     \n"
        // "fld   ft9, 40(sp)     \n"
        // "fld   ft10, 32(sp)    \n"
        // "fld   ft11, 24(sp)    \n"
        // Increment stack pointer back to its original value
        "addi  sp, sp, 272     \n"
        :
        :
        : "memory"
    );
}

void restore_next_task()
{
    register uintptr_t sp asm("sp");
    sp = tasks[currentTaskID].stackPointer;
    csr_write_mepc(tasks[currentTaskID].PC);
}

#pragma GCC pop_options
