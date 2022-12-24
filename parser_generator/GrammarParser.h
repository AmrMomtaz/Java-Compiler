#include <unordered_map>
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
    unordered_map<string, vector<string>> &getProductions();
private:
    const string input_file_name;
    // productions map
    unordered_map<string, vector<string>> productions;
};


#endif //JAVA_COMPILER_GRAMMARPARSER_H
