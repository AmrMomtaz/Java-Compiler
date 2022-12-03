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
    DFA_Minimized dfa_min(dfa.get_DFA());
    dfa_min.optimize_dfa();
    LexicalAnalyzer LA(dfa_min.get_DFA_Minimized());
//    LexicalAnalyzer LA(dfa.get_DFA());

    string input_text="";
    ifstream myfile; myfile.open("test_program.txt");
    if ( myfile.is_open() ) {
        char mychar;
        while (myfile) {
            mychar = myfile.get();
            input_text+=mychar;
        }
    }
    cout << input_text << "\n";
    myfile.close();

    //split the input text on the white space
    vector<string> words = split_string_by_white_spaces(input_text);
    for (auto word = words.begin(); word != words.end(); ++word) {
//        cout << *word << "\n";
        vector<pair<string, string>> tokens = LA.getAllTokensInText(*word);
        for (auto i = tokens.begin(); i != tokens.end(); ++i) {
            pair<string, string> token = *i;
            cout << token.first << " : " << token.second << "\n";
        }
    }
    return 0;
}
