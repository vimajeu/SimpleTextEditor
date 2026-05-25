cmake_minimum_required(VERSION 4.2)
project(SimpleTextEditor C)

set(CMAKE_C_STANDARD 11)

add_executable(SimpleTextEditor main.c
        buffer.c
        buffer.h
)
