cmake_minimum_required(VERSION 3.20)
project(pc C)

set(CMAKE_C_STANDARD 90)

add_executable(pc main.c linked_list.h linked_list.c colour_linked_list.h colour_linked_list.c)