#include <unordered_map>
#include <vector>
#include <set>
#include <string>

#ifndef JAVA_COMPILER_FF_GENERATOR_H
#define JAVA_COMPILER_FF_GENERATOR_H

using namespace std;

class FF_Generator {

private:
    unordered_map<string, vector<vector<string>>> ll1;
    unordered_map<string, set<string>> First;
    unordered_map<string, set<string>> Follow;
    unordered_map<string, vector<pair<string, vector<string>>>> associated_prod;
    unordered_map<string, pair<int, int>> indices;
    set<string> done;
    string ss;

    bool is_terminal(const string& s);
    bool union_(set<string>& set_s, const set<string>& set_p);
    bool is_leftmost(const string& s, vector<string>& p, int idx, int p_size);
    void computeFirst(const string& s, const vector<vector<string>>& prods);
    void computeFollow(const string& s);

public:
    explicit FF_Generator(unordered_map<string, vector<vector<string>>> &grammar, string& ss);
    unordered_map<string, pair
        <vector<pair<string, vector<string>>>,
        set<string>>> getProductions();
    const unordered_map<string, set<string>> &getFirst() const;
    const unordered_map<string, set<string>> &getFollow() const;
};

#endif //JAVA_COMPILER_FF_GENERATOR_H
