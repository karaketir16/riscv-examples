# Set the minimum CMake version
cmake_minimum_required(VERSION 3.10)

set(ExecName addijx)

# Add the executable
add_executable(${ExecName} main.c addijx.s)

# Link against the C library (usually newlib for embedded systems)
target_link_libraries(${ExecName})

# Specify the linker script if needed (optional)
# set(CMAKE_EXE_LINKER_FLAGS "-T your_linker_script.ld")

# Optional: Add custom commands to run the program with QEMU
add_custom_target(run_${ExecName}
    COMMAND qemu-riscv32-static ${ExecName}
    DEPENDS ${ExecName}
    COMMENT "Running the program with QEMU"
)
