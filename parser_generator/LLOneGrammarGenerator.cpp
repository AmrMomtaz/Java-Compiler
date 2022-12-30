#include "LLOneGrammarGenerator.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

LLOneGrammarGenerator::LLOneGrammarGenerator
    (unordered_map<string, vector<vector<string>>> file_productions) : productions(file_productions),
    counter(0) {

    for (auto vec : productions) {
        for (int i=0; i<vec.second.size(); i++) {
            if (vec.second[i].size() == 1 && vec.second[i][0] == "Epsilon")
                productions[vec.first][i] = vector<string>();
        }
    }
    // ELIMINATE LEFT RECURSION
    eliminate_indirect_left_recursion();

    // ELIMINATE LEFT FACTORING
    // convert vector to queue naively
    queue<string> keys_queue;
    for (string key : get_map_keys()) keys_queue.push(key);

    // loop over all productions
    while (! keys_queue.empty()) {
        string LHS = keys_queue.front();
        keys_queue.pop();
        unordered_map<string, vector<vector<string>>> place_holder;
        while (canBeFactored(LHS))
            place_holder = eliminate_left_factor(LHS);

        // add the LHS to be checked again for left factoring
        if (! place_holder.empty()) {
            for (auto it : place_holder) keys_queue.push(it.first);
        }
        place_holder.clear();
    }

    for (auto vec : productions) {
        for (int i=0; i<vec.second.size(); i++) {
            if (vec.second[i].empty())
                productions[vec.first][i] = vector<string>{"Epsilon"};
        }
    }
}

void LLOneGrammarGenerator::eliminate_indirect_left_recursion() {
    int prod_size = 0;
    bool isChanged;
    do {
        isChanged = false;
        vector<string> keys = get_map_keys();
        if (keys.size() != prod_size) {
            prod_size = keys.size();
            isChanged = true;
        }
        for (int i=0; i<keys.size(); i++) { // i : 1 -> n
            for(int j=0; j<i; j++) { // j : 1 -> i-1
                // replace
                substitute(keys[i], keys[j]);
            }
            while (canBeLeftRecursed(keys[i]))
                eliminate_left_recursion(keys[i]);
        }
    }
    while (isChanged);
}

void LLOneGrammarGenerator::eliminate_left_recursion(string LHS) {
    vector<vector<string>> RHS = productions.at(LHS);

    vector<string> alpha;
    vector<vector<string>> beta;
    string new_LHS = LHS + "_recur_" + to_string(counter++);

    for (int i = 0; i < RHS.size(); i++) {
        // LHS = A and RHS = A b
        // so left recursion exists
        if (alpha.empty() && RHS[i][0] == LHS) {
            // fill alpha where [A -> A alpha | beta]
            for (int j = 1; j < RHS[i].size(); j++)
                alpha.push_back(RHS[i][j]);

            alpha.push_back(new_LHS);
        }
        else {
            RHS[i].push_back(new_LHS);
            beta.push_back(RHS[i]);
        }
    }

    productions[LHS] = beta;
    if (beta.empty())
        productions[LHS].push_back(vector<string>{new_LHS});

    productions[new_LHS].push_back(alpha);
    productions[new_LHS].push_back(vector<string>{});
    remove_extra_epsilons(LHS);
    remove_extra_epsilons(new_LHS);
}

