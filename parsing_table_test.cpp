#include<iostream>
using namespace std;
#include "cfg_input_parser.h"
#include "production.h"
//#include "parsing_table.h"

void example1();
void example2();
void example3();

int main(){
//    example1();
//    example2();
    example3();
    return 0;
}

void example1(){
    string name = "eps";
    rule* eps = new rule(name,true);
    eps->epsilon = true;
    name = "$";
    rule* dollar = new rule(name, true);
    name = "i";
    rule* i = new rule(name, true);
    name = "t";
    rule* t = new rule(name, true);
    name = "e";
    rule* e = new rule(name, true);
    name = "a";
    rule* a = new rule(name, true);
    name = "b";
    rule* b = new rule(name, true);

    name = "S";
    rule* S = new rule(name, false);
    name = "E";
    rule* E = new rule(name, false);
    E->has_epsilon_first = true;
    name = "C";
    rule* C = new rule(name, false);

    //first
    S->first.insert(i);
    S->first.insert(a);

    E->first.insert(e);
    E->first.insert(eps);

    C->first.insert(b);

    // follow
    S->follow.insert(dollar);
    S->follow.insert(e);

    E->follow.insert(dollar);
    E->follow.insert(e);

    C->follow.insert(t);


    // productions
    vector<rule*> prodS1;
    prodS1.push_back(i);
    prodS1.push_back(C);
    prodS1.push_back(t);
    prodS1.push_back(S);
    prodS1.push_back(E);

    vector<rule*> prodS2;
    prodS2.push_back(a);

    S->productions.push_back(prodS1);
    S->productions.push_back(prodS2);

    vector<rule*> prodE1;
    prodE1.push_back(e);
    prodE1.push_back(S);

    vector<rule*> prodE2;
    prodE2.push_back(eps);

    E->productions.push_back(prodE1);
    E->productions.push_back(prodE2);


    vector<rule*> prodC1;
    prodC1.push_back(b);

    C->productions.push_back(prodC1);

    // first 2 exp
    vector<rule*> first2expS1;
    first2expS1.push_back(i);
    first2expS1.push_back(C);
    first2expS1.push_back(t);
    first2expS1.push_back(S);
    first2expS1.push_back(E);

    vector<rule*> first2expS2;
    first2expS2.push_back(a);

    S->first_to_expression[i] = first2expS1;
    S->first_to_expression[a] = first2expS2;

    vector<rule*> first2expE1;
    first2expE1.push_back(e);
    first2expE1.push_back(S);

    vector<rule*> first2expE2;
    first2expE2.push_back(eps);

    E->first_to_expression[e] = first2expE1;
    E->first_to_expression[eps] = first2expE2;

    vector<rule*> first2expC1;
    first2expC1.push_back(b);

    C->first_to_expression[b] = first2expC1;

    set<rule*> NT;
    set<rule*> T;
    NT.insert(S);
    NT.insert(E);
    NT.insert(C);

    T.insert(dollar);
    T.insert(i);
    T.insert(t);
    T.insert(e);
    T.insert(a);
    T.insert(b);

    parsing_table pt = parsing_table(NT, T);
    pt.get_parsing_table();
    pt.print_parsing_table();
    cout << "\nDone";
}

