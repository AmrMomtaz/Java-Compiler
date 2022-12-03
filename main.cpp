#include "lexical_analyzer/NFA.h"
#include "lexical_analyzer/DFA.h"
#include "lexical_analyzer/DFA_Minimized.h"
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
    DFA_Minimized dfa_min(dfa.getTransitionTable());
    LexicalAnalyzer LA(dfa_min.getMinimizedTransitionTable());

    string input_text;
    ifstream fh;
    fh.open("test_program.txt");
    if (fh.is_open()) {
        char ch;
        while (fh) {
            ch = fh.get();
            input_text+=ch;
        }
    }
    cout << input_text << "\n";
    fh.close();

    // split the input text on the white space
    vector<string> words = split_string_by_white_spaces(input_text);
    for (auto word = words.begin(); word != words.end(); ++word) {
        vector<pair<string, string>> tokens = LA.getAllTokensInText(*word);
        for (auto i = tokens.begin(); i != tokens.end(); ++i) {
            pair<string, string> token = *i;
            cout << token.first << " : " << token.second << "\n";
        }
    }
    return 0;
}
