#include "TransitionTable.h"

using namespace std;
TransitionTable::TransitionTable(bool isDeterministic) : is_deterministic(isDeterministic) {std::cout << "[INFO] New table created";}

const unordered_map<int, unordered_map<char, vector<int>>> &TransitionTable::getTable() const { return table;}

const unordered_map<int, string> &TransitionTable::getAcceptingStates() const {return accepting_states;}
