#include "NFA.h"
#include "LexicalAnalyzer.h"
#include "../utils/TransitionTable.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;
string tokenize(string s, const string removed_chars, const string c) {
    for (int i = 0; i < removed_chars.length(); i++) {
        s.erase(remove(s.begin(), s.end(), removed_chars[i]), s.end());
    }
    if (!s.size()) {
        return "";
    }
    stringstream ss;
    ss << s[0];
    for (int i = 1; i < s.size()+1; i++) {
        ss << c << s[i];
    }
    string myString = ss.str();
    string st = myString.substr(0, myString.size()-1);
    return st;
}
vector<string> adv_tokenizer(string s, char del){
    vector<string> strings;
    stringstream ss(s);
    string word;
    while (!ss.eof()) {
        getline(ss, word, del);
        strings.push_back(word);
    }
    return strings;
}

vector<string> split_string_by_white_spaces(string s){
    char white_spaces[3] = {' ','\n', '\t'};
    vector<string> words = adv_tokenizer(s, white_spaces[0]);
    for (int i=1; i<3; i++){
        vector<string> temp_1;
        for (auto j = words.begin(); j != words.end(); ++j){
            vector<string> temp_2 = adv_tokenizer(*j, white_spaces[i]);
            for (auto k = temp_2.begin(); k != temp_2.end(); ++k)
                temp_1.push_back(*k);
        }
        words=temp_1;
    }
    return words;
}

int lexicalAnalyzerTestRun() {
    //    TransitionTable TT(true); //will be created down

    string letter="AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
    string digit = "0123456789";
    string edges[14]= {"0/i1/t2/e3/<4/=5/>6/"+tokenize(letter,"ite","7/")+tokenize(digit,"","8/"),
                       "1/f9/"+tokenize(letter,"f","7/"),
                       "2/h10/"+tokenize(letter,"h","7/"),
                       "3/l11/"+tokenize(letter,"l","7/"),
                       "4/>5/=5",
                       "6/=5",
                       "8/"+tokenize(digit,"","8/"),
                       "9/"+tokenize(digit,"","7/"),
                       "10/e12/"+tokenize(letter,"e","7/"),
                       "11/s13/"+tokenize(letter,"s","7/"),
                       "12/n14/"+tokenize(letter,"n","7/"),
                       "13/e15/"+tokenize(letter,"e","15/"),
                       "14/"+tokenize(letter,"","7/"),
                       "15/"+tokenize(letter,"","7/")};
    ///Creating The Minimal DFA
    unordered_map<int, unordered_map<char, vector<int>>> table;
    for (int i = 0; i < 14; i++) {
//        cout<<edges[i] << "\n";
        int current_state = edges[i][0]- '0';
        bool first_time= true;
        unordered_map<char, vector<int>> transitions;
//        vector<string> remaining_string = adv_tokenizer(edges[i].substr(1, edges[i].size()), '/');
        vector<string> remaining_string = adv_tokenizer(edges[i], '/');
        for (auto x = remaining_string.begin(); x != remaining_string.end(); ++x) {
            string temp = *x;
            if(!first_time) {
//            cout << temp << "\n";
                if (!x->empty()) {
                    vector<int> coming_states;
//                cout << temp << "\n";
//                cout << temp.substr(1, temp.size() - 1) << "\n";
                    coming_states.push_back(stoi(temp.substr(1, edges[i].size() - 1)));
                    transitions[temp[0]] = coming_states;
                }
            } else{
                current_state = stoi(temp);
                first_time = false;
            }
        }
        table[current_state] = transitions;
    }
    ///Define the accepting states
    unordered_map<int, string> accepting_states;
    accepting_states[1] = "P5";
    accepting_states[2] = "P5";
    accepting_states[3] = "P5";
    accepting_states[4] = "P4";
    accepting_states[5] = "P4";
    accepting_states[6] = "P4";
    accepting_states[7] = "P5";
    accepting_states[8] = "P6";
    accepting_states[9] = "P1";
    accepting_states[10] = "P5";
    accepting_states[11] = "P5";
    accepting_states[12] = "P5";
    accepting_states[13] = "P5";
    accepting_states[14] = "P2";
    accepting_states[15] = "P3";


    TransitionTable TT(true,table,accepting_states,0);
    for (auto i : TT.getTable()) {
        pair<int, unordered_map<char, vector<int>>> temp = i;
        int num = temp.first;
        unordered_map<char, vector<int>> trans = temp.second;
        for (auto j : trans) {
            cout << num << "---(" << j.first << ")--->" << j.second[0] << endl;
        }
    }
    cout << "num of states that has coming state = " << TT.getTable().size() << endl;
    ///Now The Minimal DFA is Ready to be used
    ///Define the accepting states names
    unordered_map<string, string> accepting_states_names;
    accepting_states_names["P1"]="if";
    accepting_states_names["P2"]="then";
    accepting_states_names["P3"]="else";
    accepting_states_names["P4"]="relop";
    accepting_states_names["P5"]="id";
    accepting_states_names["P6"]="num";
    accepting_states_names["Not Defined!"]="Not Defined!";

    ///get the lexical analyzer
    LexicalAnalyzer LA(TT);

    string input_text="";
    ifstream myfile; myfile.open("C:\\Users\\momen\\OneDrive\\Documents\\GitHub\\Java-Compiler\\test_program.txt");
    if ( myfile.is_open() ) {
        char mychar;
        while ( myfile ) {
            mychar = myfile.get();
            input_text+=mychar;
        }
    }
    cout << input_text << "\n";

    //split the input text on the white space
    vector<string> words = split_string_by_white_spaces(input_text);
    for (auto word = words.begin(); word != words.end(); ++word) {
//        cout << *word << "\n";
        vector<pair<string, string>> tokens = LA.getAllTokensInText(*word);
        for (auto i = tokens.begin(); i != tokens.end(); ++i) {
            pair<string, string> token = *i;
            cout << token.first << " : " << accepting_states_names[token.second] << "\n";
        }
    }
    return 0;
}