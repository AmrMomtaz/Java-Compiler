cmake_minimum_required(VERSION 3.22)
project(Java_Compiler)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE
        main.cpp
        utils/TransitionTable.cpp
        utils/GrammarIO.cpp
        lexical_analyzer/NFA.cpp)

add_executable(java_compiler "${SOURCE}")

file(COPY grammar_input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})