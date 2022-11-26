#include <string>

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
};

#endif //JAVA_COMPILER_GRAMMARIO_H
