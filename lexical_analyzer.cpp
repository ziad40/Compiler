#include "lexical_analyzer.h"

int Node::counter = 1;
vector<Node*> lexical_analysis(string relative_path, read_input& r){
    r.read_lines(relative_path);
    NFA* s = r.routing_nfa;
//    cout << s->node_map.size();

    DFA dfa = DFA(s);
    Node* res = dfa.convert_to_DFA();
    cout << "Intital Node ID = " << dfa.DFA_start_node.id << endl;
    cout << "Number of States = " << dfa.DFA_node_map.size() << endl;
    dfa.print_dfa();
    cout << "-------------------------------------------------------------------------------" << endl;
    vector<Node*> minimized_dfa = dfa.minimize();
    cout << "--------------------------------------------------------------------------------" << endl;
    dfa.print_dfa();
    cout << "-----------------------------------------------------------------------------------" << endl;
    for(Node* node : minimized_dfa){
        cout << node->id << "   " << node->acceptance << "     " << endl;
        for(auto &entry : node->transitions){
            cout << entry.first << "->";
            for(Node* next : entry.second){
                cout << next->id << "   ";
            }
        }
        cout<<endl;
    }
    return minimized_dfa;
}