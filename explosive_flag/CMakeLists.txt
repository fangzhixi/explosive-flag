cmake_minimum_required(VERSION 3.26)
project(explosive_flag C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(explosive_flag
        explosive_flag.h
        main.c
        tools.c)
