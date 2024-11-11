/*
   Baremetal main program with timer interrupt.
   SPDX-License-Identifier: Unlicense

   https://five-embeddev.com/

   Tested with sifive-hifive-revb, but should not have any
   dependencies to any particular implementation.
   
*/

// RISC-V CSR definitions and access classes
#include "riscv-csr.h"
#include "riscv-interrupts.h"
#include "timer.h"

#include "vector_table.h"

// Machine mode interrupt service routine

// Global to hold current timestamp, written in MTI handler.
static volatile uint64_t timestamp = 0;
// Expect this to increment one time per second - inside exception handler, after each return of MTI handler.
static volatile uint64_t ecall_count = 0;

#define RISCV_MTVEC_MODE_VECTORED 1

int main(void) {
    // Global interrupt disable
    csr_clr_bits_mstatus(MSTATUS_MIE_BIT_MASK);
    csr_write_mie(0);
    
    // Setup the IRQ handler entry point, set the mode to vectored
    csr_write_mtvec((uint_xlen_t) riscv_mtvec_table | RISCV_MTVEC_MODE_VECTORED);

    // Enable MIE.MTI
    csr_set_bits_mie(MIE_MTI_BIT_MASK);

    // Global interrupt enable 
    csr_set_bits_mstatus(MSTATUS_MIE_BIT_MASK);

    // Setup timer for 1 second interval
    timestamp = mtimer_get_raw_time();
    mtimer_set_raw_time_cmp(MTIMER_SECONDS_TO_CLOCKS(1));
    
    // Busy loop
    do {
        // Wait for timer interrupt
        __asm__ volatile ("wfi");
        // Try a synchronous exception.
        uint_xlen_t val = csr_read_mstatus() & MSTATUS_MIE_BIT_MASK;
        __asm__ volatile ("ecall");
    } while (1);
    
    // Will not reach here
    return 0;
}


