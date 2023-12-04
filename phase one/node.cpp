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
    Node(map<char, vector<Node*>> transitions){
        this-> transitions = transitions;
        acceptance = false;  
    }

    Node(){
        acceptance = false;  
    }

    Node(string ID){
        id = ID;
        acceptance = false;  
    }

    void add_next_node(Node* new_node){
        epsilon_transitions.push_back(new_node);
    }

    void add_next_node(char c, Node* new_node){
        transitions[c].push_back(new_node);
    }
};

#endif

