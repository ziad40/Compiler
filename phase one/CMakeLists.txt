cmake_minimum_required(VERSION 3.26)
project(phase_one)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(phase_one
        DFA.cpp
        NFA.cpp
        node.cpp
        read_input.cpp
        utilities.cpp)
