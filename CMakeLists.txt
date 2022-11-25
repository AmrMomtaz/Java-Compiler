cmake_minimum_required(VERSION 3.22)
project(Java_Compiler)

set(CMAKE_CXX_STANDARD 17)

add_executable(Java_Compiler main.cpp)
add_library(Table utils/TransitionTable.cpp utils/TransitionTable.h)