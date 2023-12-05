#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;



class node{

public:
    
    map<char, node*> transitions;
    
    string id;
    
    bool acceptance;

    node(map<char, node*> transitions){
        this -> transitions = transitions;
        this -> acceptance = false;
    }

    node(){
        this->acceptance = true;
    }
    node(string id){
        this->id = id;
    }
};


 vector<node*> minimize(vector<node*>& states, node*& startState) {
    // Grouping accepting and non-accepting states initially
    
    vector<node*> accepting;
    vector<node*> nonaccepting; 
    for (node* state : states) {
        if (state->acceptance)
            accepting.push_back(state);
        else
            nonaccepting.push_back(state);
    }
    
    //collect all groups
    vector<vector<node*>> groups;
    groups.push_back(nonaccepting);
    groups.push_back(accepting);


    bool changed = true;

    vector<node*> newNodes; //vector for the new states after the minimization
    map<int, map<char,int>> groupsTransition;

    //keep looping as there is new grousp are created
    while (changed) {
        vector<vector<node*>> newGroups; //hold the new groups after each step in minimization
        groupsTransition.clear();
        int index = 0;
        //go through each group to check if we can group any of its states
        for (vector<node*> group : groups) {
            map<map<char, int>, vector<node*>> equivalence; //hold the equivalence states with their common transitions 
    
            //go through each state in the group
            for (node* state : group) {
                map<char, int> transitionMap; //hold all transitions for each state with the groups (state S --> group i with input x)

                // Checking all transitions for the state
                for (const auto& transition : state->transitions) {
                    
                    //get the input char and the next state according the this input
                    char input = transition.first; 
                    node* nextState = transition.second;
                    
                    for (size_t i = 0; i < groups.size(); ++i) {
                        //get the index of the group that holds the next state, if found save it with 
                        if (find(groups[i].begin(), groups[i].end(), nextState) != groups[i].end()) {
                            transitionMap[input] = i; 
                            break;
                        }
                    }
                }
                //save all the states of the same group with the same transition map in the same place
                equivalence[transitionMap].push_back(state);
            }

            // Adding states to new groups based on equivalence
            for (const auto& eq : equivalence) {
                newGroups.push_back(eq.second);
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


    for(size_t i = 0; i < groupsTransition.size(); i++){
        node* temp = new node(to_string(i));
        newNodes.push_back(temp);
    }

    // Outputting the minimized groups
    for (size_t i = 0; i < groups.size(); ++i) {
        if(find(groups[i].begin(), groups[i].end(), startState) != groups[i].end()){
            cout << "found at i= " << i << endl;
            cout << "new id should be: " << newNodes[i] -> id << endl;
            startState = newNodes[i];    
        }
        
        cout << "Group " << i << ": ";
        for (node* state : groups[i]) {
            cout << state->id << " ";
        }
        cout << endl;
    }


    

    for(auto g: groupsTransition){
        int index = g.first;
        map<char, int> transitions = g.second;

        node* current_state = newNodes[index];
        for(auto trans: transitions){
            current_state -> transitions[trans.first] = newNodes[trans.second];
        }
    }

    return newNodes;

}


int main()
{

    node* A = new node("0137");
    node* B = new node("247");
    node* C = new node("58");
    node* D = new node("7");
    node* E = new node("68");
    node* F = new node("8");

    B -> acceptance = true;
    C -> acceptance = true;
    E -> acceptance = true;
    F -> acceptance = true;

    A -> transitions['a'] = B;
    A -> transitions['b'] = F;


    B -> transitions['a'] = D;
    B -> transitions['b'] = C;


    C -> transitions['b'] = E;

    D -> transitions['a'] = D;
    D -> transitions['b'] = F;

    E -> transitions['b'] = F;

    F -> transitions['b'] = F;

    node temp = node();
    vector<node*> states;
    states.push_back(A);
    states.push_back(B);
    states.push_back(C);
    states.push_back(D);
    states.push_back(E);
    states.push_back(F);


/*
    node* A = new node("A");
    node* B = new node("B");
    B->acceptance = false;
    node* C = new node("C");
    C->acceptance = false;
    node* D = new node("D");
    D->acceptance = false;
    node* E = new node("E");
    E -> acceptance = true;

    A -> transitions['a'] = A;
    A -> transitions['b'] = B;
    B -> transitions['a'] = D;
    B -> transitions['b'] = D;
    C -> transitions['a'] = A;
    C -> transitions['b'] = B;
    D -> transitions['a'] = E;
    D -> transitions['b'] = B;


//    cout << A ->transitions.first << endl;
    node temp = node();
    vector<node*> states;
    states.push_back(A);
    states.push_back(B);
    states.push_back(C);
    states.push_back(D);
    states.push_back(E);
*/
    node* startState = A;
    
    vector<node*> minimized_states = minimize(states,startState);
    for(node* n : minimized_states){
        cout << "state of id: " << n-> id;
        cout<< " with Transitions: " << endl;
        for(auto m: n->transitions){
            cout<<"input:  " << m.first << " --> State: " << m.second->id <<endl;  
        }
    }

    cout << "start State: " << startState -> id << endl;
    //cout << "Hello world:-  " << temp.acceptance << endl;
    return 0;
}
