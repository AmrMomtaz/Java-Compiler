#include <string>
#include "../utils/GrammarIO.cpp"

#ifndef JAVA_COMPILER_NFA_H
#define JAVA_COMPILER_NFA_H

using namespace std;
/**
 * Used to handle create the NFA using thompson's algorithm.
 */
class NFA {
private:
    GrammarIO grammarIo;
public:
    NFA(const string &grammar_input_file);
};


#endif //JAVA_COMPILER_NFA_H
