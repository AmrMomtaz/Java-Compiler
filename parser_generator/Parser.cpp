#include <iterator>
#include "Parser.h"
Parser::Parser(LexicalAnalyzer &la, unordered_map<string,pair<vector<pair<string,vector<string>>>,set<string>>> &LL1 ) : LA(la) {
    valid_parsing_table=make_parsing_table(LL1);
    stack.push("$");
    std::cout << "[INFO] New parser created" << "\n";
}
bool Parser::make_parsing_table(unordered_map<string, pair
        <vector<pair<string,vector<string>>>,
        set<string>>> &LL1) {
    for (auto x : LL1){
//        cout << x.first << " " << x.second.first.size() << endl;
        unordered_map<string,vector<string>> temp;
        for(auto& first: x.second.first){
            if(first.first!="Epsilon") {
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
                    if (temp.count(follow)==0||(temp[follow].size()==1&&temp[follow][0]=="sync")) {
                        vector<string> v;
                        v.push_back("Epsilon");
                        temp[follow] = v;
//                    std::cout << follow << ' ';
                    } else{
                        cout<< "-> ERROR: the Grammar is ambiguous!"<<endl;
                        return false;
                    }
                }
            }
        }
//        cout << "\n";
        parsing_table[x.first]=temp;
    }
    return true;
}
void Parser::printParsingTable(){
    cout <<"--------------------------------- Parsing Table ----------------------------------"<<endl;
    for (auto x : parsing_table){
        cout<< x.first<<": "<< endl;
        for (auto y : x.second){
            cout << y.first<<": ";
            for (auto z : y.second){
                cout<<z<<" ";
            }
            cout << endl;
        }
        cout <<"________________________________________________________"<<endl;
    }
    cout<<"------------------------------ End of Parsing Table--------------------------------"<<endl;
}
string Parser::get_stack_elements(){
    if(stack.empty()) return "";
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
vector<string> Parser::get_stack_elements_vector(){
    if(stack.empty()) return vector<string>{""};
    ::stack<string> tempt;
    vector<string> strings;
    while(stack.size()!=1) {
        tempt.push(stack.top());
        strings.push_back(stack.top()+=" ");
        stack.pop();
    }
    while(!tempt.empty()) {
        stack.push(tempt.top());
        tempt.pop();
    }
    return strings;
}
void Parser::parseInput(string starting_production, string input_file_path, string token_output_file, string left_most_derivation_output_file, string stack_events_and_errors){
    vector<string> stack_statements;
    int current_place = 0;
    vector<vector<string>> output_left_most_derivation;

    stack.push(starting_production);
    stack_statements.push_back(get_stack_elements());
    output_left_most_derivation.push_back(get_stack_elements_vector());

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
    cout<<"--------------------------------- The input file ----------------------------------"<<endl;
    cout << input_text << "\n";
    fh.close();

    // split the input text on the white space
    vector<string> words = LA.split_string_by_white_spaces(input_text);

    bool text_ended = false;
    bool set_text_ended = false;
    cout << "------------------------------- Tokens and events --------------------------------" << "\n";
    ofstream fo;
    fo.open(token_output_file);
    if (fo.is_open()) {
        for (auto word = words.begin(); word != words.end(); ++word) {
            vector<pair<string, string>> tokens = LA.getAllTokensInText(*word);
            for (auto i = tokens.begin(); i != tokens.end(); ++i) {
                pair<string, string> token = *i;
                if(token.first=="\377"&&!text_ended){
                    set_text_ended= true;
                    token.first="\377";
                    token.second="$";
                }
                if(token.first=="\377"&&text_ended){
                    if(stack.top()!="$"){
                        cout << "Error: The input file finished while the stack isn't empty!" << endl;
                        stack_statements.push_back("-> Error: The input file finished while the stack isn't empty!");
                        break;
                    }
                    else{
                        cout << "Finished Parsing the input file." << endl;
                        stack_statements.push_back("-> Finished Parsing the input file.");
                    }

                }
                if(set_text_ended){
                    text_ended= true;
                }
                fo << token.first << " : " << token.second << "\n";
//                cout << token.first << " : " << token.second << "\n";
                cout << token.first << " : " << token.second;
                //the parser work here
                bool get_next_token = false;
                while(!get_next_token){
                    if(stack.empty()){
                        get_next_token= true;
                        break;
                    }
                    bool is_terminal =  parsing_table.find(stack.top())==parsing_table.end();
//                    cout << ", " << is_terminal;
                    if (is_terminal){
                        if(stack.top()==token.second){
                            cout<< ", Matching "+token.second;
                            stack_statements.push_back("-> Matching " + token.second);
                            stack.pop();
                            stack_statements.push_back(get_stack_elements());
                            current_place+=1;
                            get_next_token = true;
                        } else{
                            if(stack.top()=="Epsilon"){
                                cout << ", Pop Epsilon from the stack";
                                stack.pop();
                                stack_statements.push_back(get_stack_elements());
                                current_place+=1;
                            }
                            else {
                                cout << ", Error -> insert " + stack.top() + " in the input";
                                stack_statements.push_back("-> Error: insert " + stack.top() + " in the input");
                                stack.pop();
                                stack_statements.push_back(get_stack_elements());
                                current_place+=1;
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
                            cout<<", solution: discard "+token.first + " from the input";
                            stack_statements.push_back("-> Error: discard " + token.first + " from the input");
                            stack_statements.push_back(get_stack_elements());
                            get_next_token= true;
                        } else{
                            if(strings.size()==1&&strings[0]=="sync"){
                                cout<<", pop the Non-terminal "+stack.top()+" from the stack";
                                stack_statements.push_back("-> Pop the Non-terminal " + stack.top() + " from the stack");
                                stack.pop();
                                stack_statements.push_back(get_stack_elements());

                                vector<string> temp=output_left_most_derivation[output_left_most_derivation.size()-1];
                                temp[current_place]="sync";
                                current_place+=1;
                                output_left_most_derivation.push_back(temp);
                                continue;
                            }
                            cout <<",the new Production: "+imploded.str();
                            stack.pop();
                            current_place+=1;

                            for (auto ir = strings.rbegin(); ir != strings.rend(); ++ir) {
                                stack.push(*ir);
                            }
                            stack_statements.push_back(get_stack_elements());

                            int current = 0;
                            vector<string> temp=output_left_most_derivation[output_left_most_derivation.size()-1];
                            for (auto ir = strings.begin(); ir != strings.end(); ++ir) {
                                temp.insert(temp.begin() + current_place + current, *ir);
                                current+=1;
                            }
                            temp.erase(temp.begin() + current_place - 1);
                            current_place-=1;
                            output_left_most_derivation.push_back(temp);
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
//    fo.close();

    ofstream fo_2;
    fo_2.open(stack_events_and_errors);
    if (fo_2.is_open()) {
        cout << "-------------------------------- The Stack Updates --------------------------------" << endl;
        for (auto i = stack_statements.begin(); i != stack_statements.end(); ++i) {
            cout << *i << endl;
            fo_2 << *i << endl;
        }
    }

    ofstream fo_1;
    fo_1.open(left_most_derivation_output_file);
    if (fo_1.is_open()) {
        cout<<"------------------------ The Leftmost Derivation Sentential ------------------------"<<"\n";
        fo_1<<"------------------------ The Leftmost Derivation Sentential ------------------------"<<"\n";
        for (auto i = output_left_most_derivation.begin(); i != output_left_most_derivation.end(); ++i) {
            ostringstream imploded;
            vector<string> strings = *i;
            copy(strings.begin(), strings.end(),
                 ostream_iterator<std::string>(imploded, " "));
            cout << imploded.str() << "\n";
            fo_1 << imploded.str() << "\n";
        }
    }
}