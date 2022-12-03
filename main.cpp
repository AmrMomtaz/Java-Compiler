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
    TransitionTable TT = dfa.get_DFA();
    ///get the lexical analyzer
    LexicalAnalyzer LA(TT);

    string input_text="";
    ifstream myfile; myfile.open("C:\\Users\\momen\\OneDrive\\Documents\\GitHub\\Java-Compiler\\test_program.txt");
    if ( myfile.is_open() ) {
        char mychar;
        while ( myfile ) {
            mychar = myfile.get();
            input_text+=mychar;
        }
    }
    cout << input_text << "\n";

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
