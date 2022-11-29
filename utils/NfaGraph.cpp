#include "NfaGraph.h"

NfaNode* NfaGraph::create_new_node(int& new_id) {
    return new NfaNode(new_id++);
}
