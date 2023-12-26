#include<iostream>
using namespace std;
#include "production.h"

void example1(){
    string name = "S";
    rule r1 = rule(name, false);
    r1.epsilon = false;
    name = "$";
    r1.follow.insert(new rule(name, false));

    name = "i";
    rule r2 = rule(name, true);
    r2.epsilon = false;

    name = "C";
    rule r3 = rule(name, false);
    r3.epsilon = false;

    name = "t";
    rule r4 = rule(name, true);
    r4.epsilon = false;

    name = "E";
    rule r5 = rule(name, false);
    r5.epsilon = false;

    name = "a";
    rule r6 = rule(name, true);
    r6.epsilon = false;

    name = "e";
    rule r7 = rule(name, true);
    r7.epsilon = false;

    name = "epsilon";
    rule r8 = rule(name, true);
    r8.epsilon = true;

    name = "b";
    rule r9 = rule(name, true);
    r9.epsilon = false;


    vector<vector<rule*>> p1;
    vector<rule*> temp1;
    temp1.push_back(&r2);
    temp1.push_back(&r3);
    temp1.push_back(&r4);
    temp1.push_back(&r1);
    temp1.push_back(&r5);

    vector<rule*> temp2;
    temp2.push_back(&r6);

    p1.push_back(temp1);
    p1.push_back(temp2);

    r1.productions = p1;

    vector<vector<rule*>> p2;
    vector<rule*> temp3;
    temp3.push_back(&r7);
    temp3.push_back(&r1);

    vector<rule*> temp4;
    temp4.push_back(&r8);

    p2.push_back(temp3);
    p2.push_back(temp4);
    r5.productions = p2;


    vector<vector<rule*>> p3;
    vector<rule*> temp5;
    temp5.push_back(&r9);
    p3.push_back(temp5);
    r3.productions = p3;

    r1.get_first();
    r5.get_first();
    r3.get_first();

    vector<rule*> rules = {&r1, &r2, &r3, &r4, &r5, &r6, &r7, &r8, &r9};

    r1.get_follow(rules);
    r5.get_follow(rules);
    r3.get_follow(rules);


    for (auto p: r1.first)
        cout << p->name << " ";
    cout << endl;

     for (auto p: r5.first)
        cout << p->name << " ";
    cout << endl;

    for (auto p: r3.first)
        cout << p->name << " ";
    cout << endl;

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

    E->get_first();
    E_dash -> get_first();
    T -> get_first();
    T_dash -> get_first();
    F -> get_first();

    vector<rule*> rules = {E, E_dash, T, T_dash, F, eps, dollar, multiply, plus, open, close, id};

    E -> get_follow(rules);
    E_dash -> get_follow(rules);
    T-> get_follow(rules);
    T_dash-> get_follow(rules);
    F-> get_follow(rules);

    cout << "E:\nfirst:" << endl;
    for (auto p: E->first)
        cout << p->name << " ";
    cout << endl;

    cout << "follow: "<<endl;
    for (auto p: E->follow)
        cout << p->name << " ";
    cout << endl;


    cout << "E`:\nfirst:" << endl;
    for (auto p: E_dash->first)
        cout << p->name << " ";
    cout << endl;

    cout << "follow: "<<endl;
    for (auto p: E_dash->follow)
        cout << p->name << " ";
    cout << endl;

    cout << "T:\nfirst:" << endl;
    for (auto p: T->first)
        cout << p->name << " ";
    cout << endl;

    cout << "follow: "<<endl;
    for (auto p: T->follow)
        cout << p->name << " ";
    cout << endl;

    cout << "T`:\nfirst:" << endl;
    for (auto p: T_dash->first)
        cout << p->name << " ";
    cout << endl;

    cout << "follow: "<<endl;
    for (auto p: T_dash->follow)
        cout << p->name << " ";
    cout << endl;

    cout << "F:\nfirst:" << endl;
    for (auto p: F->first)
        cout << p->name << " ";
    cout << endl;

    cout << "follow: "<<endl;
    for (auto p: F->follow)
        cout << p->name << " ";
    cout << endl;
}

//int main() {
//    example2();
//    return 0;
//}