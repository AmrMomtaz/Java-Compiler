#include "NFA.h"

using namespace std;

NFA::NFA(const string &grammar_input_file) : grammarIo(grammar_input_file),
    transitionTable(false) {

    new_state_id = 1;
    log = true;
}

void NFA::run() {
    handle_keywords_and_punctuations();
}

//
// Private methods
//

void NFA::handle_keywords_and_punctuations() {
    // handling keywords
    const vector<string>& keywords = grammarIo.get_keywords();
    if (log) {
        cout << "[INFO] Keywords are -> ";
        for (int i = 0 ; i < keywords.size(); i++)
            i == keywords.size() - 1 ?
                cout << keywords[i] << endl :
                cout << keywords[i] << ", " ;
    }
    for (auto& keyword : keywords) {
        NfaNode *prev_node = nfaGraph.create_new_node(new_state_id);
        nfaGraph.starting_nodes.push_back(prev_node);
        for (auto ch : keyword) {
            NfaNode *next_node = nfaGraph.create_new_node(new_state_id);
            prev_node->add_child(ch, next_node);
            prev_node = next_node;
        }
        transitionTable.addAcceptingState(new_state_id-1, keyword);
    }
    // handling punctuations
    const vector<char>& punctuations = grammarIo.get_punctuation();
    if (log) {
        cout << "[INFO] Punctuations are -> ";
        for (int i = 0 ; i < punctuations.size(); i++)
            i == punctuations.size() - 1 ?
                cout << punctuations[i] << endl :
                cout << punctuations[i] << " " ;
    }
    for (auto ch : punctuations) {
        NfaNode *first_node = nfaGraph.create_new_node(new_state_id);
        NfaNode *last_node = nfaGraph.create_new_node(new_state_id);
        first_node->add_child(ch, last_node);
        nfaGraph.starting_nodes.push_back(first_node);
        transitionTable.addAcceptingState(new_state_id-1, string(1, ch));
    }
}