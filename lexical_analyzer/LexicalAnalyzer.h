#ifndef JAVA_COMPILER_LEXICALANALYZER_H
#define JAVA_COMPILER_LEXICALANALYZER_H
#include <map>
#include <sstream>

#include "../utils/TransitionTable.h"

class LexicalAnalyzer {
private:
    //The transition table of the minimum DFA
    //to be used for tokenizing
    TransitionTable TT;//the lexical analyzer has only one unchangeable DFA
    string text;
    int current_char_idx = 0;
    map<string , string> symbol_table;
public:
    explicit LexicalAnalyzer(TransitionTable& tt);

    // Setter
    void setText(string s);
    // Getter
    const string &getText() const;

    // Setter
    void setCurrentIndex(int i);
    // Getter
    const int &getCurrentIndex() const;

    //return the next token and his type
    pair<string ,string> getNextToken();

    //return the next token and his type
    vector<pair<string ,string>> getAllTokens();

    //return the next token and his type
    vector<string> adv_tokenizer(string s, char del);
    vector<string> split_string_by_white_spaces(string s);

    //return the next token and his type
    vector<pair<string ,string>> getAllTokensInText(string text);

    void tokensInTextInFile(string input_path, string output_path);

    // Getter
    const map<string , string> &getSymbolTable()const;
};


#endif //JAVA_COMPILER_LEXICALANALYZER_H
