#include "GrammarIO.h"

using namespace std;

GrammarIO::GrammarIO(const string &grammarInputFile) : grammar_input_file(grammarInputFile) {
    initialize_priority_map();
}

vector<char> GrammarIO::get_punctuation() {
    vector<char> punctuations;
    ifstream infile(grammar_input_file);
    string line;
    while (getline(infile, line)) {
        int index = 0;
        while (line[index] == ' ')
            index++;
        if (line[index] == '[') {
            index++;
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
    return punctuations;
}

vector<string> GrammarIO::get_keywords() {
    vector<string> keywords;
    ifstream infile(grammar_input_file);
    string line;
    while (getline(infile, line)) {
        int index = 0;
        while (line[index] == ' ')
            index++;
        if (line[index] == '{') {
            index++;
            while (index < line.size() && line[index] != '}') {
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
    return keywords;
}

unordered_map<string, vector<char>> GrammarIO::get_regular_expressions() {
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
    return parse_regular_expression(regular_expressions);
}

unordered_map<string, vector<string>> GrammarIO::get_regular_definitions() {
    unordered_map<string,vector<string>> regular_definitions_map;
    ifstream infile(grammar_input_file);
    vector<string> regular_definitions;
    string line;
    while (getline(infile, line)) {
        string first_word;
        istringstream iss(line);
        iss >> first_word;
        if (is_regular_definition(first_word))
            regular_definitions.push_back(line);
    }
    infile.close();
    return parse_regular_definition(regular_definitions);
}

//
// Private methods
//

/**
 * Checks whether the line is a regular expression or not.
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
unordered_map<string, vector<char>> GrammarIO::parse_regular_expression
    (vector<string> &regular_expressions) {

    unordered_map<string, vector<pair<char,char>>> regular_expressions_pairs_map;
    for (auto &regular_expression : regular_expressions) {
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
        regular_expressions_pairs_map[regular_expression_name] = vector<pair<char, char>>();
        // Getting expression characters
        for (; index < n ; index++) {
            if (regular_expression[index] != ' ' && regular_expression[index] != '|') {
                char ch1 = regular_expression[index++];
                while (regular_expression[index] == ' ' || regular_expression[index] == '-')
                    index++;
                char ch2 = regular_expression[index++];
                regular_expressions_pairs_map[regular_expression_name].push_back({ch1, ch2});
            }
        }
    }
    unordered_map<string, vector<char>> regular_expressions_map;
    for (auto& map_entry : regular_expressions_pairs_map) {
        string regular_expression_name = map_entry.first;
        vector<char> characters;
        for (auto& list_entry : map_entry.second)
            for (char ch = list_entry.first ; ch <= list_entry.second ; ch ++)
                characters.push_back(ch);
        regular_expressions_map[regular_expression_name] = characters;
    }
    regular_expressions_pairs_map.clear();
    return regular_expressions_map;
}

/**
 * Checks whether the line is a regular definition or not.
 */
bool GrammarIO::is_regular_definition(const string &first_word) {
    if (first_word[first_word.size()-1] == ':')
        return true;
    else
        return false;
}

/**
 * Parses a given regular definition and adds it to the map.
 */
unordered_map<string, vector<string>> GrammarIO::parse_regular_definition
    (vector<string> &regular_definitions) {

    unordered_map<string, vector<string>> regular_definitions_map;
    for (auto& regular_definition : regular_definitions) {
        int index = 0, n = regular_definition.size();
        while (regular_definition[index] == ' ')
            index++;
        string regular_definition_name;
        while (regular_definition[index] != ':')
            regular_definition_name += regular_definition[index++];
        index++;
        vector<string> tokens;
        while (index < n) {
            while (index < n && regular_definition[index] == ' ')
                index++;
            string current;
            bool check = false;
            while (index < n) {
                char ch = regular_definition[index++];
                if (ch == '\\') {
                    check = ! check;
                    current += ch;
                    continue;
                }
                else if (ch == '|' || ch == '*' || ch == '+' || ch == '(' || ch == ')') {
                    if (check)
                        current += ch;
                    else {
                        if (!current.empty()) {
                            tokens.push_back(current);
                            current = "";
                        }
                        tokens.push_back(string(1, ch));
                    }
                }
                else if (ch == ' ') {
                    if (!current.empty()) {
                        tokens.push_back(current);
                        current = "";
                    }
                    while(index < n && regular_definition[index] == ' ')
                        index++;
                }
                else
                    current += ch;
                check = false;
            }
            if (!current.empty())
                tokens.push_back(current);
            regular_definitions_map[regular_definition_name] = tokens;
        }
    }
    return regular_definitions_map;
}

string GrammarIO::clean_token(const string& token) {
    string new_string;
    bool check = false;
    for (char ch : token) {
        if (ch == '\\') {
            if (! check) {
                check = true;
                continue;
            }
            else
                new_string += ch;
        }
        else if (check && ch == 'L')
            new_string += string(1,0);
        else
            new_string += ch;
        check = false;
    }
    return new_string;
}

/**
 * Initialized the priority map.
 */
void GrammarIO::initialize_priority_map() {
    const vector<char>& punctuations = get_punctuation();
    const vector<string>& keywords = get_keywords();
    for (char ch : punctuations)
        priority_map[string(1,ch)] = 0;
    for (const string& keyword : keywords)
        priority_map[keyword] = 0;

    // Getting regular definitions names in-order
    vector<string> regular_definitions_names;
    ifstream infile(grammar_input_file);
    string line;
    while (getline(infile, line)) {
        string first_word;
        istringstream iss(line);
        iss >> first_word;
        if (is_regular_definition(first_word))
            regular_definitions_names.push_back
                (string(first_word.begin(), first_word.end()-1));
    }
    infile.close();

    int new_priority = 1;
    for (const auto& regular_definition : regular_definitions_names)
        priority_map[regular_definition] = new_priority++;
}

string GrammarIO::get_highest_priority(vector<string> &accepting_states) {
    int highest_priority = INT32_MAX;
    string result;
    for (string& accepting_state : accepting_states) {
        int current_priority = priority_map.at(accepting_state);
        if (current_priority == 0)
            return accepting_state;
        else if (current_priority < highest_priority) {
            highest_priority = current_priority;
            result = accepting_state;
        }
    }
    return result;
}