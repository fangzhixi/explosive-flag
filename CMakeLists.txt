cmake_minimum_required(VERSION 3.26)
project(explosive_flag C)

set(CMAKE_C_STANDARD 11)

include_directories(src/tools)

add_executable(explosive_flag
        src/demo/test1.c
        src/demo/test2.c
        src/include/explosive_flag.h
        src/tools/explosive_flag.c
        src/demo/main.c
        src/demo/main.h)
