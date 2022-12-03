#include "NfaGraph.h"

void NfaGraph::setRegularExpressions(const unordered_map<string, vector<char>> &regularExpressions) {
    regular_expressions = regularExpressions;
}

NfaNode* NfaGraph::create_new_node(int& new_id) {
    return new NfaNode(new_id++);
}

pair<NfaNode *, NfaNode *> NfaGraph::represent_token(const string &token, int& new_id) {
    NfaNode* starting_node = create_new_node(new_id);
    NfaNode* ending_node = nullptr;
    if (regular_expressions.find(token) == regular_expressions.end()) {
        NfaNode *prev_node = starting_node;
        for (auto ch : token) {
            NfaNode *next_node = create_new_node(new_id);
            prev_node->add_child(ch, next_node);
            prev_node = next_node;
        }
        ending_node = prev_node;
    } else {
        const vector<char>& chars = regular_expressions.at(token);
        ending_node = create_new_node(new_id);
        for (char ch : chars) {
            starting_node->add_child(ch, ending_node);
        }
    }
    return {starting_node, ending_node};
}

pair<NfaNode *, NfaNode *> NfaGraph::concatenate
    (const string &token1, const string &token2, int& new_id,
     bool kleene_closure, bool positive_closure) {

    pair<NfaNode*, NfaNode*> SE_nodes1 = represent_token(token1, new_id);

    NfaNode* kleene_first = nullptr;
    if (kleene_closure) kleene_first = create_new_node(new_id);
    pair<NfaNode*, NfaNode*> SE_nodes2 = represent_token(token2, new_id);

    if (! kleene_closure)
        SE_nodes1.second->add_child(0, SE_nodes2.first);
    else {
        SE_nodes1.second->add_child(0, kleene_first);
        kleene_first->add_child(0, SE_nodes2.first);
        kleene_first->add_child(0, SE_nodes2.second);
    }
    if (kleene_closure || positive_closure)
        SE_nodes2.second->add_child(0, SE_nodes2.first);
    return {SE_nodes1.first, SE_nodes2.second};
}

pair<NfaNode *, NfaNode *> NfaGraph::union_op
    (const string &token1, const string &token2, int &new_id,
     bool kleene_closure, bool positive_closure) {

    NfaNode* first_node = create_new_node(new_id);
    pair<NfaNode*, NfaNode*> SE_nodes1 = represent_token(token1, new_id);

    NfaNode* kleene_first = nullptr;
    if (kleene_closure) kleene_first = create_new_node(new_id);
    pair<NfaNode*, NfaNode*> SE_nodes2 = represent_token(token2, new_id);

    NfaNode* last_node = create_new_node(new_id);
    SE_nodes1.second->add_child(0, last_node);
    SE_nodes2.second->add_child(0, last_node);
    first_node->add_child(0, SE_nodes1.first);

    if (kleene_closure) {
        first_node->add_child(0, kleene_first);
        kleene_first->add_child(0, SE_nodes2.first);
        kleene_first->add_child(0, SE_nodes2.second);
    }
    else
        first_node->add_child(0, SE_nodes2.first);
    if (kleene_closure || positive_closure)
        SE_nodes2.second->add_child(0, SE_nodes2.first);
    return {first_node, last_node};
}

pair<NfaNode *, NfaNode *>NfaGraph::union_op
        (const pair<NfaNode *, NfaNode *> &SE_nodes1, const string &token2,
         int &new_id, bool kleene_closure, bool positive_closure) {

    NfaNode* first_node = create_new_node(new_id);
    NfaNode* kleene_first = nullptr;
    if (kleene_closure) kleene_first = create_new_node(new_id);
    pair<NfaNode*, NfaNode*> SE_nodes2 = represent_token(token2, new_id);

    NfaNode* last_node = create_new_node(new_id);
    SE_nodes1.second->add_child(0, last_node);
    SE_nodes2.second->add_child(0, last_node);
    first_node->add_child(0, SE_nodes1.first);

    if (kleene_closure) {
        first_node->add_child(0, kleene_first);
        kleene_first->add_child(0, SE_nodes2.first);
        kleene_first->add_child(0, SE_nodes2.second);
    }
    else
        first_node->add_child(0, SE_nodes2.first);
    if (kleene_closure || positive_closure)
        SE_nodes2.second->add_child(0, SE_nodes2.first);
    return {first_node, last_node};
}

pair<NfaNode *, NfaNode *>NfaGraph::union_op
    (const pair<NfaNode *, NfaNode *> &SE_nodes1, const pair<NfaNode *, NfaNode *> &SE_nodes2, int &new_id) {

    NfaNode* first_node = create_new_node(new_id);
    NfaNode* last_node = create_new_node(new_id);
    SE_nodes1.second->add_child(0, last_node);
    SE_nodes2.second->add_child(0, last_node);
    first_node->add_child(0, SE_nodes1.first);
    first_node->add_child(0, SE_nodes2.first);
    return {first_node, last_node};
}

pair<NfaNode *, NfaNode *> NfaGraph::perform_kleene_closure(const string &token, int &new_id) {
    NfaNode* kleene_first = create_new_node(new_id);
    pair<NfaNode*, NfaNode*> SE_nodes = represent_token(token, new_id);
    SE_nodes.second->add_child(0, SE_nodes.first);
    kleene_first->add_child(0, SE_nodes.first);
    kleene_first->add_child(0, SE_nodes.second);
    return {kleene_first, SE_nodes.second};
}

pair<NfaNode *, NfaNode *> NfaGraph::perform_positive_closure(const string &token, int &new_id) {
    pair<NfaNode*, NfaNode*> SE_nodes = represent_token(token, new_id);
    SE_nodes.second->add_child(0, SE_nodes.first);
    return {SE_nodes.first, SE_nodes.second};
}
