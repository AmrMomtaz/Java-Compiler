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
    vector<NfaNode> children;
};


#endif //JAVA_COMPILER_NFANODE_H
