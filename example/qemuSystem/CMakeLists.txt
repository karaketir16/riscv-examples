# Set the minimum CMake version
cmake_minimum_required(VERSION 3.10)


# Set the compiler flags
set(CMAKE_C_FLAGS "-nostdlib -static")
set(CMAKE_ASM_FLAGS "-nostdlib -static")

add_subdirectory(privilege)
add_subdirectory(qemuBare)