cmake_minimum_required(VERSION 3.15)
project(DATATYPE C)

set(CMAKE_C_STANDARD 99)

add_executable(DATATYPE main.c typedef.h circle_queue.c test_circle_queue.h circle_queue.h stack.c stack.h test_stack.h)