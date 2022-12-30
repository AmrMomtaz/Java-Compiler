#include "lexical_analyzer/NFA.h"
#include "lexical_analyzer/DFA.h"
#include "lexical_analyzer/DFA_Minimized.h"
#include "utils/TransitionTable.h"
#include "utils/GrammarIO.h"
#include "lexical_analyzer/LexicalAnalyzerTest.cpp"
#include "parser_generator/GrammarParser.h"
#include "parser_generator/Parser.h"

using namespace std;

/**
 * Driver code (starting point of the project)
 */
int main() {
    ///Dyh el 7agat el Adeema

//    NFA nfa("grammar_input.txt");
//    DFA dfa(nfa);
//    DFA_Minimized dfa_min(dfa.getTransitionTable());
//    //print the minimal DFA
//    TransitionTable TT = dfa_min.getMinimizedTransitionTable();
//    TT.saveTableToFile("minimalDFA.txt");
//    LexicalAnalyzer LA(TT);
//    ////////////////////////////////////////////////////////////////////////////////////////////////
//    unordered_map<string , pair<vector<pair<string , vector<string> >>,vector<string >>> LL1 ;
//    vector<pair<string , vector<string> >> first={make_pair("int",vector<string>{"STATEMENT_LIST"}),make_pair("float",vector<string>{"STATEMENT_LIST"}),make_pair("if",vector<string>{"STATEMENT_LIST"}),make_pair("while",vector<string>{"STATEMENT_LIST"}),make_pair("id",vector<string>{"STATEMENT_LIST"})};
//    vector<string > follow={"$"};
//    LL1["METHOD_BODY"] = make_pair(first,follow);
//    first={make_pair("int",vector<string>{"STATEMENT","A"}),make_pair("float",vector<string>{"STATEMENT","A"}),make_pair("if",vector<string>{"STATEMENT","A"}),make_pair("while",vector<string>{"STATEMENT","A"}),make_pair("id",vector<string>{"STATEMENT","A"})};
//    follow={"$"};
//    LL1["STATEMENT_LIST"] = make_pair(first,follow);
//    first={make_pair("int",vector<string>{"STATEMENT","A"}),make_pair("float",vector<string>{"STATEMENT","A"}),make_pair("if",vector<string>{"STATEMENT","A"}),make_pair("while",vector<string>{"STATEMENT","A"}),make_pair("id",vector<string>{"STATEMENT","A"}),make_pair("epsilon",vector<string>{"epsilon"})};
//    follow={"$"};
//    LL1["A"] = make_pair(first,follow);
//    first={make_pair("int",vector<string>{"DECLARATION"}),make_pair("float",vector<string>{"DECLARATION"}),make_pair("if",vector<string>{"IF"}),make_pair("while",vector<string>{"WHILE"}),make_pair("id",vector<string>{"ASSIGNMENT"})};
//    follow={"int","float","if","while","id"};
//    LL1["STATEMENT"] = make_pair(first,follow);
//    first={make_pair("int",vector<string>{"PRIMITIVE_TYPE","id",";"}),make_pair("float",vector<string>{"PRIMITIVE_TYPE","id",";"})};
//    follow={"int","float","if","while","id","$"};
//    LL1["DECLARATION"] = make_pair(first,follow);
//    first={make_pair("int",vector<string>{"int"}),make_pair("float",vector<string>{"float"})};
//    follow={"id"};
//    LL1["PRIMITIVE_TYPE"] = make_pair(first,follow);
//    first={make_pair("if",vector<string>{"if","(","EXPRESSION",")","{","STATEMENT","}","else","{","STATEMENT","}"})};
//    follow={"int","float","if","while","id","$"};
//    LL1["IF"] = make_pair(first,follow);
//    first={make_pair("while",vector<string>{"while","(","EXPRESSION",")","{","STATEMENT","}"})};
//    follow={"int","float","if","while","id","$"};
//    LL1["WHILE"] = make_pair(first,follow);
//    first={make_pair("id",vector<string>{"id","assign","EXPRESSION",";"})};
//    follow={"int","float","if","while","id","$"};
//    LL1["ASSIGNMENT"] = make_pair(first,follow);
//    first={make_pair("id",vector<string>{"SIMPLE_EXPRESSION","B"}),make_pair("num",vector<string>{"SIMPLE_EXPRESSION","B"}),make_pair("(",vector<string>{"SIMPLE_EXPRESSION","B"}),make_pair("+",vector<string>{"SIMPLE_EXPRESSION","B"}),make_pair("-",vector<string>{"SIMPLE_EXPRESSION","B"})};
//    follow={")",";"};
//    LL1["EXPRESSION"] = make_pair(first,follow);
//    first={make_pair("relop",vector<string>{"relop","SIMPLE_EXPRESSION"}),make_pair("epsilon",vector<string>{"epsilon"})};
//    follow={")",";"};
//    LL1["B"] = make_pair(first,follow);
//    first={make_pair("id",vector<string>{"TERM","C"}),make_pair("num",vector<string>{"TERM","C"}),make_pair("(",vector<string>{"TERM","C"}),make_pair("+",vector<string>{"SIGN","TERM","C"}),make_pair("-",vector<string>{"SIGN","TERM","C"})};
//    follow={"relop",")",";"};
//    LL1["SIMPLE_EXPRESSION"] = make_pair(first,follow);
//    first={make_pair("addop",vector<string>{"addop","TERM","C"}),make_pair("epsilon",vector<string>{"epsilon"})};
//    follow={"relop",")",";"};
//    LL1["C"] = make_pair(first,follow);
//    first={make_pair("id",vector<string>{"FACTOR","D"}),make_pair("num",vector<string>{"FACTOR","D"}),make_pair("(",vector<string>{"FACTOR","D"})};
//    follow={"addop","relop",")",";"};
//    LL1["TERM"] = make_pair(first,follow);
//    first={make_pair("mulop",vector<string>{"mulop","FACTOR","D"}),make_pair("epsilon",vector<string>{"epsilon"})};
//    follow={"addop","relop",")",";"};
//    LL1["D"] = make_pair(first,follow);
//    first={make_pair("id",vector<string>{"id"}),make_pair("num",vector<string>{"num"}),make_pair("(",vector<string>{"(","EXPRESSION",")"})};
//    follow={"mulop","addop","relop",")",";"};
//    LL1["FACTOR"] = make_pair(first,follow);
//    first={make_pair("+",vector<string>{"+"}),make_pair("_",vector<string>{"_"})};
//    follow={"id","num","("};
//    LL1["SIGN"] = make_pair(first,follow);
//    ////////////////////////////////////////////////////////////////////////////////////////////////
//    Parser PA(LA,LL1);
//    PA.printParsingTable();
//    PA.parseInput("test_program.txt","test_program_output.txt","METHOD_BODY");

    ///Dyh 7agat taba3 Momtaz
    GrammarParser grammarParser("parser_grammar.txt");
    unordered_map<string, vector<vector<string>>>& productions = grammarParser.getProductions();
    cout << grammarParser.getStartingSymbol() << endl;
    return 0;
}
