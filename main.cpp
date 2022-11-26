#include "lexical_analyzer/NFA.h"
using namespace std;
/**
 * Driver code (starting point of the project)
 */
int main() {
    NFA nfa("grammar_input.txt");
    nfa.run();
    return 0;
}
