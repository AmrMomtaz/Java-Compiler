#include "GrammarIO.h"

using namespace std;

GrammarIO::GrammarIO(const string &grammarInputFile) : grammar_input_file(grammarInputFile) {}

void GrammarIO::get_regular_expressions() {
    ifstream infile(grammar_input_file);
    string line;
    while (getline(infile, line)) {
        string first_word;
        istringstream iss(line);
        iss >> first_word;
        cout << first_word << endl;
    }
    infile.close();
}

//
// Helper functions
//

bool is_regular_expression(const string& first_word) {
    if (first_word[first_word.size()-1] == ':')
        return false;
    else
        return true;
}