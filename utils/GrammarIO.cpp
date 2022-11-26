#include "GrammarIO.h"

using namespace std;

GrammarIO::GrammarIO(const string &grammarInputFile) : grammar_input_file(grammarInputFile) {}

void GrammarIO::get_regular_expressions() {
    unordered_map<string, vector<pair<char,char>>> regular_expressions_map;
    ifstream infile(grammar_input_file);
    vector<string> regular_expressions;
    string line;
    while (getline(infile, line)) {
        string first_word;
        istringstream iss(line);
        iss >> first_word;
        if (is_regular_expression(first_word))
            regular_expressions.push_back(line);
    }
    infile.close();
    for (auto &regular_expression : regular_expressions)
        parse_regular_expression(regular_expression, regular_expressions_map);
    for (auto& map_entry : regular_expressions_map) {
        cout << map_entry.first << " = ";
        for (auto& list_entry : map_entry.second)
            cout << list_entry.first << "," << list_entry.second << " ";
        cout << endl;
    }
}

void GrammarIO::get_punctuation() {
    vector<char> punctuations;
    ifstream infile(grammar_input_file);
    string line;
    while (getline(infile, line)) {;
        if (line[0] == '[') {
            int index = 1;
            bool check = false;
            while (line[index] != ']') {
                if (line[index] == '\\') {
                    if (! check)
                        check = true;
                    else {
                        punctuations.push_back(line[index]);
                        check = false;
                    }
                }
                else if (line[index] != ' ') {
                    punctuations.push_back(line[index]);
                    check = false;
                }
                index++;
            }
        }
    }
    infile.close();
    for (auto  &ch : punctuations)
        cout << ch;
}

void GrammarIO::get_keywords() {
    vector<string> keywords;
    ifstream infile(grammar_input_file);
    string line;
    while (getline(infile, line)) {;
        if (line[0] == '{') {
            int index = 1;
            while (index < line.size() && line[index != '}']) {
                if (line[index] != ' ') {
                    string keyword;
                    while (index < line.size()) {
                        if (line[index] == ' ' || line[index] == '}')
                            break;
                        else {
                            keyword += line[index];
                            index++;
                        }
                    }
                    keywords.push_back(keyword);
                }
                index++;
            }
        }
    }
    infile.close();
    for (auto  &keyword : keywords)
        cout << keyword << " ";
}

//
// Private methods
//

/**
 * Determines whether it is a regular expression or not.
 */
bool GrammarIO::is_regular_expression(const string& first_word) {
    if (first_word[first_word.size()-1] == ':' || first_word[0] == '[' || first_word[0] == '{')
        return false;
    else
        return true;
}

/**
 * Parses a given regular expression and adds it to the map.
 */
void GrammarIO::parse_regular_expression
    (string &regular_expression,unordered_map<string, vector<pair<char, char>>> &regular_expressions_map) {

    // getting regular expression's name
    string regular_expression_name;
    int index = 0, n = regular_expression.size();
    for (; index < n ; index++) {
        if (regular_expression[index] == ' ')
            continue;
        else if (regular_expression[index] == '=')
            break;
        else
            regular_expression_name += regular_expression[index];
    }
    index++;
    regular_expressions_map[regular_expression_name] = vector<pair<char, char>>();
    // Getting expression characters
    for (; index < n ; index++) {
        if (regular_expression[index] != ' ' && regular_expression[index] != '|') {
            char ch1 = regular_expression[index++];
            while (regular_expression[index] == ' ' || regular_expression[index] == '-')
                index++;
            char ch2 = regular_expression[index++];
            regular_expressions_map[regular_expression_name].push_back({ch1, ch2});
        }
    }
}
