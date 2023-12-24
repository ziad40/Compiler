#include<iostream>
using namespace std;
#include "production.h"

int main(){

    rule r1; 
    r1.name = "S";
    r1.epsilon = false;
    r1.terminal = false;
    
    rule r2;
    r2.name = "i";
    r2.epsilon = false;
    r2.terminal = true;

    rule r3;
    r3.name = "C";
    r3.epsilon = false;
    r3.terminal = false;


    rule r4; 
    r4.name = "t";
    r4.epsilon = false;
    r4.terminal = true;


    rule r5;
    r5.name = "E";
    r5.epsilon = false;
    r5.terminal = false;

    rule r6;
    r6.name = "a";
    r6.epsilon = false;
    r6.terminal = true;

    rule r7;
    r7.name = "e";
    r7.epsilon = false;
    r7.terminal = true;

    rule r8;
    r8.name = "epsilon";
    r8.epsilon = true;
    r8.terminal = true;

    rule r9;
    r9.name = 'b';
    r9.epsilon = false;
    r9.terminal = true;


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


    for (auto p: r1.first)
        cout << p->name << " ";
    cout << endl;

     for (auto p: r5.first)
        cout << p->name << " ";
    cout << endl;

    for (auto p: r3.first)
        cout << p->name << " ";
    cout << endl;
    return 0;
}