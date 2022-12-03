#include "lexical_analyzer/NFA.h"
#include "lexical_analyzer/DFA.h"
#include "utils/TransitionTable.h"
#include "utils/GrammarIO.h"
#include "lexical_analyzer/LexicalAnalyzerTest.cpp"

using namespace std;

/**
 * Driver code (starting point of the project)
 */
int main() {
    NFA nfa("grammar_input.txt");
    DFA dfa(nfa);
    dfa.run();
    dfa.get_DFA();
    int x = 0;
    return 0;
}
