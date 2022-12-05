#include "LexicalAnalyzer.h"

LexicalAnalyzer::LexicalAnalyzer(TransitionTable& tt) : TT(tt) {std::cout << "[INFO] New lexical analyzer created" << "\n";}

// Setter
void LexicalAnalyzer::setText(string s){text = s; current_char_idx = 0;}
// Getter
const string &LexicalAnalyzer::getText() const { return text;}

// Setter
void LexicalAnalyzer::setCurrentIndex(int i){current_char_idx = i;}
// Getter
const int &LexicalAnalyzer::getCurrentIndex() const { return current_char_idx;}
const map<string , string> &LexicalAnalyzer::getSymbolTable() const {return symbol_table;}

//return the next token and his type
pair<string ,string> LexicalAnalyzer::getNextToken(){
    if (!TT.isDeterministic()){
        cout << "Error The acceptor is not deterministic finite state acceptor !" << "\n";
        return make_pair("", "");
    }

    int starting_idx = current_char_idx;

    unordered_map<int, unordered_map<char, vector<int>>>& table = TT.getTable();
    unordered_map<int, string>& accepting_states = TT.getAcceptingStates();
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
        pair<string ,string> symbol = make_pair(text.substr(starting_idx, text.size()-starting_idx), accepting_states[current_state]);
        if (symbol.second=="id"){
            symbol_table[symbol.first] = symbol.second;
        }
        return symbol;
    }
    //no coming state so go back tell find accepting state
    else{
        int count = 0;
        for (auto ir = reached_states.rbegin(); ir != reached_states.rend(); ++ir) {
            int curr_state = *ir;
            if (!(accepting_states.find(curr_state) == accepting_states.end())){
                pair<string ,string> symbol = make_pair(text.substr(starting_idx, reached_states.size()-1-count), accepting_states[curr_state]);
                if (symbol.second=="id"){
                    symbol_table[symbol.first] = symbol.second;
                }
                return symbol;
            }
            count +=1;
        }
        return make_pair(text.substr(starting_idx, text.size()-starting_idx), "Not Defined!");
    }
}

//return the next token and his type
vector<pair<string ,string>> LexicalAnalyzer::getAllTokensInText(string text) {
    setText(text);
    return getAllTokens();
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

vector<string> LexicalAnalyzer::adv_tokenizer(string s, char del){
    vector<string> strings;
    stringstream ss(s);
    string word;
    while (!ss.eof()) {
        getline(ss, word, del);
        strings.push_back(word);
    }
    return strings;
}
vector<string> LexicalAnalyzer::split_string_by_white_spaces(string s){
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

void LexicalAnalyzer::tokensInTextInFile(string input_path, string output_path){
    string input_text;
    ifstream fh;
    fh.open("test_program.txt");
    if (fh.is_open()) {
        char ch;
        while (fh) {
            ch = fh.get();
            input_text+=ch;
        }
    }
    cout << input_text << "\n";
    fh.close();

    // split the input text on the white space
    vector<string> words = split_string_by_white_spaces(input_text);

    cout << "-------- Tokens --------" << "\n";
    ofstream fo;
    fo.open("test_program_output.txt");
    if (fo.is_open()) {
        for (auto word = words.begin(); word != words.end(); ++word) {
            vector<pair<string, string>> tokens = getAllTokensInText(*word);
            for (auto i = tokens.begin(); i != tokens.end(); ++i) {
                pair<string, string> token = *i;
                fo << token.first << " : " << token.second << "\n";
                cout << token.first << " : " << token.second << "\n";
            }
        }
    }
}

