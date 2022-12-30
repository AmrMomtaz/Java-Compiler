#include <iterator>
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
string Parser::get_stack_elements(){
    ::stack<string> tempt;
    string strings;
    while(stack.size()!=1) {
        tempt.push(stack.top());
        strings+=stack.top()+=" ";
        stack.pop();
    }
    while(!tempt.empty()) {
        stack.push(tempt.top());
        tempt.pop();
    }
    return strings;
}
void Parser::parseInput(string input_file_path, string token_output_file, string starting_production){
    vector<string> output_left_most_derivation;

    vector<string> error_messages;

    stack.push(starting_production);
    output_left_most_derivation.push_back(get_stack_elements());

    string input_text;
    ifstream fh;
    fh.open(input_file_path);
    if (fh.is_open()) {
        char ch;
        while (!fh.eof()) {
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
    fo.open(token_output_file);
    if (fo.is_open()) {
        for (auto word = words.begin(); word != words.end(); ++word) {
            vector<pair<string, string>> tokens = LA.getAllTokensInText(*word);
            for (auto i = tokens.begin(); i != tokens.end(); ++i) {
                pair<string, string> token = *i;
                if(token.first=="\377"){
                    if(stack.top()!="$"){
                        cout << "Error: The input file finished while the stack isn't empty!" << endl;
                        output_left_most_derivation.push_back("-> Error: The input file finished while the stack isn't empty!");
                        break;
                    }
                    else{
                        cout << "Finished Parsing the input file." << endl;
                        output_left_most_derivation.push_back("-> Finished Parsing the input file.");
                    }

                }
                fo << token.first << " : " << token.second << "\n";
//                cout << token.first << " : " << token.second << "\n";
                cout << token.first << " : " << token.second;
                //the parser work here
                bool get_next_token = false;
                while(!get_next_token){
                    bool is_terminal =  parsing_table.find(stack.top())==parsing_table.end();
//                    cout << ", " << is_terminal;
                    if (is_terminal){
                        if(stack.top()==token.second){
                            cout<< ", Matching "+token.second;
                            output_left_most_derivation.push_back("-> Matching "+token.second);
                            stack.pop();
                            output_left_most_derivation.push_back(get_stack_elements());
                            get_next_token = true;
                        } else{
                            if(stack.top()=="epsilon"){
                                cout << ", Pop epsilon from the stack";
                                stack.pop();
                                output_left_most_derivation.push_back(get_stack_elements());
                            }
                            else {
                                cout << ", Error -> insert " + stack.top() + " in the input";
                                output_left_most_derivation.push_back("-> Error: insert "+stack.top() + " in the input");
                                stack.pop();
                                output_left_most_derivation.push_back(get_stack_elements());
//                                get_next_token = true;
                            }
                        }
                    } else{
                        vector<string> strings = parsing_table[stack.top()][token.second];
                        ostringstream imploded;
                        copy(strings.begin(), strings.end(),
                                  ostream_iterator<std::string>(imploded, " "));

                        if(strings.size()==0){///Nun Terminal No Matching in the parsing table
                            cout<<",Error: Non Terminal can't go to Terminal -> drop that Non Terminal";
                            output_left_most_derivation.push_back("-> Error: Non Terminal can't go to Terminal -> drop that Non Terminal");
                            stack.pop();
                            output_left_most_derivation.push_back(get_stack_elements());
                        } else{
                            cout <<",the new Production: "+imploded.str();
                            stack.pop();
                            for (auto ir = strings.rbegin(); ir != strings.rend(); ++ir) {
                                stack.push(*ir);
                            }
                            output_left_most_derivation.push_back(get_stack_elements());
//                            for(auto &x:strings){
//                                stack.push(x);
//                            }
                        }
                    }
                    cout << endl;
//                    cout<<stack.size()<<endl;
                }
            }
        }
    }
    cout<<"-------- The Leftmost Derivation Sentential --------"<<endl;
    for (auto i = output_left_most_derivation.begin(); i != output_left_most_derivation.end(); ++i)
        cout << *i << endl;
}