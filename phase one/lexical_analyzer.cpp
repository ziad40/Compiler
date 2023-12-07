#include "read_input.cpp"
#include "DFA.cpp"

#include <fstream>

int Node::counter = 1;
int main(){
    string relative_path = "/media/elsharawy/Data/CSED/level 4 term 1/Compilers/compilers project/Compiler/phase one/input_example.txt";
    read_input r;
    r.read_lines(relative_path);
    NFA* s = r.routing_nfa;
    DFA dfa = DFA(s);
    Node* res = dfa.convert_to_DFA();
    dfa.print_dfa();
    return 0;
}