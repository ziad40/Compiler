#include "read_input.cpp"
#include "DFA.cpp"

int Node::counter = 1;
int main(){
    read_input r;
    r.read_lines(R"(/media/elsharawy/Data/CSED/level 4 term 1/Compilers/compilers project/Compiler/phase one/input_example.txt)");
    NFA* s = r.regular_definations["letter"];
    DFA dfa = DFA(s);
    Node* res = dfa.convert_to_DFA();
    dfa.print_dfa();
    return 0;
}