# Set the minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(RISCV_Project C ASM)

# Specify the target architecture for RISC-V
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR riscv32)

# Set the build type to Debug if not set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()


add_subdirectory(qemuUser)
add_subdirectory(qemuSystem)
