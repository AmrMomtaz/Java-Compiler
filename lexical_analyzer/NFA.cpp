#include "NFA.h"

using namespace std;

NFA::NFA(const string &grammar_input_file) :
    grammarIo(grammar_input_file),
    transitionTable(false) {

    new_state_id = 1;
    log = true;
    nfaGraph.setRegularExpressions(grammarIo.get_regular_expressions());
}

void NFA::run() {
    handle_regular_definitions();
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
        pair<NfaNode*,NfaNode*> SE_nodes = nfaGraph.represent_token(keyword, new_state_id);
        nfaGraph.starting_nodes.push_back(SE_nodes.first);
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
        pair<NfaNode*,NfaNode*> SE_nodes =
                nfaGraph.represent_token(string(1,ch), new_state_id);
        nfaGraph.starting_nodes.push_back(SE_nodes.first);
        transitionTable.addAcceptingState(new_state_id-1, string(1, ch));
    }
    cout << "BOOM" << endl;
}

void NFA::handle_regular_definitions() {
    unordered_map<string, vector<string>> regular_definitions =
            grammarIo.get_regular_definitions();
    for (auto& pattern : regular_definitions) {
        const string& pattern_name = pattern.first;
        const vector<string>& pattern_tokens = pattern.second;
        pair<NfaNode*, NfaNode*> SE_nodes = perform_recursion(pattern_tokens, false, false);
        nfaGraph.starting_nodes.push_back(SE_nodes.first);
        transitionTable.addAcceptingState(SE_nodes.second->getId(), pattern_name);
    }
    cout << "Done" << endl;
}

pair<NfaNode*, NfaNode*> NFA::perform_recursion
    (const vector<string> &tokens, bool kleene_closure, bool positive_closure) {

    string prev_token;
    NfaNode* sentinelNode = new NfaNode(-1);
    NfaNode* ending_node = sentinelNode;
    for (int i = 0; i < tokens.size(); i++) {
        const string& token = tokens[i];
        if (token == "|" || token == "+" || token == "*" || token == "(" || token == ")") {

            if (token == "|") { // Union
                if (prev_token.empty() || i == tokens.size()-1) // Error cases
                    exit(-17);
                const string &next_token = tokens[++i];

                bool kleene = false, positive = false; // Lookahead
                if (i < tokens.size()-1) {
                    if (tokens[i+1] == "*") { kleene = true; i++; }
                    else if (tokens[i+1] == "+") { positive = true; i++; }
                }

                pair<NfaNode *, NfaNode *> SE_nodes =
                        nfaGraph.union_op(prev_token, next_token, new_state_id,
                                            kleene, positive);
                ending_node->add_child(0, SE_nodes.first);
                ending_node = SE_nodes.second;
                prev_token = "";
            }
            else if (token == "*") {
                if (prev_token.empty())
                    exit(-17);
                pair<NfaNode *, NfaNode *> SE_nodes =
                        nfaGraph.perform_kleene_closure(prev_token, new_state_id);
                ending_node->add_child(0, SE_nodes.first);
                ending_node = SE_nodes.second;
                prev_token = "";
            }
            else if (token == "+") {
                if (prev_token.empty())
                    exit(-17);
                pair<NfaNode *, NfaNode *> SE_nodes =
                        nfaGraph.perform_positive_closure(prev_token, new_state_id);
                ending_node->add_child(0, SE_nodes.first);
                ending_node = SE_nodes.second;
                prev_token = "";
            }
            else if (token == "(") {

            }
        } else {
            if (prev_token.empty())
                prev_token = token;
            else { // Concatenation
                bool kleene = false, positive = false; // Lookahead
                if (i < tokens.size()-1) {
                    if (tokens[i+1] == "*") { kleene = true; i++; }
                    else if (tokens[i+1] == "+") { positive = true; i++; }
                }
                pair<NfaNode *, NfaNode *> SE_nodes = nfaGraph.concatenate
                        (prev_token, token, new_state_id, kleene, positive);
                ending_node->add_child(0, SE_nodes.first);
                ending_node = SE_nodes.second;
                prev_token = "";
            }
        }
    }
    if (! prev_token.empty()) {
        pair<NfaNode *, NfaNode *> SE_nodes
                = nfaGraph.represent_token(prev_token, new_state_id);
        ending_node->add_child(0, SE_nodes.first);
        ending_node = SE_nodes.second;
        prev_token = "";
    }
    NfaNode* starting_node = sentinelNode->getChildren().at(0)[0];
    delete(sentinelNode);
    return {starting_node, ending_node};
}
