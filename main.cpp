#include "lexical_analyzer/NFA.h"
#include "lexical_analyzer/DFA.h"
#include "lexical_analyzer/DFA_Minimized.h"
#include "utils/TransitionTable.h"
#include "utils/GrammarIO.h"
#include "lexical_analyzer/LexicalAnalyzerTest.cpp"
#include "parser_generator/GrammarParser.h"
#include "parser_generator/Parser.h"
#include "parser_generator/LLOneGrammarGenerator.h"
#include "parser_generator/FF_Generator.h"

using namespace std;

/**
 * Driver code (starting point of the project)
 */
int main() {
    NFA nfa("grammar_input.txt");
    DFA dfa(nfa);
    DFA_Minimized dfa_min(dfa.getTransitionTable());

    TransitionTable TT = dfa_min.getMinimizedTransitionTable();
    TT.saveTableToFile("minimalDFA.txt");
    LexicalAnalyzer LA(TT);

    GrammarParser grammarParser("parser_grammar.txt");
    unordered_map<string, vector<vector<string>>>& productions = grammarParser.getProductions();
    cout << grammarParser.getStartingSymbol() << endl;
    string ss = grammarParser.getStartingSymbol();

    LLOneGrammarGenerator ll1_gen(productions);
    unordered_map<string, vector<vector<string>>> grammar = ll1_gen.get_ll_one_grammar();

    FF_Generator ff_gen(grammar, ss);

    unordered_map<string, pair<vector<pair<string,vector<string>>>, set<string>>> ff_out
        = ff_gen.getProductions();

    Parser PA(LA, ff_out);
    if (PA.valid_parsing_table) {
        PA.printParsingTable("parsing_table_output_file.txt");
        PA.parseInput(ss, "test_program.txt", "test_program_output.txt",
                      "left_most_derivation_output_file.txt", "stack_events_and_errors.txt");
    } else cout << "Cannot parsing as, the grammar is ambiguous!" << endl;

    return 0;
}
