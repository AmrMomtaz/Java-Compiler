#include <vector>
#include <string>
#include <unordered_map>

#ifndef JAVA_COMPILER_LLONEGRAMMARGENERATOR_H
#define JAVA_COMPILER_LLONEGRAMMARGENERATOR_H
using namespace std;

class LLOneGrammarGenerator {
public:
    int counter;

    explicit LLOneGrammarGenerator(unordered_map<string, vector<vector<string>>> file_productions);
    unordered_map<string, vector<vector<string>>> get_ll_one_grammar();
    void print_productions();

private:
    unordered_map<string, vector<vector<string>>> productions;
    bool canBeFactored(string LHS);
    bool canBeLeftRecursed(string LHS);
    void substitute(string LHS_to_be_changed, string LHS_to_replace);
    void eliminate_left_recursion(string LHS);
    unordered_map<string, vector<vector<string>>> eliminate_left_factor(string LHS);
    void eliminate_indirect_left_recursion();
    void remove_extra_epsilons(string LHS);
    vector<string> get_map_keys();
};
#endif //JAVA_COMPILER_LLONEGRAMMARGENERATOR_H
