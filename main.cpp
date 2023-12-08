#include "parser.h"
int main(int argc, char* argv[])
{
    string relative_path = "../input_example.txt";
    vector<Node*> dfa = lexical_analysis(relative_path);
    string file = "../Main.java";
    Parser parser;
    parser.parse(dfa, file);
    return 0;
}