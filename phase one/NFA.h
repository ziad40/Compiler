#include "node.h"
class NFA
{

public:
    node* start_node;
    node* end_node;
    
     
    NFA(node& start, node& end){
        start_node = &start;
        end_node = &end;
    }
};


