#include "../utils/GrammarIO.h"

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
    explicit NFA(const string &grammar_input_file);
    void run();
};

#endif //JAVA_COMPILER_NFA_H
