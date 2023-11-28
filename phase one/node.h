#include <vector>
using namespace std;
class node
{
    
public:
    vector<char> transation;
    vector<node*> next_nodes;
    int id;
    node(vector<char> transation){
        for(char x : transation){
            this->transation.push_back(x);
        }  
    }

    node(vector<char> transation, vector<node*>& next_nodes){
        for(char x : transation){
            this->transation.push_back(x);
        } 
        this->next_nodes = next_nodes;
    }

    node(){}

    void add_next_node(node& new_node){
        node n = node(new_node.transation, new_node.next_nodes);
        next_nodes.push_back(&n);
    }
};

