#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "NFA.h"

using namespace std;

NFA::NFA(const string& grammar_input_file) { initialize_rules(grammar_input_file);}

void NFA::initialize_rules(const string& grammar_input_file) {
    ifstream infile(grammar_input_file);
    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        cout << line << endl;
    }
}