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
    // The index of the starting state
    int starting_state;
    // Determines whether the table is for NFA or DFA
    bool is_deterministic;

public:
    explicit TransitionTable(bool isDeterministic);
    explicit TransitionTable(bool isDeterministic, unordered_map<int, unordered_map<char,
                             vector<int>>> table_map, unordered_map<int,string> accepting_states_map,
                             int starting_state_int);
    // Adds new state to the accepting states
    void addAcceptingState(int state,const string& state_name);

    // Getters
    const unordered_map<int, unordered_map<char, vector<int>>> &getTable() const;
    const unordered_map<int, string>& getAcceptingStates() const;
    const int &getStartingState()const;
    const bool &isDeterministic() const;

    // Setters
    void setAcceptingStates(unordered_map<int, string> accepting_states_map);
    void setTable(unordered_map<int, unordered_map<char, vector<int>>> table_map);
    void setStartingStates(int ss);
};

#endif //JAVA_COMPILER_TABLE_H