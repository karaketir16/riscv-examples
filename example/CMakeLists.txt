# Set the minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(RISCV_Project C ASM)

# Specify the target architecture for RISC-V
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR riscv32)

set(CMAKE_C_COMPILER "/opt/riscv32/bin/riscv32-unknown-elf-gcc")
set(CMAKE_ASM_COMPILER "/opt/riscv32/bin/riscv32-unknown-elf-gcc")

# Set the build type to Debug if not set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()


add_subdirectory(qemuUser)
add_subdirectory(qemuSystem)


#riscv64
#*multilib_defaults:
#march=rv64imafdc_zicsr_zifencei mabi=lp64d

#riscv32
#*multilib_defaults:
#march=rv32imafdc_zicsr_zifencei mabi=ilp32d
