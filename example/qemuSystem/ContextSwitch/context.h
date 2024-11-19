#pragma once

#include "riscv-csr.h"

typedef struct TaskContext_t {
    uint_xlen_t* stackPointer;
    uint_xlen_t* PC;
} TaskContext;

#define MAX_TASKS 2

extern TaskContext tasks[MAX_TASKS];
extern int currentTaskID;
