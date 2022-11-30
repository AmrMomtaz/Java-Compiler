#include "NfaNode.h"

#ifndef JAVA_COMPILER_NFAGRAPH_H
#define JAVA_COMPILER_NFAGRAPH_H

/**
 * Utils for NFA graph
 */
class NfaGraph {
private:
    unordered_map<string, vector<char>> regular_expressions;
public:
    // Contains the starting nodes of each pattern.
    vector<NfaNode *> starting_nodes;

    void setRegularExpressions(const unordered_map<string, vector<char>> &regularExpressions);

    /**
     * Creates new node increments the new_id.
     */
    NfaNode* create_new_node(int& new_id);

    /**
     * Returns the graph which corresponds to a certain token.
     */
    pair<NfaNode*, NfaNode*> represent_token(const string& token, int& new_id);

    /**
     * Performs concatenation between two tokens.
     */
    pair<NfaNode*, NfaNode*> concatenate(const string& token1, const string& token2, int& new_id,
                                         bool kleene_closure, bool positive_closure);

    /**
     * Performs union between two tokens.
     */
    pair<NfaNode*, NfaNode*> union_op(const string& token1, const string& token2, int& new_id,
                                      bool kleene_closure, bool positive_closure);

    /**
     *  Performs kleene closure.
     */
    pair<NfaNode*, NfaNode*> perform_kleene_closure(const string& token, int& new_id);

    /**
     *  Performs positive closure.
     */
    pair<NfaNode*, NfaNode*> perform_positive_closure(const string& token, int& new_id);
};


#endif //JAVA_COMPILER_NFAGRAPH_H
