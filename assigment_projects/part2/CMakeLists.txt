cmake_minimum_required(VERSION 3.27)
project(part2 C)

set(CMAKE_C_STANDARD 11)

add_library(library SHARED library/library.c)

add_executable(part2 main.c)

target_link_libraries(part2 library)