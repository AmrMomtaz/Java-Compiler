#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

#ifndef JAVA_COMPILER_GRAMMARPARSER_H
#define JAVA_COMPILER_GRAMMARPARSER_H

using namespace std;
class GrammarParser {
public:
    // Constructor
    explicit GrammarParser(const string &inputFileName);
    // Getter
    unordered_map<string, vector<vector<string>>> &getProductions();
private:
    const string input_file_name;
    // productions map
    unordered_map<string, vector<vector<string>>> productions;

    void parse_grammar();
    void parse_production(vector<string>& production_lines, string& production_name);
};


#endif //JAVA_COMPILER_GRAMMARPARSER_H
