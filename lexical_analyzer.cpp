#include "lexical_analyzer.h"

// int Node::counter = 1;
vector<Node *> lexical_analysis(string relative_path, read_input &r)
{
    r.read_lines(relative_path);
    NFA *s = r.routing_nfa;
    //    cout << s->node_map.size();

    DFA dfa = DFA(s);
    Node *res = dfa.convert_to_DFA();
    cout << "Intital Node ID = " << dfa.DFA_start_node.id << endl;
    cout << "Number of States = " << dfa.DFA_node_map.size() << endl;
    //    dfa.print_dfa();
    cout << "-------------------------------------------------------------------------------" << endl;
    vector<Node *> minimized_dfa = dfa.minimize();
    cout << "--------------------------------------------------------------------------------" << endl;
    vector<Node *> nn;
    for (auto &entry : dfa.DFA_node_map)
        nn.push_back(entry.second);

    return minimized_dfa;
}