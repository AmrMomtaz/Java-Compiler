#include "../utils/GrammarIO.h"
#include "../utils/NfaGraph.h"
#include "../utils/TransitionTable.h"
#include <stack>

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
    int new_state_id;
    bool log;

    void handle_keywords_and_punctuations();
    void handle_regular_definitions();
    pair<NfaNode*, NfaNode*> perform_recursion(const vector<string>& tokens,
                                               bool kleene_closure, bool positive_closure);
public:
    explicit NFA(const string &grammar_input_file);
    // Driver code of NFA
    void run();
};

#endif //JAVA_COMPILER_NFA_H
