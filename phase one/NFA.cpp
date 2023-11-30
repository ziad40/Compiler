#include "node.cpp"
#include <set>

using namespace std;

#ifndef N_F_A_H
#define N_F_A_H
class NFA{
public:
    Node* start_node;
    Node* end_node;
    map<string, Node*> node_map;
    set<char> inputs;
     
    NFA(Node& start, Node& end){
        start_node = &start;
        end_node = &end;
    }
};

#endif

