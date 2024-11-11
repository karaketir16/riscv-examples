# Set the minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Set the compiler flags (now with zicsr extension included)
set(CMAKE_C_FLAGS "-march=rv32im -mabi=ilp32 -ggdb")
set(CMAKE_ASM_FLAGS "-march=rv32im -mabi=ilp32 -ggdb")

add_subdirectory(bookAddijx)
add_subdirectory(greatestInArray)
add_subdirectory(helloWorld)
add_subdirectory(factorialReq)
add_subdirectory(writeTest)
add_subdirectory(sum)

