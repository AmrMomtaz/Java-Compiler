#include "NfaNode.h"

#ifndef JAVA_COMPILER_NFAGRAPH_H
#define JAVA_COMPILER_NFAGRAPH_H

/**
 * Utils for NFA graph
 */
class NfaGraph {
public:
    // Contains the starting nodes of each pattern.
    vector<NfaNode *> starting_nodes;
    // Creates new node INCREMENTS the new_id.
    NfaNode* create_new_node(int& new_id);
};


#endif //JAVA_COMPILER_NFAGRAPH_H
