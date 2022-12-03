#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>

#ifndef JAVA_COMPILER_GRAMMARIO_H
#define JAVA_COMPILER_GRAMMARIO_H

using namespace std;
/**
 * Provide utils to read grammar from input file.
 */
class GrammarIO {
private:
    string grammar_input_file;
    unordered_map<string, string> gg;
    static bool is_regular_expression(const string& first_word);
    static unordered_map<string, vector<char>> parse_regular_expression
        (vector<string> &regular_expressions);
    static bool is_regular_definition(const string& first_word);
    static unordered_map<string, vector<string>> parse_regular_definition
        (vector<string> &regular_definitions);
public:
    explicit GrammarIO(const string &grammarInputFile);

    // Returns all the punctuations in the grammar
    vector<char> get_punctuation();
    // Returns all the keywords in the grammar
    vector<string> get_keywords();
    // Returns regular expressions' map where <regular_expression_name, chars>
    unordered_map<string, vector<char>> get_regular_expressions();
    // Returns regular definitions' map where <pattern_name, pattern_tokens_list>
    unordered_map<string, vector<string>> get_regular_definitions();
    // Cleans a given token and return a new token without the / and detects the epsilon
    static string clean_token(const string &token);
};

#endif //JAVA_COMPILER_GRAMMARIO_H
