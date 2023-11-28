#include <vector>
using namespace std;
class node
{
    
public:
    char transation;
    vector<node*> next_nodes;
    bool empty;
    node(char transation){
        this->transation = transation;
        empty = true;
    }

    node(char transation, vector<node*>& next_nodes){
        this->transation = transation;
        this->next_nodes = next_nodes;
        empty = true;
    }

    node(){
        empty = true;
    }

    void add_next_node(node& new_node){
        node n = node(new_node.transation, new_node.next_nodes);
        next_nodes.push_back(&n);
    }
};

