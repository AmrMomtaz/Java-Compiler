#include "LexicalAnalyzer.h"

LexicalAnalyzer::LexicalAnalyzer(TransitionTable tt) : TT(tt) {std::cout << "[INFO] New lexical analyzer created" << "\n";}

// Setter
void LexicalAnalyzer::setText(string s){text = s; current_char_idx = 0;}
// Getter
const string &LexicalAnalyzer::getText() const { return text;}

// Setter
void LexicalAnalyzer::setCurrentIndex(int i){current_char_idx = i;}
// Getter
const int &LexicalAnalyzer::getCurrentIndex() const { return current_char_idx;}

//return the next token and his type
pair<string ,string> LexicalAnalyzer::getNextToken(){
    if (!TT.isDeterministic()){
        cout << "Error The acceptor is not deterministic finite state acceptor !" << "\n";
        return make_pair("", "");
    }

    int starting_idx = current_char_idx;

    unordered_map<int, unordered_map<char, vector<int>>> table = TT.getTable();
    unordered_map<int, string> accepting_states = TT.getAcceptingStates();
    int current_state = TT.getStartingState();

    vector<int> reached_states;
    reached_states.push_back(current_state);

    while (current_char_idx<text.size()) {
        char current_char = text[current_char_idx];
        vector<int> &coming_state = table[current_state][current_char];

        if(coming_state.size() == 0) {
            if (current_char_idx==starting_idx) setCurrentIndex(current_char_idx+1);
            break;
        }

        else if (coming_state.size() != 1) {
            cout << "Error The acceptor is not deterministic finite state acceptor !" << "\n";
            return make_pair("", "");
        }

        current_state = coming_state[0];
        reached_states.push_back(current_state);
        setCurrentIndex(current_char_idx + 1);
    }
    if (current_char_idx>=text.size()){
        //check that if the current state is accepting state or not
        if (accepting_states.find(current_state) == accepting_states.end())
            return make_pair(text.substr(starting_idx, text.size()-starting_idx), "Not Defined!");
        return make_pair(text.substr(starting_idx, text.size()-starting_idx), accepting_states[current_state]);
    }
    //no coming state so go back tell find accepting state
    else{
        int count = 0;
        for (auto ir = reached_states.rbegin(); ir != reached_states.rend(); ++ir) {
            int curr_state = *ir;
            if (!(accepting_states.find(curr_state) == accepting_states.end())){
                return make_pair(text.substr(starting_idx, reached_states.size()-1-count), accepting_states[curr_state]);
            }
            count +=1;
        }
        return make_pair(text.substr(starting_idx, text.size()-starting_idx), "Not Defined!");
    }
}

//return the next token and his type
vector<pair<string ,string>> LexicalAnalyzer::getAllTokens(){
    vector<pair<string ,string>> pairs;
    while (getCurrentIndex()<getText().size()){
        pair<string ,string> p = getNextToken();
        pairs.push_back(p);
//        cout << p.first<< " " << p.second << "\n";
    }
    return pairs;
}
//return the next token and his type
vector<pair<string ,string>> LexicalAnalyzer::getAllTokensInText(string text){
    setText(text);
    return getAllTokens();
}
