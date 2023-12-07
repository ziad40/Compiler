#include "lexical_analyzer.h"
#include <sstream>
using namespace std;
string read_java_file(string path)
{
    ifstream f(path);
    string str;
    if (f)
    {
        ostringstream ss;
        ss << f.rdbuf(); // reading data
        str = ss.str();
    }
    return str;
}
int main(int argc, char* argv[])
{
    string relative_path = "/Users/adele/Desktop/College/Year4/Term1/CSE421-Compilers/Project/input_example.txt";
    vector<Node*> dfa = lexical_analysis(relative_path);
    string file = read_java_file("/Users/adele/Desktop/College/Year4/Term1/CSE421-Compilers/Project/Main.java");

    Node* prev_node = nullptr;
    Node* current_node = dfa[0];
    bool prev_node_acceptance = false;
    bool current_node_acceptance = current_node->acceptance;
    for(char c : file){
        for(auto &entry : current_node->transitions){
            char t = entry.first;
            if(t == c){
                prev_node = current_node;
                prev_node_acceptance = prev_node->acceptance;
                current_node = entry.second[0];
                current_node_acceptance = current_node->acceptance;
                break;
            }
        }
    }
    return 0;
}