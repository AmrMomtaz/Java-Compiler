#include "NFA.h"

using namespace std;

NFA::NFA(const string &grammar_input_file) :
    grammarIo(grammar_input_file),
    transitionTable(false) {

    new_state_id = 1;
    log = true;
    nfaGraph.setRegularExpressions(grammarIo.get_regular_expressions());
    handle_keywords_and_punctuations();
    handle_regular_definitions();
    initialize_table();
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
}

pair<NfaNode*, NfaNode*> NFA::perform_recursion
    (const vector<string> &tokens, bool kleene_closure, bool positive_closure) {

    string prev_token;
    pair<NfaNode* , NfaNode*> prev_pair;
    NfaNode* sentinelNode = new NfaNode(-1);
    NfaNode* kleene_closure_node = nullptr;
    NfaNode* ending_node = sentinelNode;
    if (kleene_closure)
        kleene_closure_node = nfaGraph.create_new_node(new_state_id);
    for (int i = 0; i < tokens.size(); i++) {
        const string& token = tokens[i];
        if (token == "|" || token == "+" || token == "*" || token == "(" || token == ")") {

            if (token == "|") { // union
                if (i == tokens.size()-1) // error cases
                    exit(-17);
                string next_token = tokens[++i];
                if (next_token == "(") {
                    vector<string> new_tokens;
                    int count = 0;
                    while (tokens[++i] != ")" || count) {
                        new_tokens.push_back(tokens[i]);
                        if (tokens[i] == "(")
                            count++;
                        else if (tokens[i] == ")")
                            count--;
                    }
                    bool kleene = false, positive = false; // Lookahead
                    if (i < tokens.size()-1) {
                        if (tokens[i+1] == "*") { kleene = true; i++; }
                        else if (tokens[i+1] == "+") { positive = true; i++; }
                    }
                    pair<NfaNode*, NfaNode*> SE_nodes2 = perform_recursion(new_tokens, kleene, positive);
                    pair<NfaNode *, NfaNode *> SE_nodes;
                    if (! prev_token.empty()) {
                        SE_nodes = nfaGraph.union_op(SE_nodes2, prev_token, new_state_id, kleene, positive);
                        delete(sentinelNode);
                        sentinelNode = new NfaNode(-1);
                        sentinelNode->add_child(0, SE_nodes.first);
                        ending_node = SE_nodes.second;
                        prev_token = "";
                    }
                    else {
                        SE_nodes = nfaGraph.union_op(SE_nodes2, prev_pair, new_state_id);
                        delete(sentinelNode);
                        sentinelNode = new NfaNode(-1);
                        sentinelNode->add_child(0, SE_nodes.first);
                        ending_node = SE_nodes.second;
                    }
                }
                else {
                    next_token = GrammarIO::clean_token(next_token);
                    bool kleene = false, positive = false; // Lookahead
                    if (i < tokens.size()-1) {
                        if (tokens[i+1] == "*") { kleene = true; i++; }
                        else if (tokens[i+1] == "+") { positive = true; i++; }
                    }
                    pair<NfaNode *, NfaNode *> SE_nodes;
                    if (! prev_token.empty()) {
                        SE_nodes = nfaGraph.union_op(prev_token, next_token, new_state_id, kleene, positive);
                        ending_node->add_child(0, SE_nodes.first);
                        prev_token = "";
                    }
                    else {
                        SE_nodes = nfaGraph.union_op(prev_pair, next_token, new_state_id, kleene, positive);
                        delete(sentinelNode);
                        sentinelNode = new NfaNode(-1);
                        sentinelNode->add_child(0, SE_nodes.first);
                    }
                    ending_node = SE_nodes.second;
                    prev_pair = SE_nodes;
                }
            }
            else if (token == "*") { // kleene closure
                if (prev_token.empty())
                    exit(-17);
                pair<NfaNode *, NfaNode *> SE_nodes =
                        nfaGraph.perform_kleene_closure(prev_token, new_state_id);
                prev_pair = SE_nodes;
                ending_node->add_child(0, SE_nodes.first);
                ending_node = SE_nodes.second;
                prev_token = "";
            }
            else if (token == "+") {  // positive closure
                if (prev_token.empty())
                    exit(-17);
                pair<NfaNode *, NfaNode *> SE_nodes =
                        nfaGraph.perform_positive_closure(prev_token, new_state_id);
                prev_pair = SE_nodes;
                ending_node->add_child(0, SE_nodes.first);
                ending_node = SE_nodes.second;
                prev_token = "";
            }
            else if (token == "(") {
                vector<string> new_tokens;
                int count = 0;
                while (tokens[++i] != ")" || count) {
                    new_tokens.push_back(tokens[i]);
                    if (tokens[i] == "(")
                        count++;
                    else if (tokens[i] == ")")
                        count--;
                }
                bool kleene = false, positive = false; // Lookahead
                if (i < tokens.size()-1) {
                    if (tokens[i+1] == "*") { kleene = true; i++; }
                    else if (tokens[i+1] == "+") { positive = true; i++; }
                }
                if (prev_token.empty()) {
                    pair<NfaNode *, NfaNode *> SE_nodes = perform_recursion(new_tokens, kleene, positive);
                    ending_node->add_child(0, SE_nodes.first);
                    ending_node = SE_nodes.second;
                }
                else {
                    pair<NfaNode *, NfaNode *> SE_nodes1 = nfaGraph.represent_token(prev_token, new_state_id);
                    pair<NfaNode *, NfaNode *> SE_nodes2 = perform_recursion(new_tokens, kleene, positive);
                    SE_nodes1.second->add_child(0, SE_nodes2.first);
                    ending_node->add_child(0, SE_nodes1.first);
                    ending_node = SE_nodes2.second;
                    prev_token = "";
                }
            }
        } else {
            if (prev_token.empty())
                prev_token = GrammarIO::clean_token(token);
            else { // Concatenation
                bool kleene = false, positive = false; // Lookahead
                if (i < tokens.size()-1) {
                    if (tokens[i+1] == "*") { kleene = true; i++; }
                    else if (tokens[i+1] == "+") { positive = true; i++; }
                }
                pair<NfaNode *, NfaNode *> SE_nodes = nfaGraph.concatenate
                        (prev_token, GrammarIO::clean_token(token), new_state_id, kleene, positive);
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
    if (kleene_closure) {
        kleene_closure_node->add_child(0, starting_node);
        kleene_closure_node->add_child(0, ending_node);
        ending_node->add_child(0, starting_node);
        return {kleene_closure_node, ending_node};
    }
    else if (positive_closure)
        ending_node->add_child(0, starting_node);
    return {starting_node, ending_node};
}

void NFA::initialize_table() {
    NfaNode* initial_node = new NfaNode(0);
    for (NfaNode* starting_node : nfaGraph.starting_nodes)
        initial_node->add_child(0, starting_node);

    unordered_set<int> visited_nodes;
    unordered_map<int, unordered_map<char,vector<int>>> table;
    dfs(initial_node, transitionTable.getTable(), visited_nodes);
}

void NFA::dfs(NfaNode* root, unordered_map<int, unordered_map<char,vector<int>>>& table, unordered_set<int>& visited_nodes) {
    int current_row = root->getId();
    if (visited_nodes.find(current_row) == visited_nodes.end()) {
        visited_nodes.insert(current_row);
        for (pair<const char,vector<NfaNode*>>  map_entry : root->getChildren()) {
            for (NfaNode* child : map_entry.second) {
                table[current_row][map_entry.first].push_back(child->getId());
                dfs(child, table, visited_nodes);
            }
        }
    }
}

TransitionTable &NFA::getTransitionTable() {
    return transitionTable;
}

string NFA::get_highest_priority(vector<string>& accepting_states) {
    for (string& accepting_state : accepting_states) {
        if (accepting_state == "boolean" || accepting_state == "int" || accepting_state == "float"
            || accepting_state == "if" || accepting_state == "else" || accepting_state == "while")
            return accepting_state;
    }
    return accepting_states[0];
}