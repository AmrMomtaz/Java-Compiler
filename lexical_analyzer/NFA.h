#include "../utils/GrammarIO.h"
#include "../utils/NfaGraph.h"
#include "../utils/TransitionTable.h"

#ifndef JAVA_COMPILER_NFA_H
#define JAVA_COMPILER_NFA_H

using namespace std;
/**
 * Used to handle the creation of NFA using thompson's algorithm.
 */
class NFA {
private:
    NfaGraph nfaGraph;
    GrammarIO grammarIo;
    TransitionTable transitionTable;
    unordered_map<int, vector<int>> epsilon_closure;
    int new_state_id;
    bool log;

    void handle_keywords_and_punctuations();
public:
    explicit NFA(const string &grammar_input_file);
    // Driver code of NFA
    void run();
};

#endif //JAVA_COMPILER_NFA_H
