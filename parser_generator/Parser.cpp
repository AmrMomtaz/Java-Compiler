#include "Parser.h"
Parser::Parser(LexicalAnalyzer &la, unordered_map<string,pair<vector<pair<string,vector<string>>>,vector<string>>> &LL1 ) : LA(la) {
    make_parsing_table(LL1);
    stack.push("$");
    std::cout << "[INFO] New parser created" << "\n";
}
void Parser::make_parsing_table(unordered_map<string,pair<vector<pair<string,vector<string>>>,vector<string>>> &LL1){
    for (auto x : LL1){
//        cout << x.first << " " << x.second.first.size() << endl;
        unordered_map<string,vector<string>> temp;
        for(auto& first: x.second.first){
            if(first.first!="epsilon") {
                temp[first.first] = first.second;
//                cout << first.first << ' ';
                for(auto& follow: x.second.second){
                    if (temp.count(follow)==0) {
                        vector<string> v;
                        v.push_back("sync");
                        temp[follow] = v;
//                    temp[first.first].push_back("sync");
//                    std::cout << follow << ' ';
                    }
                }
            }
            else{
//                cout<<"here"<<endl;
                for(auto& follow: x.second.second){
                    vector<string> v;
                    v.push_back("epsilon");
                    temp[follow] = v;
//                    std::cout << follow << ' ';
                }
            }
        }
//        cout << "\n";
        parsing_table[x.first]=temp;
    }
}
void Parser::printParsingTable(){
    for (auto x : parsing_table){
        cout<< x.first<<": "<< endl;
        for (auto y : x.second){
            cout << y.first<<": ";
            for (auto z : y.second){
                cout<<z<<" ";
            }
            cout << endl;
        }
        cout <<"____________________________"<<endl;
    }
}
void Parser::parseInput(){
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
    vector<string> words = LA.split_string_by_white_spaces(input_text);

    cout << "-------- Tokens --------" << "\n";
    ofstream fo;
    fo.open("test_program_output.txt");
    if (fo.is_open()) {
        for (auto word = words.begin(); word != words.end(); ++word) {
            vector<pair<string, string>> tokens = LA.getAllTokensInText(*word);
            for (auto i = tokens.begin(); i != tokens.end(); ++i) {
                pair<string, string> token = *i;
                fo << token.first << " : " << token.second << "\n";
                //the parser work here
                cout << token.first << " : " << token.second << "\n";
            }
        }
    }
}