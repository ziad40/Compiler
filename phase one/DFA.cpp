#include "NFA.cpp"
#include "node.cpp"
#include <iostream>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
#include <iterator>
#include<vector>

using namespace std;

class DFA{
    public:
        NFA* nfa;
        Node DFA_start_node;
        map<string, Node*> DFA_node_map;
    
    DFA(NFA* final_nfa){
        nfa = final_nfa;
        string start_node_id = generate_node_id(get_eq_epsilon_neighbors(final_nfa->start_node));
        DFA_start_node = Node(start_node_id);
        is_accepted(&DFA_start_node);
        DFA_node_map[start_node_id] = &DFA_start_node;
    }

    Node* convert_to_DFA(){
        queue<Node*> queue;
        set<string> visited_id;

        queue.push(&DFA_start_node);
        while(!queue.empty()){
            // 15697
            Node* n = queue.front();
            queue.pop();
            if(visited_id.find(n->id) != visited_id.end())
                continue;
            visited_id.insert(n->id);
            set<Node*> neighbors = handle_node_transactions(n);
            set<Node*>::iterator it = neighbors.begin();
            while (it != neighbors.end()) {
                queue.push(*it);
            }            
        }
        return &DFA_start_node;
    }

    set<Node*> handle_node_transactions(Node* n){ // 15679
        set<Node*> neighbors;
        map<char, string> current_node_transactions;

        for(char sub_node_id : n->id){ // 1
            Node* sub_node = nfa->node_map[sub_node_id+""];
            for (auto &entry : sub_node->transitions) { // all 1 inputs
                for(Node* next : entry.second){
                    current_node_transactions[entry.first]+=next->id;
                }
            }
        }

        for(auto &entry : current_node_transactions){ // a->2467
            set<Node*> input_next_node;  
            for(char sub_node_id : entry.second){ // 2
                set<Node*> sub_node_eps_neighbors = get_eq_epsilon_neighbors(nfa->node_map[sub_node_id+""]);
                input_next_node.insert(sub_node_eps_neighbors.begin(), sub_node_eps_neighbors.end());
            }
            // now we have eps for all 2467 so now create new node and add it to trans of current
            string new_node_id = generate_node_id(input_next_node);
            Node new_node = Node(new_node_id);
            is_accepted(&new_node);
            DFA_node_map[new_node_id] = &new_node;
            // just 1 node --------------------
            n->transitions[entry.first].push_back(&new_node);    
            neighbors.insert(&new_node);        
        }
        return neighbors;
    }

    set<Node*> get_eq_epsilon_neighbors(Node* n){
        stack<Node*> epsilon_neighbors;
        set<Node*> visited;
        epsilon_neighbors.push(n);

        while(!epsilon_neighbors.empty()){
            Node* neighbor = epsilon_neighbors.top();
            epsilon_neighbors.pop();
            if(visited.find(neighbor) != visited.end())
                continue;
            visited.insert(neighbor);
            for(Node* ep_neighbor : neighbor->epsilon_transitions){
                epsilon_neighbors.push(ep_neighbor);
            }
        }
        return visited;
    }

    string generate_node_id(set<Node*> nodes){
        string state_id = "";

        // std::vector<Node*> nodesVector(nodes.begin(), nodes.end());
        // std::sort(nodesVector.begin(), nodesVector.end(), [](Node* a, Node* b) { return a->id < b->id; });
        // std::set<Node*> sortedNodes(nodesVector.begin(), nodesVector.end());
        // sort(nodes.begin(), nodes.end(), [](Node* a, Node* b){return a->id < b->id;});

        set<Node*>::iterator it = nodes.begin();
        while (it != nodes.end()) {
            state_id += (*it)->id;
        }
        return state_id;
    }

    void is_accepted(Node* n){
        for(char c : n->id){
            Node* sub_node = nfa->node_map[c+""];
            if(sub_node->acceptance){
                n->acceptance = true;
                return;
            }
        }
        n->acceptance = false;
    }
};