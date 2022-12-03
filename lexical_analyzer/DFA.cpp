#include "DFA.h"
#include <algorithm>
#include <utility>
#include <vector>
#include <unordered_set>
using namespace std;

DFA::DFA(NFA& nfaObj) : nfa(nfaObj), transition_table(TransitionTable(true)), curr_state_num(0) {
    compute_column(vector<int>{0});
    while (! states_queue.empty()) {
        vector<int> states_vector = states_queue.front();
        states_queue.pop();

        // get the new state number
        int state_number = states_to_state_map[states_vector];
        unordered_map<char, vector<int>> row;

        // <3,4,5> -> [a -> <5,6,5,2>]
        //    .        .        .
        //    .        .        .
        //    .        .        .
        for (int state : states_vector) {
            unordered_map<char, vector<int>>& NFA_columns = nfa.getTransitionTable().getTable().at(state);

            // a -> <5, 6>
            // .  .    .
            // .  .    .
            // .  .    .
            for (auto& it: NFA_columns) {
                if (it.first == 0) continue;
                // concatenate the values of the vector with the values in a -> <2, 3> for different states
                row[it.first].insert(row[it.first].end(), it.second.begin(), it.second.end());
            }
        }

        // remove the repetition and create states for each
        for (const auto &it: row)
            row[it.first] = vector<int>{compute_column(it.second)};

        transition_table.getTable()[state_number] = row;
    }

//    states_to_state_map.clear();
    states_queue = {};
    computed_states.clear();
}

vector<int> DFA::get_states_vector_from_set(const unordered_set<int>& states_set) {
    vector<int> states_vector(states_set.begin(), states_set.end());
    sort(states_vector.begin(), states_vector.end());
    return states_vector;
}

int DFA::get_or_create_state(const vector<int>& states_vector) {
    if (states_to_state_map.find(states_vector) != states_to_state_map.end())   // if it exists
        return states_to_state_map[states_vector];

    // if it doesn't exist then create a new number for it and update the accepting states and return the new number
    states_to_state_map[states_vector] = curr_state_num;
    add_accepting_state(curr_state_num, states_vector);
    return curr_state_num++;
}

int DFA::compute_column(const vector<int>& states) {
    const vector<int> states_vector = get_states_vector_from_set(get_epsilon_closure(states));
    int new_state = get_or_create_state(states_vector);
    if (computed_states.find(new_state) == computed_states.end()) { // if not found
        states_queue.push(states_vector);
        computed_states.insert(new_state);
    }
    return new_state;
}

void DFA::add_accepting_state(int new_state, const vector<int>& states) {
    const unordered_map<int, string>& NFA_accepting_states = nfa.getTransitionTable().getAcceptingStates();
    vector<string> accepting_state_strings;
    for (int state : states) {
        if (NFA_accepting_states.find(state) != NFA_accepting_states.end()) {
            accepting_state_strings.push_back(NFA_accepting_states.at(state));
//            accepting_states[new_state] = NFA_accepting_states.at(state);
//            return;
        }
    }
    if (! accepting_state_strings.empty())
        transition_table.addAcceptingState(new_state,  nfa.get_highest_priority(accepting_state_strings));
}

unordered_set<int> DFA::get_epsilon_closure(const vector<int>& states_vector){
    // create a queue for nodes to check
    // create a set to check whether already accessed
    // create a set for the current number of nodes
        // if number before and after doesn't change or nothing to be added to the queue
        // and queue size is zero then leave

    const unordered_map<int, unordered_map<char, vector<int>>>& transition_table = nfa.getTransitionTable().getTable();
    queue<int> epsilon_states_queue;
    unordered_set<int> closure;

    for (int state_value : states_vector) {
        if (closure.find(state_value) != closure.end())
            continue;

        epsilon_states_queue.push(state_value);
        closure.insert(state_value);
        while (! epsilon_states_queue.empty()) {
            int curr_state = epsilon_states_queue.front();
            epsilon_states_queue.pop();
//            if(curr_state == 102){
//                cout << "here";
//            }
            if (transition_table.at(curr_state).find(0) == transition_table.at(curr_state).end()) // doesn't have any epsilon transitions
                continue;

            vector<int> epsilon_transitions = transition_table.at(curr_state).at(0);
            for (int value : epsilon_transitions) {
                // if already visited then skip it to not waste time
                if (closure.find(value) != closure.end())
                    continue;

                closure.insert(value);
                epsilon_states_queue.push(value);
            }
        }
    }
    return closure;
}

TransitionTable &DFA::getTransitionTable() {
    return transition_table;
}

