cmake_minimum_required(VERSION 3.25)
project(project)

set(CMAKE_CXX_STANDARD 14)

include_directories("phase one")

add_executable(project
        "NFA.h"
        "node.h"
        "read_input.cpp"
        "utilities.h"
        "lexical_analyzer.cpp"
        "DFA.cpp"
        "DFA.cpp"
        "DFA_test.cpp"
        parser.cpp
        lexical_analyzer.h
        parser.h
        main.cpp
)
