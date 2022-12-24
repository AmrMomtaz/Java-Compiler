#include "GrammarParser.h"

GrammarParser::GrammarParser(const string &inputFileName) : input_file_name(inputFileName) {
    
}

unordered_map<string, vector<string>> &GrammarParser::getProductions() {
    return productions;
}
