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
    static bool is_regular_expression(const string& first_word);
    static void parse_regular_expression
        (string &regular_expression, unordered_map<string, vector<pair<char,char>>>& regular_expressions_map);
public:
    explicit GrammarIO(const string &grammarInputFile);

    // Return all the regular expressions in the grammar
    void get_regular_expressions();
    // Return all the punctuations in the grammar
    vector<char> get_punctuation();
    // Returns all the keywords in the grammar
    vector<string> get_keywords();
};

#endif //JAVA_COMPILER_GRAMMARIO_H
