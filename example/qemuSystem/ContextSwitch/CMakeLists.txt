# Set the minimum CMake version
cmake_minimum_required(VERSION 3.10)

set(ExecName context)

# Add the executable
add_executable(${ExecName} context.c entry.S inline.c dummy.c timer.c vector_table.c) #dummy is just for link test

set(LINKER_SCRIPT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/baremetal.ld")

target_link_options(${ExecName} PRIVATE "-T${LINKER_SCRIPT_PATH}")

# Link against the C library (usually newlib for embedded systems)
target_link_libraries(${ExecName})