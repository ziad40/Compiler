#include "NFA.h"
#include "node.h"
#include <set>
#include <stack>
#include <queue>

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
            for (Node* neighbor : neighbors) {
                queue.push(neighbor);
            }
        }
        return &DFA_start_node;
    }

    set<Node*> handle_node_transactions(Node* n){ // 15679
        set<Node*> neighbors;
        map<char, string> current_node_transactions;
        vector<string> ids = get_sub_nodes_id(n->id);
        for(const string& s : ids){ // 1
            Node* sub_node = nfa->node_map[s];
            for (auto &entry : sub_node->transitions) { // all 1 inputs
                for(Node* next : entry.second){
                    //////////////////////////
                    current_node_transactions[entry.first]+=next->id+',';
                }
                if(!current_node_transactions[entry.first].empty())
                    current_node_transactions[entry.first].erase(current_node_transactions[entry.first].size() - 1);
            }
        }

        for(auto &entry : current_node_transactions){ // a->2467
            set<Node*> input_next_node;
            //////////////////////////////
            vector<string> ids_to_gen = get_sub_nodes_id(entry.second);
            for(string sub_node_id : ids_to_gen){ // 2
//                string s(1,sub_node_id);
                set<Node*> sub_node_eps_neighbors = get_eq_epsilon_neighbors(nfa->node_map[sub_node_id]);
                input_next_node.insert(sub_node_eps_neighbors.begin(), sub_node_eps_neighbors.end());
            }
            // now we have eps for all 2467 so now create new node and add it to trans of current
            string new_node_id = generate_node_id(input_next_node);
            if(DFA_node_map.find(new_node_id) != DFA_node_map.end()){
                // element found
                Node* node = DFA_node_map[new_node_id];
                n->transitions[entry.first].push_back(node);
            }
            else{
                Node* new_node = new Node(new_node_id);
                is_accepted(new_node);
                DFA_node_map[new_node_id] = new_node;
                // just 1 node --------------------
                n->transitions[entry.first].push_back(new_node);
                neighbors.insert(new_node);
            }
        }
        return neighbors;
    }

    static set<Node*> get_eq_epsilon_neighbors(Node* n){
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

    static string generate_node_id(const set<Node*>& nodes){
        string state_id;
        auto it = nodes.begin();
        while (it != nodes.end()) {
            state_id += (*it)->id + ',';
            it++;
        }
        if(!state_id.empty())
            state_id.erase(state_id.size() - 1);
        return state_id;
    }

    void is_accepted(Node* n) const{
        vector<string> ids = get_sub_nodes_id(n->id);
        for(const string& s : ids){
            Node* sub_node = nfa->node_map[s];
            if(sub_node->acceptance){
                n->acceptance = true;
                return;
            }
        }
        n->acceptance = false;
    }

    static vector<string> get_sub_nodes_id(const string& id) {
        std::vector<std::string> result;
        size_t start = 0;
        size_t end = id.find(',');

        // Check if the delimiterentry.second is not found
        if (end == std::string::npos) {
            result.push_back(id);
            return result;
        }

        while (end != std::string::npos) {
            result.push_back(id.substr(start, end - start));
            start = end + 1;
            end = id.find(',', start);
        }

        // Add the last substring
        result.push_back(id.substr(start));

        return result;
    }

    void print_dfa(){
        queue<Node*> queue;
        set<string> visited;
        queue.push(&DFA_start_node);
        while(!queue.empty()){
            Node* node = queue.front();
            queue.pop();
            if(visited.find(node->id) != visited.end())
                continue;
            visited.insert(node->id);
            printf("\nState %s   %d",node->id.c_str(),node->acceptance);
            printf("\nTransactions\n");
            for(auto &entry : node->transitions){
                printf("\t%c -> ",entry.first);
                for(Node* n : entry.second){
                    printf("%s ",n->id.c_str());
                    queue.push(n);
                }
            }
            printf("\tepsilon -> ");
            for(Node* n : node->epsilon_transitions){
                printf("%s ",n->id.c_str());
                queue.push(n);
            }
            printf("\n");
        }
    }
};