#include "TransitionTable.h"

TransitionTable::TransitionTable(bool isDeterministic) : is_deterministic(isDeterministic) {
    std::cout << "[INFO] New transition table is created." << endl;
}
TransitionTable::TransitionTable(bool isDeterministic, unordered_map<int, unordered_map<char,
                                 vector<int>>> table_map, unordered_map<int, string> accepting_states_map,
                                 int starting_state_int) : is_deterministic(isDeterministic) {

    table = table_map;
    accepting_states = accepting_states_map;
    starting_state = starting_state_int;
    cout << "[INFO] New table created" << "\n";
}

void TransitionTable::addAcceptingState(int state, const string &state_name) {
    accepting_states[state] = state_name;
}

// Getters
const unordered_map<int, unordered_map<char, vector<int>>> &TransitionTable::getTable() const {
    return table;
}
const unordered_map<int, string> &TransitionTable::getAcceptingStates() const {
    return accepting_states;
}
const int &TransitionTable::getStartingState() const {
    return starting_state;
}
const bool &TransitionTable::isDeterministic() const {
    return is_deterministic;
}
// Setters
void TransitionTable::setTable(unordered_map<int, unordered_map<char, vector<int>>> table_map) {
    table = table_map;
}
void TransitionTable::setStartingStates(int starting_state_int) {
    starting_state = starting_state_int;
}
void TransitionTable::setAcceptingStates(unordered_map<int, string> accepting_states_map) {
    accepting_states = accepting_states_map;
}