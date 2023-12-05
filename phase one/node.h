#include <vector>
#include <map>
#include<iostream>

using namespace std;

#ifndef Node_H
#define Node_H

class Node{
public:
    map<char, vector<Node*>> transitions;  // input -> state
    vector<Node*> epsilon_transitions;
    string id;
    bool acceptance;
    static int counter;

    Node(map<char, vector<Node*>> transitions){
        this-> transitions = transitions;
        acceptance = false;
    }

    Node(){
        acceptance = false;
    }

    explicit Node(string ID){
        id = ID;
        acceptance = false;
    }

    Node(bool is_accepted){
        id = to_string(counter++);
        acceptance = is_accepted;
    }

    void add_next_node(Node* new_node){
        epsilon_transitions.push_back(new_node);
    }

    void add_next_node(char c, Node* new_node){
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

#endif

