#include "NFA.h"
#include "node.h"
#include <iostream>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
#include <iterator>

using namespace std;

class DFA{
    public:
        NFA* nfa;
        node DFA_start_node;
        map<string, node*> DFA_node_map;
    
    DFA(NFA* final_nfa){
        nfa = final_nfa;
        string start_node_id = generate_node_id(get_eq_epsilon_neighbors(final_nfa->start_node));
        DFA_start_node = node(start_node_id);
        is_accepted(&DFA_start_node);
        DFA_node_map[start_node_id] = &DFA_start_node;
    }

    node* convert_to_DFA(){
        queue<node*> queue;
        set<string> visited_id;

        queue.push(&DFA_start_node);
        while(!queue.empty()){
            // 15697
            node* n = queue.front();
            queue.pop();
            if(visited_id.find(n->id) != visited_id.end())
                continue;
            visited_id.insert(n->id);
            set<node*> neighbors = handle_node_transactions(n);
            set<node*>::iterator it = neighbors.begin();
            while (it != neighbors.end()) {
                queue.push(*it);
            }            
        }
        return &DFA_start_node;
    }

    set<node*> handle_node_transactions(node* n){ // 15679
        set<node*> neighbors;
        map<char, string> current_node_transactions;

        for(char sub_node_id : n->id){ // 1
            node* sub_node = nfa->node_map[sub_node_id+""];
            for (auto &entry : sub_node->transitions) { // all 1 inputs
                for(node* next : entry.second){
                    current_node_transactions[entry.first]+=next->id;
                }
            }
        }

        for(auto &entry : current_node_transactions){ // a->2467
            set<node*> input_next_node;  
            for(char sub_node_id : entry.second){ // 2
                set<node*> sub_node_eps_neighbors = get_eq_epsilon_neighbors(nfa->node_map[sub_node_id+""]);
                input_next_node.insert(sub_node_eps_neighbors.begin(), sub_node_eps_neighbors.end());
            }
            // now we have eps for all 2467 so now create new node and add it to trans of current
            string new_node_id = generate_node_id(input_next_node);
            node new_node = node(new_node_id);
            is_accepted(&new_node);
            DFA_node_map[new_node_id] = &new_node;
            // just 1 node --------------------
            n->transitions[entry.first].push_back(&new_node);    
            neighbors.insert(&new_node);        
        }
        return neighbors;
    }

    set<node*> get_eq_epsilon_neighbors(node* n){
        stack<node*> epsilon_neighbors;
        set<node*> visited;
        epsilon_neighbors.push(n);

        while(!epsilon_neighbors.empty()){
            node* neighbor = epsilon_neighbors.top();
            epsilon_neighbors.pop();
            if(visited.find(neighbor) != visited.end())
                continue;
            visited.insert(neighbor);
            for(node* ep_neighbor : neighbor->epsilon_transitions){
                epsilon_neighbors.push(ep_neighbor);
            }
        }
        return visited;
    }

    string generate_node_id(set<node*> nodes){
        string state_id = "";
        sort(nodes.begin(), nodes.end(), [](node* a, node* b){return a->id < b->id;});
        set<node*>::iterator it = nodes.begin();
        while (it != nodes.end()) {
            state_id += (*it)->id;
        }
        return state_id;
    }

    void is_accepted(node* n){
        for(char c : n->id){
            node* sub_node = nfa->node_map[c+""];
            if(sub_node->acceptance){
                n->acceptance = true;
                return;
            }
        }
        n->acceptance = false;
    }
};