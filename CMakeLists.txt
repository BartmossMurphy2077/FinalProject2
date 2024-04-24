cmake_minimum_required(VERSION 3.27)
project(FinalProject2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(FinalProject2 main.c
        DB_Handler.c
        functions.h)
