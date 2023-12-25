//#include<iostream>
//using namespace std;
//#include "production.h"
//#include "parsing_table.h"
//
//int main(){
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
//
//    rule* eps = new rule("eps", true);
//    eps->epsilon = true;
//    return 0;
//}
