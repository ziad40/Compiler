#include "read_input.cpp"
#include "DFA.cpp"

#include <fstream>

int Node::counter = 1;
int main(){
    string relative_path = "/media/elsharawy/Data/CSED/level 4 term 1/Compilers/compilers project/Compiler/phase one/input_example.txt";
    read_input r;
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
    return 0;
}