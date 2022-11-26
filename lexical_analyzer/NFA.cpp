#include "NFA.h"

using namespace std;

NFA::NFA(const string &grammar_input_file) : grammarIo(grammar_input_file) {}

void NFA::run() {
    grammarIo.get_keywords();
}
