# Set the minimum CMake version
cmake_minimum_required(VERSION 3.10)

set(ExecName writeTest)

# Add the executable
add_executable(${ExecName} assembly.s)

# Link against the C library (usually newlib for embedded systems)
target_link_libraries(${ExecName})

# Specify the linker script if needed (optional)
# set(CMAKE_EXE_LINKER_FLAGS "-T your_linker_script.ld")


