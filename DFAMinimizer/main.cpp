#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;



class node{

public:
    
    map<char, node*> transitions;
    map<char, int> groupTransitions;
    
    string id;
    
    bool acceptance;
    bool isStart;

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
    void setStart(){
        this-> isStart = true;
    }

};


void minimize(vector<node*>& states) {
    // Grouping accepting and non-accepting states initially
    vector<node*> accepting;
    vector<node*> nonaccepting;
    
    for (node* state : states) {
        if (state->acceptance)
            accepting.push_back(state);
        else
            nonaccepting.push_back(state);
    }

    //cout << "accepting size: " << accepting.size()<< endl;
    //cout << "non accepting size: " << nonaccepting.size()<<endl;
    
    vector<vector<node*>> groups;
    groups.push_back(nonaccepting);
    groups.push_back(accepting);

    bool changed = true;

    vector<node*> newNodes;

    while (changed) {
        vector<vector<node*>> newGroups;

        //go through each group to check its states
        for (vector<node*> group : groups) {
            map<map<char, int>, vector<node*>> equivalence; //will be <string, int> instead of string, string
           // cout << "group size: " << group.size() << endl;

            //go through each state in each group
            for (node* state : group) {
                map<char, int> transitionMap;//will be <string, int> instead of string, string
                //cout << "the state is : " << state -> id << endl;

                // Checking all transitions for each state
                for (const auto& transition : state->transitions) {
                    
                    char input = transition.first;
                    //cout << " the input is: " << input << endl;
                    
                    node* nextState = transition.second;
                    //cout << "next state is: " << nextState -> id << endl;
                    // Finding the group to which the next state belongs
                    
                    for (size_t i = 0; i < groups.size(); ++i) {
                        /*auto query = find(groups[i].begin(), groups[i].end(), nextState);
                        if (query != groups[i].end()) {
                            std::cout << "Element " << nextState-> id << " found at index: " << std::distance(groups[i].begin(), query) << std::endl;
                        } else {
                            std::cout << "Element " << nextState -> id << " not found." << std::endl;
                        }

                        bool query_result = query != groups[i].end();
                        cout << "query result: " << query_result << endl;*/

                        if (find(groups[i].begin(), groups[i].end(), nextState) != groups[i].end()) {
                            transitionMap[input] = i; 
                            break;
                        }
                    }
                }
                equivalence[transitionMap].push_back(state);
            }

            // Adding states to new groups based on equivalence
            for (const auto& eq : equivalence) {
                /*for(node* sec: eq.second){
                    cout << sec -> id << " ";
                }
                cout << "eq size = " << eq.second.size() << endl;
                cout << endl;
*/
                newGroups.push_back(eq.second);
                //cout << "groups_size: " << groups.size()<< " new Groups size: " << newGroups.size() << endl;
            }
        }


        if(newGroups.size() == groups.size()){
            changed = false;


            for(size_t i; i < newGroups.size(); i++){
                node* temp = new node(to_string(i));
                newNodes.push_back(temp);
            }

          /*  for(size_t i; i < equ.size(); i++){
                for(auto transition: newGroups[i].first){
                    node* temp = newNodes[i];
                    temp->transitions[transition.first[0]] = newNodes[transition.second];
                }
            }*/
        }
        //cout << "size of new Groups is: " << newGroups.size() << endl;
        //cout << "changed: " << changed << endl;
        if (changed) {
            groups = newGroups;
        }
    }

    //cout << "\n\nwe finished" << endl;
    //cout << "groups size " << groups.size() << endl;
    // Outputting the minimized groups
    for (size_t i = 0; i < groups.size(); ++i) {
        cout << "Group " << i << ": ";
        for (node* state : groups[i]) {
            cout << state->id << " ";
        }
        cout << endl;
    }

    for(node* node:newNodes){
        cout<< "node: " << node -> id << endl;
        cout << "transition for this node: " << endl;
        for (auto transition: node -> transitions){
            cout << "input: " << transition.first << " --> " << transition.second-> id << endl;
        }
    }

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
    minimize(states);

    //cout << "Hello world:-  " << temp.acceptance << endl;
    return 0;
}
