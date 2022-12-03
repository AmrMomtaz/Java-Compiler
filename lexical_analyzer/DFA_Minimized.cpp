#include "DFA_Minimized.h"

using namespace std;

DFA_Minimized::DFA_Minimized(TransitionTable& trans_table) : tt(trans_table),
    new_transition_table(TransitionTable(true)) {

    cout << "[INFO] New DFA Minimizer created." << "\n";
}

bool DFA_Minimized::minimize(list<list<int>> &curr_partitions,
                             int n_partitions, const int indices[],
                             unordered_map<int, string> & accepting_states,
                             const unordered_map<int, unordered_map<char, vector<int>>> &table) {

    list<list<int>> new_partitions;

    while (!curr_partitions.empty()) {
        auto i = curr_partitions.front();
        curr_partitions.pop_front();

        while (!i.empty()) {
            int base_state = i.front();
            i.pop_front();

            list<int> temp;
            temp.push_back(base_state);
            auto j = i.begin();

            while (j != i.end()) {
                if (is_equiv(base_state, *j, indices,
                             accepting_states, table)) {
                    temp.push_back(*j);
                    j = i.erase(j);
                }
                else
                    j++;
            }
            new_partitions.push_back(temp);
        }
    }

    if (n_partitions == new_partitions.size()) {
        curr_partitions = new_partitions;
        return false;
    }

    curr_partitions = new_partitions;
    return true;
}

bool DFA_Minimized::is_equiv(int state_p, int state_q, const int indices[],
                             unordered_map<int, string> & accepting_states,
                             const unordered_map<int, unordered_map<char, vector<int>>> &table) {

    int dead_state = (int) table.size();
    unordered_map<char, vector<int>> trans_p;
    unordered_map<char, vector<int>> trans_q;

    if (state_p != dead_state)
        trans_p = table.at(state_p);
    if (state_q != dead_state)
        trans_q = table.at(state_q);

    if (accepting_states.find(state_p) != accepting_states.end() &&
            accepting_states.find(state_q) != accepting_states.end()) {
        if (accepting_states[state_p] != accepting_states[state_q])
            return false;
    }

    bool flag = true;
    int u = 0, v = 0;

    // Check all the transitions of state p.
    for (auto kv : trans_p) {
        u = kv.second[0];
        v = (trans_q.find(kv.first) != trans_q.end()) ? trans_q[kv.first][0] : dead_state;
        flag &= indices[u] == indices[v];
        if (!flag)
            return flag;
    }

    // Check all the transitions of state q.
    for (auto kv : trans_q) {
        u = kv.second[0];
        v = (trans_p.find(kv.first) != trans_p.end()) ? trans_p[kv.first][0] : dead_state;
        flag &= indices[u] == indices[v];
        if (!flag)
            return flag;
    }

    return flag;
}

void DFA_Minimized::optimize_dfa() {

    int ss = 0;
    unordered_map<int, unordered_map<char, vector<int>>>& table = tt.getTable();
    unordered_map<int, string>& accepting_states = tt.getAcceptingStates();

    list<int> non_finals;
    list<int> finals;

    int indices[table.size() + 1];

    for(auto & kv : table) {
        if (accepting_states.find(kv.first) == accepting_states.end()) {
            non_finals.push_back(kv.first);
            indices[kv.first] = 0;
        }
        else {
            finals.push_back(kv.first);
            indices[kv.first] = 1;
        }
    }

    // Defining dead state.
    int dead_state = (int) table.size();
    non_finals.push_back(dead_state);
    indices[dead_state] = 0;

    // Creating partitions.
    list<list<int>> partitions;
    partitions.push_back(non_finals);
    partitions.push_back(finals);

    // Start partitioning.
    while (minimize(partitions, (int) partitions.size(), indices,
                    accepting_states, table)) {
        int idx = 0;
        for (auto & i : partitions) {
            for (auto & j : i)
                indices[j] = idx;
            idx++;
        }
    }

    // Creating new Transition Table.
    int new_ss = indices[ss];

    for (auto & i : partitions) {
        int u = i.front();
        unordered_map<char, vector<int>> trans_u;
        if (u != dead_state)
            trans_u = table.at(u);
        else
            continue;

        if (accepting_states.find(u) != accepting_states.end())
            new_transition_table.addAcceptingState(indices[u], accepting_states.at(u));

        for (auto & kv : trans_u)
            new_transition_table.getTable()[indices[u]][kv.first] = vector<int> {indices[kv.second[0]]};
    }

    new_transition_table.setStartingStates(new_ss);
}

TransitionTable DFA_Minimized::get_DFA_Minimized() {
    return new_transition_table;
}