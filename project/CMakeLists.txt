cmake_minimum_required(VERSION 3.26)
project(project C)

set(CMAKE_C_STANDARD 23)

add_executable(project main.c
        tools.c)
