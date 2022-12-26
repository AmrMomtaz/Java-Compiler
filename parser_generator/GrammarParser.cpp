#include "GrammarParser.h"

GrammarParser::GrammarParser(const string &inputFileName) : input_file_name(inputFileName) {
    parse_grammar();
}

unordered_map<string, vector<vector<string>>> &GrammarParser::getProductions() {
    return productions;
}

/**
 * This function is used to get the production name and the rest of the productions.
 */
void GrammarParser::parse_grammar() {
    ifstream infile(input_file_name);
    vector<string> regular_expressions;
    string line;
    getline(infile, line);
    while (!line.empty()) {
        for (int i = 0 ; i < line.size() ; i++) {
            string production_name;
            while (line[i] == ' ' || line[i] == '#')
                i++;
            while (line[i] != ' ' && line[i] != '=')
                production_name += line[i++];
            while (line[i] == ' ' || line[i] == '=')
                i++;
            vector<string> production_lines;
            production_lines.emplace_back(line.substr(i, line.size()-i));
            line = "";
            while (getline(infile, line)) {
                int new_i = 0;
                while (line[new_i] == ' ')
                    new_i++;
                if (line[new_i] == '#')
                    break;
                else
                    production_lines.emplace_back(line);
            }
            parse_production(production_lines, production_name);
            break;
        }
    }
    infile.close();
}

/**
 * This function returns the production a vector of production tokens given the production lines.
 */
void GrammarParser::parse_production(vector<string> &production_lines, string& production_name) {
    vector<vector<string>> tokens;
    vector<string> current_tokens;
    for (string& production_line : production_lines) {
        int n = production_line.size();
        for (int i = 0 ; i < n ; i++) {
            while (i < n && production_line[i] == ' ')
                i++;
            string token;
            if (i < n && production_line[i] == '\'') {
                i++;
                while (i < n && production_line[i] != '\'') {
                    token += production_line[i++];
                }
                i++;
            }
            else {
                while (i < n && production_line[i] != ' ')
                    token += production_line[i++];
            }
            if (token == "|") {
                tokens.emplace_back(current_tokens);
                current_tokens.clear();
            }
            else {
                current_tokens.emplace_back(token);
            }
        }
    }
    if (! current_tokens.empty())
        tokens.emplace_back(current_tokens);
    productions[production_name] = tokens;
}
