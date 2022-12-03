#include "TransitionTable.h"

TransitionTable::TransitionTable(bool isDeterministic) : is_deterministic(isDeterministic) {
    std::cout << "[INFO] New transition table is created." << endl;
}
TransitionTable::TransitionTable(bool isDeterministic, const unordered_map<int, unordered_map<char,
                                 vector<int>>>& table_map, const unordered_map<int, string>& accepting_states_map,
                                 int starting_state_int) : is_deterministic(isDeterministic)
                                 , table(table_map), accepting_states(accepting_states_map)  {

    starting_state = starting_state_int;
    cout << "[INFO] New table created" << "\n";
}

TransitionTable::TransitionTable(bool isDeterministic, const unordered_map<int, unordered_map<char,vector<int>>> &table,
                                 const unordered_map<int, string>& accepting_states) : is_deterministic(isDeterministic)
                                 , table(table), accepting_states(accepting_states){}


void TransitionTable::addAcceptingState(int state, const string &state_name) {
    accepting_states[state] = state_name;
}

// Getters
unordered_map<int, unordered_map<char, vector<int>>> &TransitionTable::getTable() {
    return table;
}
unordered_map<int, string> &TransitionTable::getAcceptingStates() {
    return accepting_states;
}
const int &TransitionTable::getStartingState() const {
    return starting_state;
}
const bool &TransitionTable::isDeterministic() const {
    return is_deterministic;
}
// Setters
void TransitionTable::setStartingStates(int starting_state_int) {
    starting_state = starting_state_int;
}

void TransitionTable::setAcceptingStates(const unordered_map<int, string> &accepting_states_map) {
    accepting_states = accepting_states_map;
}

void TransitionTable::setTable(const unordered_map<int, unordered_map<char, vector<int>>> &table_map) {
    table = table_map;
}