#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "NFA.h"

using namespace std;

NFA::NFA(const string &grammar_input_file) : grammarIo(grammar_input_file) {}
