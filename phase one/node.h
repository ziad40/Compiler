#ifndef NODE_H
#define NODE_H

#include <vector>
#include <map>
#include <chrono>
#include <ctime>
using namespace std;
#include <iostream>


class node
{
    
public:
    map<char, vector<node*>> transitions;
    vector<node*> epsilon_transitions;
    string id;
    static int counter;
    bool acceptance;
    node(map<char, vector<node*>> transitions) : transitions(transitions) {
        acceptance = false;
    }

    node(bool acceptance){
        id = to_string(counter++);
        acceptance = acceptance;  
    }

    void add_next_node(node* new_node){
        epsilon_transitions.push_back(new_node);
    }

    void add_next_node(char c, node* new_node){
        transitions[c].push_back(new_node);
    }

    void printNode() const {
        cout << "Node ID: " << id << ", Acceptance: " << acceptance << endl;
        // Print transitions
        cout << "Transitions:" << endl;
        for (auto entry : this->transitions) {
            char symbol = entry.first;
            const auto& next_nodes = entry.second;
            cout << "  " << symbol << " -> ";
            for (const auto& next_node : next_nodes) {
                cout << next_node-> id << " ";
            }
            cout << endl;
        }

        // Print epsilon transitions
        cout << "Epsilon Transitions:" << endl;
        for (auto epsilon_node : epsilon_transitions) {
            cout << "  " << epsilon_node->id << endl;
        }
        cout << endl;
    }
};

#endif // NODE_H
