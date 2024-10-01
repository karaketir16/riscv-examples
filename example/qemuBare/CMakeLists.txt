# Set the minimum CMake version
cmake_minimum_required(VERSION 3.10)

set(ExecName qemuBare)


# Set the compiler flags
set(CMAKE_C_FLAGS "-march=rv32im -mabi=ilp32 -nostdlib -static")
set(CMAKE_ASM_FLAGS "-march=rv32im -mabi=ilp32 -nostdlib -static")

# Add the executable
add_executable(${ExecName} assembly.s)


set(LINKER_SCRIPT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/baremetal.ld")

target_link_options(${ExecName} PRIVATE "-T${LINKER_SCRIPT_PATH}")

# Link against the C library (usually newlib for embedded systems)
target_link_libraries(${ExecName})


# Specify the linker script if needed (optional)
# set(CMAKE_EXE_LINKER_FLAGS "-T baremetal.ld")


