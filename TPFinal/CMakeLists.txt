project(TPFinal C)

cmake_minimum_required(VERSION 3.14)
set(CMAKE_C_STANDARD 99)

enable_testing()
set(CMAKE_C_FLAGS "-Wall -Werror -std=c11")

add_subdirectory(src)
add_subdirectory(test)
