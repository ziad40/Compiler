#include "NFA.h"
#include "node.h"
#include <set>
#include <stack>
#include <queue>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

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
                    current_node_transactions[entry.first]+=next->id+',';
                }
//                if(!current_node_transactions[entry.first].empty())
//                    current_node_transactions[entry.first].erase(current_node_transactions[entry.first].size() - 1);
            }
        }

        for(auto &entry : current_node_transactions){ // a->2467
            set<Node*> input_next_node;
            vector<string> ids_to_gen = get_sub_nodes_id(entry.second);
            for(string sub_node_id : ids_to_gen){ // 2
//                string s(1,sub_node_id);
                if(sub_node_id == "")
                    continue;
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
                handle_node_type(new_node);
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

    void handle_node_type(Node* n){
        vector<string> sub_nodes_id = get_sub_nodes_id(n->id);
        for(const string& sub_node_id : sub_nodes_id){
            Node* sub_node = nfa->node_map[sub_node_id];
            if(sub_node->acceptance){
                set<string> sub_node_types = sub_node->types;
                for(const string& sub_node_type : sub_node_types){
                    n->types.insert(sub_node_type);
                }
            }
        }
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
            cout << "\n" << "Types: ";
            for(string type : node->types){
                cout << type << "    ";
            }
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

    vector<vector<Node*>> partition_by_type(vector<Node*> states){
        map<set<string>, vector<Node*>> states_by_types;
        for(Node* state: states){
            states_by_types[state->types].push_back(state);
        }

        vector<vector<Node*>> partitioned_states;

        for(auto s: states_by_types){
            partitioned_states.push_back(s.second);
        }
        return partitioned_states;
    }

    vector<Node*> minimize() {
        // Grouping accepting and non-accepting states initially
        vector<Node*> states;
        for(auto &entry : DFA_node_map)
            states.push_back(entry.second);

        Node* startState = &DFA_start_node;


        vector<Node*> accepting;
        vector<Node*> nonaccepting;
        for (Node* state : states) {
            if (state->acceptance)
                accepting.push_back(state);
            else
                nonaccepting.push_back(state);
        }

        //collect all groups
        vector<vector<Node*>> groups = partition_by_type(accepting);
        groups.push_back(nonaccepting);


        bool changed = true;

        vector<Node*> newNodes; //vector for the new states after the minimization
        vector<bool> acceptingSates;
        map<int, map<char,int>> groupsTransition;

        //keep looping as there is new groups are created
        while (changed) {
            vector<vector<Node*>> newGroups; //hold the new groups after each step in minimization
            groupsTransition.clear();
            int index = 0;
            //go through each group to check if we can group any of its states
            for (vector<Node*> group : groups) {
                map<map<char, int>, vector<Node*>> equivalence; //hold the equivalence states with their common transitions

                //go through each state in the group
                for (Node* state : group) {
                    map<char, int> transitionMap; //hold all transitions for each state with the groups (state S --> group i with input x)

                    // Checking all transitions for the state
                    for (const auto& transition : state->transitions) {

                        //get the input char and the next state according the input
                        char input = transition.first;
                        vector<Node*> nextStates = transition.second;
                        for(Node* nextState : nextStates) {
                            for (size_t i = 0; i < groups.size(); ++i) {
                                //get the index of the group that holds the next state, if found save it with
                                if (find(groups[i].begin(), groups[i].end(), nextState) != groups[i].end()) {
                                    transitionMap[input] = i;
                                    break;
                                }
                            }
                        }
                    }
                    //save all the states of the same group with the same transition map in the same place
                    equivalence[transitionMap].push_back(state);
                }

                // Adding states to new groups based on equivalence
                for (const auto& eq : equivalence) {
                    newGroups.push_back(eq.second);
//                    acceptingSates.push_back(false);
//                    for(Node* state1: eq.second){
//                        for (Node* state2: accepting){
//                            if(state1 == state2){
//                                acceptingSates.back() =true;
//                                break;
//                            }
//                        }
//                    }
                    groupsTransition[index++] = eq.first;
                }
            }

            //check if there was any change in number of groups if so stop the minimization
            if(newGroups.size() == groups.size()){
                changed = false;
            }
            //if there is new groups was created save them as the initial groups to start minimizing from the beginning
            if (changed) {
                groups = newGroups;
            }
        }


//        for(size_t i = 0; i < groupsTransition.size(); i++){
//            string s = to_string(i);
//            Node* temp = new Node(s);
//            temp -> acceptance = acceptingSates[i];
//            newNodes.push_back(temp);
//        }

        // Outputting the minimized groups
        for (size_t i = 0; i < groups.size(); ++i) {
            string s = to_string(i);
            Node* temp = new Node(s);
//            temp -> acceptance = acceptingSates[i];
            newNodes.push_back(temp);

            if(find(groups[i].begin(), groups[i].end(), startState) != groups[i].end()){
                startState = newNodes[i];
            }
            cout << "Group " << i << ": ";
            for (Node* state : groups[i]) {
                for(Node* node_star : accepting){
                    if(state == node_star){
                        newNodes[i]->acceptance = true;
                        for(const string& type_star : node_star->types) {
                            newNodes[i]->types.insert(type_star);
                        }
                    }
                }
                cout << state->id << " ";
            }
            cout << endl;
        }

        for(auto g: groupsTransition){
            int index = g.first;
            map<char, int> transitions = g.second;

            Node* current_state = newNodes[index];
            for(auto trans: transitions){
                current_state -> transitions[trans.first].push_back(newNodes[trans.second]);
            }
        }
        DFA_start_node = *startState; // Update DFA_start_node
        return newNodes;

    }
};