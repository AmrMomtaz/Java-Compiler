#include "TransitionTable.h"

using namespace std;
TransitionTable::TransitionTable(bool isDeterministic) : is_deterministic(isDeterministic) {std::cout << "[INFO] New table created" << "\n";}
TransitionTable::TransitionTable(bool isDeterministic, unordered_map<int, unordered_map<char, vector<int>>> table_map, unordered_map<int, string> accepting_states_map,int starting_state_int) : is_deterministic(isDeterministic) {table = table_map; accepting_states=accepting_states_map; starting_state=starting_state_int; std::cout << "[INFO] New table created" << "\n";}

// Setter
void TransitionTable::setTable(unordered_map<int, unordered_map<char, vector<int>>> table_map){table = table_map;}
// Getter
const unordered_map<int, unordered_map<char, vector<int>>> &TransitionTable::getTable() const { return table;}

// Setter
void TransitionTable::setAcceptingStates(unordered_map<int, string> accepting_states_map){accepting_states = accepting_states_map;}
// Getter
const unordered_map<int, string> &TransitionTable::getAcceptingStates() const {return accepting_states;}

// Setter
void TransitionTable::setStartingStates(int starting_state_int){starting_state = starting_state_int;}
// Getter
const int &TransitionTable::getStartingState() const {return starting_state;}

const bool &TransitionTable::isDeterministic() const {return is_deterministic;}
