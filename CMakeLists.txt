cmake_minimum_required(VERSION 3.21)
project(suffix_array C)
set(CMAKE_C_STANDARD 99)

add_compile_options(-Wextra -pedantic -Wall -Wno-unused-parameter)

add_executable(suffix_array main.c string_type.h string_type.c error_strings.h)
