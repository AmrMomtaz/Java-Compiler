#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>

#include "GrammarIO.h"

using namespace std;

GrammarIO::GrammarIO(const string &grammarInputFile) : grammar_input_file(grammarInputFile) {
    ifstream infile(grammar_input_file);
    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        cout << line << endl;
    }
    infile.close();
}