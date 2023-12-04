
class node;

class NFA
{

public:
    node* start_node;
    node* end_node;
    map<int, node*> node_map;
    string name;

    NFA(node& start, node& end){
        start_node = &start;
        end_node = &end;
    }

    NFA(){
    }
};


