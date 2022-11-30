#include "lexical_analyzer/NFA.h"
#include "utils/TransitionTable.h"
#include "utils/GrammarIO.h"

using namespace std;

/**
 * Driver code (starting point of the project)
 */
int main() {
    NFA nfa("grammar_input.txt");
    nfa.run();
    return 0;
}
