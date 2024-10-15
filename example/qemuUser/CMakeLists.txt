# Set the minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Set the compiler flags (now with zicsr extension included)
set(CMAKE_C_FLAGS "-ggdb")
set(CMAKE_ASM_FLAGS "-ggdb")

add_subdirectory(bookAddijx)
add_subdirectory(greatestInArray)
add_subdirectory(helloWorld)
add_subdirectory(factorialReq)
add_subdirectory(writeTest)
add_subdirectory(sum)

