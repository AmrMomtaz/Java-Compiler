#include "NFA.h"

using namespace std;

NFA::NFA(const string &grammar_input_file) : grammarIo(grammar_input_file) {
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
        cout << "[INFO] Keywords are : ";
        for (int i = 0 ; i < keywords.size(); i++)
            i == keywords.size()-1 ?
                cout << keywords[i] << endl :
                cout << keywords[i] << ", " ;
    }
    for (auto& keyword : keywords) {
        nfaGraph.create_new_node(new_state_id);
    }
}
