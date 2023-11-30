#include <iostream>
#include "node.cpp"
#include "NFA.cpp"
#include "DFA.cpp"

using namespace std;

int main()
{
    /* code */
    Node q0 = Node("0");
    Node q1 = Node("1");
    Node q2 = Node("2");

    q0.transitions['a'].push_back(&q0);
    q0.transitions['b'].push_back(&q0);
    q0.transitions['a'].push_back(&q1);
    q1.transitions['b'].push_back(&q2);

    q2.acceptance = true;

    NFA nfa = NFA(q0,q0);
    DFA dfa = DFA(&nfa);
    Node* res = dfa.convert_to_DFA();
    std::cout << res->id;
    return 0;
};
