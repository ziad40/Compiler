#include <iostream>
#include "parsing_table.h"
#include "production.h"

using namespace std;

int main(){
    rule* eps = new rule("eps", true);
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
    cout << "Done";
    return 0;
}