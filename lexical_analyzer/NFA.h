#include <string>

#ifndef JAVA_COMPILER_NFA_H
#define JAVA_COMPILER_NFA_H

using namespace std;
class NFA {
private:
    static void initialize_rules(const string& grammar_input_file);
public:
    explicit NFA(const string &grammar_input_file);
};


#endif //JAVA_COMPILER_NFA_H
