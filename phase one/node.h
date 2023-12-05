#ifndef NODE_H
#define NODE_H

#include <utility>
#include <vector>
#include <map>
using namespace std;
#include <iostream>


class Node{
public:
    map<char, vector<Node*>> transitions;  // input -> state
    vector<Node*> epsilon_transitions;
    string id;
    static int counter;
    bool acceptance;
    Node(map<char, vector<Node*>> transitions){
        this-> transitions = transitions;
        acceptance = false;  
    }

    Node(bool acceptance){
        id = to_string(counter++);
        acceptance = acceptance;
    }

    Node(string& id){
        this->id = id;
        acceptance = false;
    }

    Node();

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