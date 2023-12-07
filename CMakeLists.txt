cmake_minimum_required(VERSION 3.25)
project(project)

set(CMAKE_CXX_STANDARD 14)

include_directories("phase one")

add_executable(project
        "phase one/NFA.h"
        "phase one/node.h"
        "phase one/read_input.cpp"
        "phase one/utilities.h"
        "phase one/DFA_test.cpp"
        "phase one/DFA.cpp"
        "phase one/lexical_analyzer.cpp")
