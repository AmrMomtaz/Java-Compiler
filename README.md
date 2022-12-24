# Java Compiler
## Overview
This project was part of CS421 Introduction to Compilers course project. This repository contains the first two phases:
### 1. Lexical Analyzer
The lexical analyzer generator is required to automatically construct a lexical analyzer given some regular expressions descriping set of tokens. The tool is required to construct a nondeterministic finite automata (NFA) for the given regular expressions, combine these NFAs together with a new starting state, convert the resulting NFA to a DFA, minimize it and emit the transition table for the reduced DFA together with a lexical analyzer program that simulates the resulting DFA machine.

### 2. Parser Generator
The parser generator expects a grammar as input. It should compute First and Follow sets and uses them to construct a predictive parsing table for the grammar.
The table is to be used to drive a predictive top-down parser. A bonus task we included is converting any grammar to be LL(1).
<br><br>
<h3><b>Please refer to the docs directory for full description of each phase and all the implementation details are found in the reports.</b></h3>
