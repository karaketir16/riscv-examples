#pragma once

#include "riscv-csr.h"

typedef struct TaskContext_t {
    uint_xlen_t stackPointer;
    uint_xlen_t PC;
} TaskContext;

#define MAX_TASKS 3

extern TaskContext tasks[MAX_TASKS];
extern int currentTaskID;


void managerTask();

// Generic macro to set a CSR register with an immediate mask using csrrsi
#define set_with_csrrsi(reg, mask)                                \
        __asm__ volatile ("csrrsi zero, " #reg ", %0" : : "i"(mask))


