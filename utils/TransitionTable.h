#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <iostream>

#ifndef JAVA_COMPILER_TABLE_H
#define JAVA_COMPILER_TABLE_H

using namespace std;
/**
 * Represents the transition table which is used either in NFA or DFA.
 * If the boolean isDeterministic is set to true it adds additional checks
 *      which satisfies the DFA transition table.
 */
class TransitionTable {
private:
    // Represents the transition table rows and columns
    unordered_map<int, unordered_map<char,vector<int>>> table;
    // Hashtable which contains the accepting states with their tokens' names
    unordered_map<int, string> accepting_states;
    // Determines whether the table is for NFA or DFA
    bool is_deterministic;

public:
    explicit TransitionTable(bool isDeterministic);

    const unordered_map<int, unordered_map<char, vector<int>>> &getTable() const;

    const unordered_map<int, string> &getAcceptingStates() const;
};

#endif //JAVA_COMPILER_TABLE_H