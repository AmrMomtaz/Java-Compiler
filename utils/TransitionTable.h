#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>

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
    const bool is_deterministic;

public:
    explicit TransitionTable(bool isDeterministic);
    explicit TransitionTable(bool isDeterministic, const unordered_map<int, unordered_map<char,
                             vector<int>>>& table_map,const unordered_map<int,string>& accepting_states_map,
                             int starting_state_int);
    explicit TransitionTable(bool isDeterministic, const unordered_map<int, unordered_map<char,vector<int>>>& table,
                             const unordered_map<int, string>& accepting_states);
    // Adds new state to the accepting states
    void addAcceptingState(int state,const string& state_name);

    void saveTableToFile(string path);

    // Getters
    unordered_map<int, unordered_map<char, vector<int>>> &getTable();
    unordered_map<int, string>& getAcceptingStates();
    const int &getStartingState()const;
    const bool &isDeterministic() const;

    // Setters
    void setAcceptingStates(const unordered_map<int, string>& accepting_states_map);
    void setTable(const unordered_map<int, unordered_map<char, vector<int>>>& table_map);
    void setStartingStates(int ss);
};

#endif //JAVA_COMPILER_TABLE_H