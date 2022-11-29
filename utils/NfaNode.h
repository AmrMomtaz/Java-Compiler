#include <iostream>
#include <unordered_map>
#include <vector>

#ifndef JAVA_COMPILER_NFANODE_H
#define JAVA_COMPILER_NFANODE_H

using namespace std;
/**
 * Represents node in the NFA Graph.
 */
class NfaNode {
private:
    int id;
    unordered_map<char, vector<NfaNode *>> children;
public:
    // Constructor
    explicit NfaNode(int id);
    // Adds new child node
    void add_child(char ch, NfaNode *child);

    // Getters
    int getId() const;
    const unordered_map<char, vector<NfaNode *>> &getChildren() const;
};


#endif //JAVA_COMPILER_NFANODE_H
