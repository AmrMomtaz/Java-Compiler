#include "lexical_analyzer/NFA.h"
#include "lexical_analyzer/DFA.h"
#include "lexical_analyzer/DFA_Minimized.h"
#include "utils/TransitionTable.h"
#include "utils/GrammarIO.h"
#include "lexical_analyzer/LexicalAnalyzerTest.cpp"
#include "parser_generator/GrammarParser.h"

using namespace std;

/**
 * Driver code (starting point of the project)
 */
int main() {
    ///Dyh el 7agat el Adeema
//    NFA nfa("grammar_input.txt");
//    DFA dfa(nfa);
//    DFA_Minimized dfa_min(dfa.getTransitionTable());
//    //print the minimal DFA
//    TransitionTable TT = dfa_min.getMinimizedTransitionTable();
//    TT.saveTableToFile("minimalDFA.txt");
//    LexicalAnalyzer LA(TT);
//    LA.tokensInTextInFile("test_program.txt", "test_program_output.txt");
//    cout << "-------- Symbol Table --------" << "\n";
//    for (auto v : LA.getSymbolTable())
//        cout << v.first << "|" << v.second << "\n";

    GrammarParser grammarParser("parser_grammar.txt");
    unordered_map<string, vector<string>>& productions = grammarParser.getProductions();
    cout << "Done" << endl;
    return 0;
}
