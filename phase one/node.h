#include <vector>
#include <map>
using namespace std;
class node
{
    
public:
    map<char, vector<node*>> transitions;
    vector<node*> epsilon_transitions;
    int id;
    bool acceptance;
    node(map<char, vector<node*>> transitions){
        this-> transitions = transitions;
        acceptance = false;  
    }

    node(){
        acceptance = false;  
    }

    node(int ID){
        id = ID;
        acceptance = false;  
    }

    void add_next_node(node* new_node){
        epsilon_transitions.push_back(new_node);
    }

    void add_next_node(char c, node* new_node){
        transitions[c].push_back(new_node);
    }
};

