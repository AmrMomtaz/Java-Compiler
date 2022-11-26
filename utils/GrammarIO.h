#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>

#ifndef JAVA_COMPILER_GRAMMARIO_H
#define JAVA_COMPILER_GRAMMARIO_H

using namespace std;
/**
 * Provide utils to read grammar from input file.
 */
class GrammarIO {
private:
    string grammar_input_file;
public:
    explicit GrammarIO(const string &grammarInputFile);
    void get_regular_expressions();
};

#endif //JAVA_COMPILER_GRAMMARIO_H
