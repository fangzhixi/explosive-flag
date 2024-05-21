cmake_minimum_required(VERSION 3.26)
project(explosive_flag C)

set(CMAKE_C_STANDARD 17)

add_executable(explosive_flag main.c
        explosive_flag.h
        tools.c)
