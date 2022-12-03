#ifndef JAVA_COMPILER_DFA_H
#define JAVA_COMPILER_DFA_H

#include <queue>
#include <vector>
#include <map>
#include <unordered_set>
#include "../utils/TransitionTable.h"
#include "NFA.h"

using namespace std;
/**
 * Used to handle create the DFA from NFA.
 */
class DFA {
private:
//    TransitionTable NFA_transition_table;
    NFA nfa;
    TransitionTable transition_table;

    map<vector<int>, int> states_to_state_map;
    queue<vector<int>> states_queue;
    unordered_set<int> computed_states;
    int curr_state_num;

    // using each row of transition table to create one state out of a vector of states
    int get_or_create_state(const vector<int>& states_vector);
    void add_accepting_state(int state, const vector<int>& states);
    int compute_column(const vector<int>& states_vector);
    static vector<int> get_states_vector_from_set(const unordered_set<int>& states_set);
    unordered_set<int> get_epsilon_closure(const vector<int>& states);


public:
//    explicit DFA(TransitionTable NFATransitionTable);
    explicit DFA(NFA& nfa);

    TransitionTable &getTransitionTable();
};
#endif //JAVA_COMPILER_DFA_H