void example2(){
    string name = "eps";
    rule* eps = new rule(name,true);
    eps->epsilon = true;

    name = "$";
    rule* dollar = new rule(name, true);

    name = "+";
    rule* plus = new rule(name, true);

    name = "*";
    rule* multiply = new rule(name, true);

    name = "(";
    rule* open = new rule(name, true);

    name = ")";
    rule* close = new rule(name, true);

    name = "id";
    rule* id = new rule(name, true);



    name = "E";
    rule* E = new rule(name, false);

    name = "E'";
    rule* E_dash = new rule(name, false);

    name = "T";
    rule* T = new rule(name, false);

    name = "T'";
    rule* T_dash = new rule(name, false);

    name = "F";
    rule* F = new rule(name, false);

    E_dash->has_epsilon_first = true;
    T_dash->has_epsilon_first = true;

    //first
    E->first.insert(open);
    E->first.insert(id);

    E_dash->first.insert(plus);
    E_dash->first.insert(eps);

    T->first.insert(open);
    T->first.insert(id);

    T_dash->first.insert(multiply);
    T_dash->first.insert(eps);

    F->first.insert(open);
    F->first.insert(id);

    // follow
    E->follow.insert(dollar);
    E->follow.insert(close);

    E_dash->follow.insert(dollar);
    E_dash->follow.insert(close);

    T->follow.insert(plus);
    T->follow.insert(close);
    T->follow.insert(dollar);

    T_dash->follow.insert(plus);
    T_dash->follow.insert(close);
    T_dash->follow.insert(dollar);

    F->follow.insert(plus);
    F->follow.insert(close);
    F->follow.insert(multiply);
    F->follow.insert(dollar);

    // productions
    vector<rule*> prodE1;
    prodE1.push_back(T);
    prodE1.push_back(E_dash);

    E->productions.push_back(prodE1);

    vector<rule*> prodE_dash1;
    prodE_dash1.push_back(plus);
    prodE_dash1.push_back(T);
    prodE_dash1.push_back(E_dash);

    vector<rule*> prodE_dash2;
    prodE_dash2.push_back(eps);

    E_dash->productions.push_back(prodE_dash1);
    E_dash->productions.push_back(prodE_dash2);


    vector<rule*> prodT1;
    prodT1.push_back(F);
    prodT1.push_back(T_dash);

    T->productions.push_back(prodT1);

    vector<rule*> prodT_dash1;
    prodT_dash1.push_back(multiply);
    prodT_dash1.push_back(F);
    prodT_dash1.push_back(T_dash);

    vector<rule*> prodT_dash2;
    prodT_dash2.push_back(eps);

    T_dash->productions.push_back(prodT_dash1);
    T_dash->productions.push_back(prodT_dash2);


    vector<rule*> prodF1;
    prodF1.push_back(open);
    prodF1.push_back(E);
    prodF1.push_back(close);

    vector<rule*> prodF2;
    prodF2.push_back(id);

    F->productions.push_back(prodF1);
    F->productions.push_back(prodF2);

    // first to exp
    vector<rule*> first2expE1;
    first2expE1.push_back(T);
    first2expE1.push_back(E_dash);


    E->first_to_expression[open] = first2expE1;
    E->first_to_expression[id] = first2expE1;


    vector<rule*> first2expE_dash1;
    first2expE_dash1.push_back(plus);
    first2expE_dash1.push_back(T);
    first2expE_dash1.push_back(E_dash);

    vector<rule*> first2expE_dash2;
    first2expE_dash2.push_back(eps);

    E_dash->first_to_expression[plus] = first2expE_dash1;
    E_dash->first_to_expression[eps] = first2expE_dash2;

    vector<rule*> first2expT1;
    first2expT1.push_back(F);
    first2expT1.push_back(T_dash);

    T->first_to_expression[open] = first2expT1;
    T->first_to_expression[id] = first2expT1;

    vector<rule*> first2expT_dash1;
    first2expT_dash1.push_back(multiply);
    first2expT_dash1.push_back(F);
    first2expT_dash1.push_back(T_dash);

    vector<rule*> first2expT_dash2;
    first2expT_dash2.push_back(eps);

    T_dash->first_to_expression[multiply] = first2expT_dash1;
    T_dash->first_to_expression[eps] = first2expT_dash2;

    vector<rule*> first2expF1;
    first2expF1.push_back(open);
    first2expF1.push_back(E);
    first2expF1.push_back(close);

    vector<rule*> first2expF2;
    first2expF2.push_back(id);

    F->first_to_expression[open] = first2expF1;
    F->first_to_expression[id] = first2expF2;

    set<rule*> NT;
    set<rule*> Terminals;
    NT.insert(E);
    NT.insert(E_dash);
    NT.insert(T);
    NT.insert(T_dash);
    NT.insert(F);

    Terminals.insert(id);
    Terminals.insert(plus);
    Terminals.insert(multiply);
    Terminals.insert(open);
    Terminals.insert(close);
    Terminals.insert(dollar);

    parsing_table pt = parsing_table(NT, Terminals);
    pt.get_parsing_table();
    pt.print_parsing_table();
    cout << "\nDone";
}

void example3(){
    string name = "eps";
    rule* eps = new rule(name,true);
    eps->epsilon = true;
    name = "$";
    rule* dollar = new rule(name, true);
    name = "c";
    rule* c = new rule(name, true);
    name = "d";
    rule* d = new rule(name, true);
    name = "e";
    rule* e = new rule(name, true);
    name = "a";
    rule* a = new rule(name, true);
    name = "b";
    rule* b = new rule(name, true);

    name = "S";
    rule* S = new rule(name, false);
    S->has_epsilon_first = true;
    name = "A";
    rule* A = new rule(name, false);

    //first
    S->first.insert(a);
    S->first.insert(c);
    S->first.insert(e);
    S->first.insert(eps);

    A->first.insert(a);
    A->first.insert(c);

    // follow
    S->follow.insert(dollar);

    A->follow.insert(b);
    A->follow.insert(d);


    // productions
    vector<rule*> prodS1;
    prodS1.push_back(A);
    prodS1.push_back(b);
    prodS1.push_back(S);

    vector<rule*> prodS2;
    prodS2.push_back(e);

    vector<rule*> prodS3;
    prodS3.push_back(eps);

    S->productions.push_back(prodS1);
    S->productions.push_back(prodS2);
    S->productions.push_back(prodS3);

    vector<rule*> prodA1;
    prodA1.push_back(a);

    vector<rule*> prodA2;
    prodA2.push_back(c);
    prodA2.push_back(A);
    prodA2.push_back(d);

    A->productions.push_back(prodA1);
    A->productions.push_back(prodA2);

    // first 2 exp
    vector<rule*> first2expS1;
    first2expS1.push_back(A);
    first2expS1.push_back(b);
    first2expS1.push_back(S);

    vector<rule*> first2expS2;
    first2expS2.push_back(e);

    vector<rule*> first2expS3;
    first2expS3.push_back(eps);

    S->first_to_expression[a] = first2expS1;
    S->first_to_expression[c] = first2expS1;
    S->first_to_expression[e] = first2expS2;

    vector<rule*> first2expA1;
    first2expA1.push_back(a);

    vector<rule*> first2expA2;
    first2expA2.push_back(c);
    first2expA2.push_back(A);
    first2expA2.push_back(d);

    A->first_to_expression[a] = first2expA1;
    A->first_to_expression[c] = first2expA2;

    set<rule*> NT;
    set<rule*> T;
    NT.insert(S);
    NT.insert(A);

    T.insert(dollar);
    T.insert(c);
    T.insert(d);
    T.insert(e);
    T.insert(a);
    T.insert(b);

    parsing_table pt = parsing_table(NT, T);
    pt.get_parsing_table();
    pt.print_parsing_table();

    cfg_input_parser cfgInputParser = cfg_input_parser(pt.parsing_map, pt.status_map, *pt.NT.begin());
    string example = "aab$";
//    string example = "ceadb$";
    for(char x : example){
        cfgInputParser.parse_lexicial(string(1,x));
    }
    cout << "\nDone";
}
