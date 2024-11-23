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

#include "context.h"

// Machine mode interrupt service routine

// Global to hold current timestamp, written in MTI handler.
static volatile uint64_t timestamp = 0;
// Expect this to increment one time per second - inside exception handler, after each return of MTI handler.
static volatile uint64_t ecall_count = 0;

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

void sleepSomeTimeMsec(int m){
    int untilWait = mtimer_get_raw_time() + MTIMER_MSEC_TO_CLOCKS(m);
    while(mtimer_get_raw_time() < untilWait);
    return;
}

void task0(){
    while(1){
        print("ABCDE0\n");
        // sleepSomeTimeMsec(0);
    }
}

void task1(){
    while(1){
        print("FGHIJ1\n");
        // sleepSomeTimeMsec(0);
    }
}

uint8_t MyStackArea[1000 * MAX_TASKS + 1];

int main(void) {
    
    tasks[1].PC             = (uint_xlen_t) &task0;
    tasks[1].stackPointer   = (uint_xlen_t) &MyStackArea[1000]; //stack grow decreasing

    tasks[2].PC             = (uint_xlen_t) &task1;
    tasks[2].stackPointer   = (uint_xlen_t) &MyStackArea[2000];

    managerTask();

    // Will not reach here
    return 0;
}


