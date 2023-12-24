#include<iostream>
using namespace std;
#include "production.h"
#include "parsing_table.h"

void example1();
void example2();

int main(){

//    rule r1 = rule("S", false);
//    r1.epsilon = false;
//
//    rule r2 = rule("i", true);
//    r2.epsilon = false;
//
//
//    rule r3 = rule("C", false);
//    r3.epsilon = false;
//
//
//    rule r4 = rule("t", true);
//    r4.epsilon = false;
//
//
//    rule r5 = rule("E", false);
//    r5.epsilon = false;
//
//    rule r6 = rule("a", true);
//    r6.epsilon = false;
//
//    rule r7 = rule("e", true);
//    r7.epsilon = false;
//
//    rule r8 = rule("epsilon", true);
//    r8.epsilon = true;
//
//    rule r9 = rule("b", true);
//    r9.epsilon = false;
//
//
//    vector<vector<rule*>> p1;
//    vector<rule*> temp1;
//    temp1.push_back(&r2);
//    temp1.push_back(&r3);
//    temp1.push_back(&r4);
//    temp1.push_back(&r1);
//    temp1.push_back(&r5);
//
//    vector<rule*> temp2;
//    temp2.push_back(&r6);
//
//    p1.push_back(temp1);
//    p1.push_back(temp2);
//
//    r1.productions = p1;
//
//    vector<vector<rule*>> p2;
//    vector<rule*> temp3;
//    temp3.push_back(&r7);
//    temp3.push_back(&r1);
//
//    vector<rule*> temp4;
//    temp4.push_back(&r8);
//
//    p2.push_back(temp3);
//    p2.push_back(temp4);
//    r5.productions = p2;
//
//
//    vector<vector<rule*>> p3;
//    vector<rule*> temp5;
//    temp5.push_back(&r9);
//    p3.push_back(temp5);
//    r3.productions = p3;
//
//    r1.get_first();
//    r5.get_first();
//    r3.get_first();
//
//
//    for (auto p: r1.first)
//        cout << p->name << " ";
//    cout << endl;
//
//     for (auto p: r5.first)
//        cout << p->name << " ";
//    cout << endl;
//
//    for (auto p: r3.first)
//        cout << p->name << " ";
//    cout << endl;

//    rule* eps = new rule("eps", true);
//    eps->epsilon = true;
    example2();
    return 0;
}

void example1(){
    rule* eps = new rule("eps",true);
    eps->epsilon = true;
    rule* dollar = new rule("$", true);
    rule* i = new rule("i", true);
    rule* t = new rule("t", true);
    rule* e = new rule("e", true);
    rule* a = new rule("a", true);
    rule* b = new rule("b", true);


    rule* S = new rule("S", false);
    rule* E = new rule("E", false);
    E->has_epsilon_first = true;
    rule* C = new rule("C", false);

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
    rule* eps = new rule("eps",true);
    eps->epsilon = true;
    rule* dollar = new rule("$", true);
    rule* plus = new rule("plus", true);
    rule* multiply = new rule("multi", true);
    rule* open = new rule("(", true);
    rule* close = new rule(")", true);
    rule* id = new rule("id", true);


    rule* E = new rule("E", false);
    rule* E_dash = new rule("E'", false);
    rule* T = new rule("Terminals", false);
    rule* T_dash = new rule("Terminals'", false);
    rule* F = new rule("F", false);
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
    prodT_dash1.push_back(plus);
    prodT_dash1.push_back(F);
    prodT_dash1.push_back(T_dash);

    T_dash->productions.push_back(prodT_dash1);

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

    E->first_to_expression[plus] = first2expE_dash1;
    E->first_to_expression[eps] = first2expE_dash2;

    vector<rule*> first2expC1;
    first2expC1.push_back(b);

    C->first_to_expression[b] = first2expC1;

    set<rule*> NT;
    set<rule*> Terminals;
    NT.insert(E);
    NT.insert(E_dash);
    NT.insert(T);
    NT.insert(T_dash);
    NT.insert(F);

    Terminals.insert(dollar);
    Terminals.insert(plus);
    Terminals.insert(multiply);
    Terminals.insert(open);
    Terminals.insert(close);
    Terminals.insert(id);

    parsing_table pt = parsing_table(NT, Terminals);
    pt.get_parsing_table();
    pt.print_parsing_table();
    cout << "\nDone";
}
