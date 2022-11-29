#include "NfaNode.h"

NfaNode::NfaNode(int id) : id(id) {}

void NfaNode::add_child(char ch, NfaNode *child) {
    children[ch].push_back(child);
}

int NfaNode::getId() const {
    return id;
}

const unordered_map<char, vector<NfaNode *>> &NfaNode::getChildren() const {
    return children;
}
