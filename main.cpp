#include "parser.h"
#include "lexical_analyzer.h"

int Node::counter = 1;
int main(int argc, char* argv[])
{
    string relative_path = "../input_example.txt";
    read_input r;


    r.read_lines(relative_path);
    NFA* s = r.regular_expressions["id"];
//    cout << s->node_map.size();

    DFA dfa_2 = DFA(s);
    Node* res = dfa_2.convert_to_DFA();
    vector<Node*> nn;
    for(auto &entry : dfa_2.DFA_node_map)
        nn.push_back(entry.second);

    cout << "Intital Node ID = " << dfa_2.DFA_start_node.id << endl;
    cout << "Number of States = " << dfa_2.DFA_node_map.size() << endl;
    dfa_2.print_dfa();
    cout << "-------------------------------------------------------------------------------" << endl;
    vector<Node*> minimized_dfa = dfa_2.minimize();
    cout << "--------------------------------------------------------------------------------" << endl;
    dfa_2.print_dfa();
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


//    vector<Node*> dfa = lexical_analysis(relative_path, r);
    string file = "../Main.java";
    Parser parser(r);
    parser.parse(minimized_dfa, file);
    return 0;
}