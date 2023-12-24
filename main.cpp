//#include "parser.h"
//#include "lexical_analyzer.h"
//
//int Node::counter = 1;
//int main(int argc, char* argv[])
//{
//    string relative_path = "../input_example.txt";
//    read_input r;
//
//
//    r.read_lines(relative_path);
//    NFA* s = r.routing_nfa;
////    cout << s->node_map.size();
//
//    DFA dfa_2 = DFA(s);
//    Node* res = dfa_2.convert_to_DFA();
//    cout << "Intital Node ID = " << dfa_2.DFA_start_node.id << endl;
//    cout << "Number of States = " << dfa_2.DFA_node_map.size() << endl;
//    dfa_2.print_dfa();
////    cout << "-------------------------------------------------------------------------------" << endl;
////    vector<Node*> minimized_dfa = dfa.minimize();
////    cout << "--------------------------------------------------------------------------------" << endl;
////    dfa.print_dfa();
////    cout << "-----------------------------------------------------------------------------------" << endl;
//
//
//    vector<Node*> nn;
//    for(auto &entry : dfa_2.DFA_node_map)
//        nn.push_back(entry.second);
//
////    vector<Node*> dfa = lexical_analysis(relative_path, r);
//    string file = "../Main.java";
//    Parser parser(r);
//    parser.parse(nn, file);
//    return 0;
//}