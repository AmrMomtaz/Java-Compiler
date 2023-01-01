#ifndef JAVA_COMPILER_PARSER_H
#define JAVA_COMPILER_PARSER_H
#include "../lexical_analyzer/LexicalAnalyzer.h"
#include <stack>
#include <set>

class Parser {
private:
    //The transition table of the minimum DFA
    //to be used for tokenizing
    stack<string> stack;//the stack where the logic will ru on
    LexicalAnalyzer LA;
    unordered_map<string , pair<vector<pair<string , vector<string> >>,set<string >>> LL1;
    unordered_map<string, unordered_map<string,vector<string>>> parsing_table;

    void make_parsing_table(unordered_map<string,pair<vector<pair<string,vector<string>>>,set<string>>> &LL1);

    string get_stack_elements();
    vector<string> get_stack_elements_vector();
public:
    explicit Parser(LexicalAnalyzer &la, unordered_map<string,pair<vector<pair<string,vector<string>>>,set<string>>> &LL1);

    void parseInput(string input_file_path, string token_output_file,string starting_production, string left_most_derivation_output_file, string stack_events_and_errors);

    void printParsingTable();
};


#endif //JAVA_COMPILER_PARSER_H
