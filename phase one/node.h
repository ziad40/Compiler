#include <vector>
using namespace std;
class node
{
    
public:
    vector<char> transations;
    vector<node*> next_nodes;
    int id;
    bool acceptance;
    node(vector<char> transation){
        for(char x : transation){
            this->transations.push_back(x);
        }
        acceptance = false;  
    }

    node(vector<char> transation, vector<node*>& next_nodes){
        for(char x : transation){
            this->transations.push_back(x);
        } 
        this->next_nodes = next_nodes;
        acceptance = false;  
    }

    node(){
        acceptance = false;  
    }

    node(int ID){
        id = ID;
        acceptance = false;  
    }

    void add_next_node(node& new_node){
        node n = node(new_node.transations, new_node.next_nodes);
        next_nodes.push_back(&n);
    }
};

