#include "parser.h"
int main(int argc, char* argv[])
{
    string relative_path = "../input_example.txt";
    read_input r;
    vector<Node*> dfa = lexical_analysis(relative_path, r);
    string file = "../Main.java";
    Parser parser(r);
    parser.parse(dfa, file);
    return 0;
}