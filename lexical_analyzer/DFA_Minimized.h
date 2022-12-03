#ifndef JAVA_COMPILER_DFA_MINIMIZED_H
#define JAVA_COMPILER_DFA_MINIMIZED_H

#include "../utils/TransitionTable.h"
#include <list>

using namespace std;

class DFA_Minimized {
private:
    TransitionTable tt;
    bool minimize(list<list<int>> & curr_partitions,
                  int n_partitions, int indices[],
                  const unordered_map<int, unordered_map<char, vector<int>>>& table);
    bool is_equiv(int state_p,
                  int state_q,
                  int indices[],
                  const unordered_map<int, unordered_map<char, vector<int>>>& table);
public:
    explicit DFA_Minimized(TransitionTable trans_table);
    void optimize_dfa();
};

#endif //JAVA_COMPILER_DFA_MINIMIZED_H
