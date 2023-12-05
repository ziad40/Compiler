#include "node.h"
#include "NFA.h"
#include "DFA.cpp"

void example1();
void example2();
void example3();
void example4();
void example5();
void example6();
void example7();
void example8();

using namespace std;

int main(){
    /* code */
//    example1();
//    example2();
//    example3();
//    example4();
//    example5();
//    example6();
//    example7();
    example8();
    return 0;
}

void example1(){

    string id0 = "0";
    string id1 = "1";
    string id2 = "2";

    Node q0 = Node(id0);
    Node q1 = Node(id1);
    Node q2 = Node(id2);

    q0.transitions['a'].push_back(&q0);
    q0.transitions['b'].push_back(&q0);
    q0.transitions['a'].push_back(&q1);
    q1.transitions['b'].push_back(&q2);

    q2.acceptance = true;

    NFA nfa = NFA(q0,q2);
    nfa.node_map["0"] = &q0;
    nfa.node_map["1"] = &q1;
    nfa.node_map["2"] = &q2;
    DFA dfa = DFA(&nfa);
    Node* res = dfa.convert_to_DFA();
    dfa.print_dfa();
}

void example2(){
    string id0 = "0";
    string id1 = "1";
    string id2 = "2";

    Node q0 = Node(id0);
    Node q1 = Node(id1);
    Node q2 = Node(id2);

    q0.transitions['0'].push_back(&q0);
    q0.transitions['1'].push_back(&q1);
    q1.transitions['0'].push_back(&q2);
    q2.transitions['0'].push_back(&q2);
    q2.transitions['1'].push_back(&q1);
    q2.transitions['1'].push_back(&q2);

    q2.acceptance = true;

    NFA nfa = NFA(q0,q2);
    nfa.node_map["0"] = &q0;
    nfa.node_map["1"] = &q1;
    nfa.node_map["2"] = &q2;
    DFA dfa = DFA(&nfa);
    Node* res = dfa.convert_to_DFA();
    dfa.print_dfa();
}

void example3(){
    string id0 = "0";
    string id1 = "1";

    Node q0 = Node(id0);
    Node q1 = Node(id1);

    q0.transitions['0'].push_back(&q0);
    q0.transitions['0'].push_back(&q1);
    q0.transitions['1'].push_back(&q1);

    q1.transitions['1'].push_back(&q0);
    q1.transitions['1'].push_back(&q1);

    q1.acceptance = true;

    NFA nfa = NFA(q0,q1);
    nfa.node_map["0"] = &q0;
    nfa.node_map["1"] = &q1;
    DFA dfa = DFA(&nfa);
    Node* res = dfa.convert_to_DFA();
    dfa.print_dfa();
}

void example4(){
    string id0 = "0";
    string id1 = "1";
    string id2 = "2";

    Node q0 = Node(id0);
    Node q1 = Node(id1);
    Node q2 = Node(id2);

    q0.transitions['a'].push_back(&q0);
    q0.transitions['b'].push_back(&q0);
    q0.transitions['b'].push_back(&q1);
    q1.transitions['b'].push_back(&q2);

    q2.acceptance = true;

    NFA nfa = NFA(q0,q2);
    nfa.node_map["0"] = &q0;
    nfa.node_map["1"] = &q1;
    nfa.node_map["2"] = &q2;
    DFA dfa = DFA(&nfa);
    Node* res = dfa.convert_to_DFA();
    dfa.print_dfa();
}

void example5(){
    string id0 = "0";
    string id1 = "1";
    string id2 = "2";

    Node q0 = Node(id0);
    Node q1 = Node(id1);
    Node q2 = Node(id2);

    q0.transitions['0'].push_back(&q0);
    q0.transitions['1'].push_back(&q1);
    q0.transitions['1'].push_back(&q2);
    q1.transitions['0'].push_back(&q1);
    q1.transitions['0'].push_back(&q2);
    q1.transitions['1'].push_back(&q2);
    q2.transitions['0'].push_back(&q0);
    q1.transitions['0'].push_back(&q1);
    q1.transitions['1'].push_back(&q1);

    q2.acceptance = true;

    NFA nfa = NFA(q0,q2);
    nfa.node_map["0"] = &q0;
    nfa.node_map["1"] = &q1;
    nfa.node_map["2"] = &q2;
    DFA dfa = DFA(&nfa);
    Node* res = dfa.convert_to_DFA();
    dfa.print_dfa();
}

void example6(){
    string id0 = "0";
    string id1 = "1";
    string id2 = "2";

    Node q0 = Node(id0);
    Node q1 = Node(id1);
    Node q2 = Node(id2);

    q0.transitions['a'].push_back(&q1);
    q0.transitions['a'].push_back(&q2);
    q2.transitions['a'].push_back(&q1);
    q2.transitions['a'].push_back(&q2);
    q2.transitions['b'].push_back(&q2);

    q1.acceptance = true;

    NFA nfa = NFA(q0,q0);
    nfa.node_map["0"] = &q0;
    nfa.node_map["1"] = &q1;
    nfa.node_map["2"] = &q2;
    DFA dfa = DFA(&nfa);
    Node* res = dfa.convert_to_DFA();
    dfa.print_dfa();
}

void example7(){
    string id0 = "0";
    string id1 = "1";
    string id2 = "2";
    string id3 = "3";
    string id4 = "4";

    Node q0 = Node(id0);
    Node q1 = Node(id1);
    Node q2 = Node(id2);
    Node q3 = Node(id3);
    Node q4 = Node(id4);

    q0.epsilon_transitions.push_back(&q1);
    q0.epsilon_transitions.push_back(&q2);

    q1.transitions['0'].push_back(&q3);
    q2.transitions['1'].push_back(&q3);
    q3.transitions['1'].push_back(&q4);

    q4.acceptance = true;

    NFA nfa = NFA(q0,q0);
    nfa.node_map["0"] = &q0;
    nfa.node_map["1"] = &q1;
    nfa.node_map["2"] = &q2;
    nfa.node_map["3"] = &q3;
    nfa.node_map["4"] = &q4;
    DFA dfa = DFA(&nfa);
    Node* res = dfa.convert_to_DFA();
    dfa.print_dfa();
}

void example8(){
    string id0 = "0";
    string id1 = "1";
    string id2 = "2";

    Node q0 = Node(id0);
    Node q1 = Node(id1);
    Node q2 = Node(id2);

    q0.epsilon_transitions.push_back(&q1);
    q1.epsilon_transitions.push_back(&q2);

    q0.transitions['0'].push_back(&q0);
    q1.transitions['1'].push_back(&q1);
    q2.transitions['2'].push_back(&q2);

    q2.acceptance = true;

    NFA nfa = NFA(q0,q0);
    nfa.node_map["0"] = &q0;
    nfa.node_map["1"] = &q1;
    nfa.node_map["2"] = &q2;
    DFA dfa = DFA(&nfa);
    Node* res = dfa.convert_to_DFA();
    dfa.print_dfa();
}