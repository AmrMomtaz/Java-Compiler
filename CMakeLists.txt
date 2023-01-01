cmake_minimum_required(VERSION 3.22)
project(Java_Compiler)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE
        main.cpp
        utils/TransitionTable.cpp
        utils/GrammarIO.cpp
        utils/NfaNode.cpp
        utils/NfaGraph.cpp
        lexical_analyzer/NFA.cpp
        lexical_analyzer/DFA.cpp
        lexical_analyzer/DFA_Minimized.cpp
        lexical_analyzer/LexicalAnalyzer.cpp
        parser_generator/Parser.cpp
        parser_generator/GrammarParser.cpp
        parser_generator/LLOneGrammarGenerator.h
        parser_generator/LLOneGrammarGenerator.cpp
        parser_generator/FF_Generator.cpp)

add_executable(java_compiler "${SOURCE}")

file(COPY grammar_input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY test_program.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY test_program_output.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY left_most_derivation_output_file.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY stack_events_and_errors.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY minimalDFA.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY parser_grammar.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})