#include "FF_Generator.h"

FF_Generator::FF_Generator(unordered_map<string, vector<vector<string>>> &grammar,
                           string& start_s) : ll1(grammar), ss(start_s) {

    for (auto & kv : ll1)
        indices[kv.first] = {0, 0};
    while (done.size() != ll1.size()) {
        for(auto & kv : ll1) {
            if (done.find(kv.first) == done.end())
                computeFirst(kv.first, kv.second);
        }
    }

    done.clear();
    indices.clear();

    Follow[ss].insert("$");
    computeFollow(ss);
    for(auto & kv : ll1) {
        if (Follow.find(kv.first) == Follow.end())
            computeFollow(kv.first);
    }

//
//    while (done.size() != ll1.size()) {
//        for(auto & kv : ll1) {
//            if (done.find(kv.first) == done.end())
//                computeFollow(kv.first);
//        }
//    }

}

void FF_Generator::computeFirst(const string& s, const vector<vector<string>>& prods) {
    pair<int, int> pair = indices[s];
    int i = pair.first, j = pair.second, n = int(prods.size()), m = int(prods[0].size());
    bool has_Epsilon;
    while (i < n) {
        while (j < m) {
            if (prods[i][j] == "Epsilon" || is_terminal(prods[i][j])) {
                First[s].insert(prods[i][j]);
                // ....Edit....
                associated_prod[s].emplace_back(prods[i][j], prods[i]);
                // ....End....
                has_Epsilon = prods[i][j] == "Epsilon";
                j = 0;
                break;
            }
            if (prods[i][j] == s) {
                j = 0;
                break;
            }
            if (done.find(prods[i][j]) == done.end()) {
                indices[s] = {i, j};
                return;
            }
            has_Epsilon = union_(First[s], First[prods[i][j]]);
            // ....Edit....
            for (auto & f : First[prods[i][j]])
                if (f == "Epsilon" && j < m - 1)
                    continue;
                else
                    associated_prod[s].emplace_back(f, prods[i]);
            // ....End....
            if (!has_Epsilon) {
                j = 0;
                break;
            }
            j++;
        }
        if (!has_Epsilon)
            First[s].erase("Epsilon");
        i++;
    }
    done.insert(s);
}

//void FF_Generator::computeFollow(const string& s) {
//    if (deps.find(s) != deps.end()) {
//        string k = deps[s];
//        if (done.find(k) != done.end()) {
//            union_follow(Follow[s], Follow[k]);
//            done.insert(s);
//        }
//        return;
//    }
//
//    for(auto & kv : ll1) {
//        for (auto & prod : kv.second) {
//            int i = 0, p_size = int(prod.size());
//            while (i < p_size) {
//                if (prod[i] == s) {
//                    if (kv.first == s) {
//
//                    }
//                    if (i == p_size - 1) {
//                        if (done.find(kv.first) == done.end()) {
//                            deps[s] = kv.first;
//                            return;
//                        }
//                        union_follow(Follow[s], Follow[kv.first]);
//                    }
//                    else {
//                        if (is_leftmost(s, prod, (i + 1), p_size)) {
//                            if (done.find(kv.first) == done.end()) {
//                                deps[s] = kv.first;
//                                return;
//                            }
//                            union_follow(Follow[s], Follow[kv.first]);
//                        }
//                    }
//                }
//                i++;
//            }
//        }
//    }
//}

//void FF_Generator::computeFirst(const string& s, const vector<vector<string>>& prods) {
//    if (visited.find(s) == visited.end())
//        visited.insert(s);
//    for (auto & p : prods) {
//        if (p[0] == "Epsilon" || is_terminal(p[0])) {
//            First[s].insert(p[0]);
//            continue;
//        }
//        else {
//            if(First.find(p[0]) == First.end())
//                computeFirst(p[0], ll1[p[0]]);
//            bool has_Epsilon = union_first(First[s], First[p[0]]);
//            if (!has_Epsilon)
//                return;
//            int p_size = int(p.size()), i = 1;
//            while (has_Epsilon && i < p_size) {
//                if(First.find(p[i]) == First.end())
//                    computeFirst(p[i], ll1[p[i]]);
//                has_Epsilon = union_first(First[s], First[p[i]]);
//                i++;
//            }
//            if (i < p_size)
//                First[s].erase("Epsilon");
//        }
//    }
//}

bool FF_Generator::union_(set<string>& set_s, const set<string>& set_p) {
    set_s.insert(set_p.begin(), set_p.end());
    return set_p.find("Epsilon") != set_p.end();
}

void FF_Generator::computeFollow(const string& s) {
    for(auto & kv : ll1) {
        for (auto & p : kv.second) {
            int i = 0, p_size = int(p.size());
            while (i < p_size) {
                if (p[i] == s) {
                    if (s == kv.first)
                        break;
                    if (i == p_size - 1) {
                        if (Follow.find(kv.first) == Follow.end())
                            computeFollow(kv.first);
                        union_(Follow[s], Follow[kv.first]);
                    }
                    else {
                        if (is_leftmost(s, p, (i + 1), p_size)) {
                            if (Follow.find(kv.first) == Follow.end())
                                computeFollow(kv.first);
                            union_(Follow[s], Follow[kv.first]);
                        }
                    }
                }
                i++;
            }
        }
    }
}

//bool FF_Generator::union_follow(set<string>& follow_s, const set<string>& set_p) {
//    follow_s.insert(set_p.begin(), set_p.end());
//    return set_p.find("Epsilon") != set_p.end();
//}

unordered_map<string, pair
    <vector<pair<string, vector<string>>>,
    set<string>>> FF_Generator::getProductions() {

    unordered_map<string, pair
        <vector<pair<string, vector<string>>>,
        set<string>>> output;

    for (auto & kv : ll1)
        output[kv.first] = {associated_prod[kv.first], Follow[kv.first]};
    return output;
}

bool FF_Generator::is_terminal(const string& s) {
    return ll1.find(s) == ll1.end() && s != "Epsilon";
}

const unordered_map<string, set<string>> &FF_Generator::getFirst() const {
    return First;
}

bool FF_Generator::is_leftmost(const string& s, vector<string>& prod, int idx, int p_size) {
    bool has_Epsilon;
    while (idx < p_size) {
        if (is_terminal(prod[idx])) {
            Follow[s].insert(prod[idx]);
            return false;
        }
        else {
            has_Epsilon = union_(Follow[s], First[prod[idx]]);
            if (!has_Epsilon)
                return false;
        }
        Follow[s].erase("Epsilon");
        idx++;
    }
    return true;
}

const unordered_map<string, set<string>> &FF_Generator::getFollow() const {
    return Follow;
}