unordered_map<string, vector<vector<string>>> LLOneGrammarGenerator::eliminate_left_factor(string LHS) {
    vector<vector<string>> RHS = productions.at(LHS);
    vector<vector<string>> rest_of_vectors;
    vector<vector<string>> remain_same;
    vector<int> indices_to_be_factored;
    string new_LHS = LHS + "_factor_" + to_string(counter++);
    string factor_string;

    // repeat for all vectors
    for (int i=0; i<RHS.size(); i++) {
        if (RHS[i].empty()) continue;

        indices_to_be_factored = {};
        indices_to_be_factored.push_back(i);

        bool isFactored = false;

        rest_of_vectors.push_back(vector<string>(RHS[i].begin()+1, RHS[i].end()));

        // check the other vectors if they have similars
        for (int j=i+1; j<RHS.size(); j++) {
            if (RHS[i][0] == RHS[j][0]) {
                factor_string = RHS[i][0];
                isFactored = true;
                // add the rest of the vectors to the rest_of_vectors data structure
                rest_of_vectors.push_back(vector<string>(RHS[j].begin()+1, RHS[j].end()));
                // insert indices to be factored
                indices_to_be_factored.push_back(j);
            }
        }
        if (isFactored) break;
    }

    // get the remaining vectors to NOT be touched
    for (int i=0; i<RHS.size(); i++) {
        if (find(indices_to_be_factored.begin(), indices_to_be_factored.end(), i) != indices_to_be_factored.end())
            continue;

        remain_same.push_back(RHS[i]);
    }
    // A -> <<a, b, c> | <a, d> | <e, f>>
    // A_factor_0 -> <<b, c> | <d>>
    productions[new_LHS] = rest_of_vectors;
    // A -> <<e, f>>
    productions[LHS] = remain_same;
    // A-> <<e, f> | <a, A_factor_0>>
    productions[LHS].push_back(vector<string>{factor_string, new_LHS});
    remove_extra_epsilons(LHS);
    remove_extra_epsilons(new_LHS);
    return productions;
}

bool LLOneGrammarGenerator::canBeFactored(string LHS) {
    vector<vector<string>> RHS = productions.at(LHS);
    for (int i=0; i<RHS.size(); i++) {
        for (int j=i+1; j<RHS.size(); j++)
            if (! RHS[i].empty() && ! RHS[j].empty() && (RHS[i][0] == RHS[j][0]))
                return true;
    }
    return false;
}

bool LLOneGrammarGenerator::canBeLeftRecursed(string LHS) {
    vector<vector<string>> RHS = productions.at(LHS);
    for (vector<string> vec : RHS)
        if (! vec.empty() && vec[0] == LHS) return true;

    return false;
}

vector<string> LLOneGrammarGenerator::get_map_keys() {
    vector<string> keys;
    for (auto it : productions) keys.push_back(it.first);
    return keys;
}

// puts productions of LHS2 in LHS1
void LLOneGrammarGenerator::substitute(string LHS1, string LHS2) {
    vector<vector<string>> RHS1 = productions.at(LHS1);
    vector<vector<string>> RHS2 = productions.at(LHS2);
    vector<vector<string>> new_RHS;

    for (auto vec1 : RHS1) {
        // if substitution needed
        if (! vec1.empty() && vec1[0] == LHS2) {
            for (auto vec2 : RHS2) {
                vector<string> tmp;
                tmp.insert(tmp.end(), vec2.begin(), vec2.end());
                tmp.insert(tmp.end(), vec1.begin()+1, vec1.end());
                new_RHS.push_back(tmp);
            }
        }
        // no substitution needed
        else {
            new_RHS.push_back(vec1);
        }
        productions[LHS1] = new_RHS;
    }
}

unordered_map<string, vector<vector<string>>> LLOneGrammarGenerator::get_ll_one_grammar() {
    return productions;
}

void LLOneGrammarGenerator::remove_extra_epsilons(string LHS) {
    vector<vector<string>> RHS = productions.at(LHS);
    vector<vector<string>> new_RHS;
    bool hit_eps = false;
    for (auto vec : RHS) {
        if (hit_eps && vec.empty())
            continue;
        if(! hit_eps && vec.empty())
            hit_eps = true;

        new_RHS.push_back(vec);
    }
    productions[LHS] = new_RHS;
}

void LLOneGrammarGenerator::print_productions() {
    for (auto it1 : productions) {
        cout << it1.first << " : ";
        for (int i=0; i<it1.second.size(); i++) {
            vector<string> vec = it1.second[i];
            for (string s : vec){
                cout << s << " ";
            }
            if (i != it1.second.size()-1)
                cout << "| ";
        }
        cout << endl;
    }
}





