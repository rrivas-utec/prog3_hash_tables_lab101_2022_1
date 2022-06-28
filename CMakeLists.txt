cmake_minimum_required(VERSION 3.22)
project(prog3_hash_tables_lab101_2022_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(${CMAKE_PROJECT_NAME}
        main.cpp
        chash.h ohash.h)
