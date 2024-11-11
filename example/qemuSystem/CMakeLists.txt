# Set the minimum CMake version
cmake_minimum_required(VERSION 3.10)


# Set the compiler flags
set(CMAKE_C_FLAGS "-march=rv32imd_zicsr -mabi=ilp32d -nostdlib -static")
set(CMAKE_ASM_FLAGS "-march=rv32imd_zicsr -mabi=ilp32d -nostdlib -static")

add_subdirectory(privilege)
add_subdirectory(qemuBare)
add_subdirectory(timer)
add_subdirectory(inlineTest)
add_subdirectory(ContextSwitch)