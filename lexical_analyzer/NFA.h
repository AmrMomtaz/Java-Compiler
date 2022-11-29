#include "../utils/GrammarIO.h"
#include "../utils/NfaGraph.h"

#ifndef JAVA_COMPILER_NFA_H
#define JAVA_COMPILER_NFA_H

using namespace std;
/**
 * Used to handle create the NFA using thompson's algorithm.
 */
class NFA {
private:
    GrammarIO grammarIo;
    unordered_map<int, vector<int>> epsilon_closure;
    NfaGraph nfaGraph;
    int new_state_id;
    bool log;

    void handle_keywords_and_punctuations();
public:
    explicit NFA(const string &grammar_input_file);
    // driver code of NFA
    void run();
};

#endif //JAVA_COMPILER_NFA_H
