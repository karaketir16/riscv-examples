# Set the minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(RISCV_Project C ASM)

# Specify the target architecture for RISC-V
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR riscv32)

# Specify the cross-compiler
set(CMAKE_C_COMPILER "riscv32-unknown-elf-gcc")
set(CMAKE_ASM_COMPILER "riscv32-unknown-elf-gcc")

# Set the compiler flags
set(CMAKE_C_FLAGS "-march=rv32im -mabi=ilp32")
set(CMAKE_ASM_FLAGS "-march=rv32im -mabi=ilp32")

# Set the build type to Debug if not set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_subdirectory(bookAddijx)
add_subdirectory(greatestInArray)
add_subdirectory(helloWorld)
add_subdirectory(factorialReq)
add_subdirectory(writeTest)
add_subdirectory(qemuBare)

