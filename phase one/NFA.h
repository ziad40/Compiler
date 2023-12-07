#ifndef NFA_H
#define NFA_H

#include <map>
#include <string>
#include "unordered_map"
using namespace std;
#include "node.h"
class NFA
{

public:
    Node* start_node;
    Node* end_node;
    map<string, Node*> node_map;
    string name;

    NFA(Node* start, Node* end) : start_node(start), end_node(end) {};

    NFA() : start_node(nullptr), end_node(nullptr) {}

    NFA(Node& start, Node& end){
        start_node = &start;
        end_node = &end;
    }

    NFA* clone() {
        NFA* nfa = new NFA();
        unordered_map<Node*, Node*> mapping;
        for(const auto& it : this->node_map){
            mapping[it.second] = it.second->clone();
        }
        for(const auto& it : this->node_map) {
            for (const auto &it2: it.second->transitions) {
                for (Node *n: it2.second) {
                    mapping[it.second]->add_next_node(it2.first, mapping[n]);
                }
            }
            for (const auto &it2: it.second->epsilon_transitions) {
                mapping[it.second]->add_next_node(mapping[it2]);
            }
        }
        nfa->start_node = mapping[this->start_node];
        nfa->end_node = mapping[this->end_node];
        return nfa;
    }
    void printNFA() const {
        cout << "NFA Name: " << name << std::endl;

        if (start_node != nullptr) {
            std::cout << "Start Node: " << start_node->id << std::endl;
        } else {
            std::cout << "Start Node: nullptr" << std::endl;
        }

        if (end_node != nullptr) {
            std::cout << "End Node: " << end_node->id << std::endl;
        } else {
            std::cout << "End Node: nullptr" << std::endl;
        }

        // Print nodes in the NFA
        std::cout << "Nodes in the NFA:" << std::endl;
        for (const auto& entry : node_map) {
            string node_id = entry.first;
            auto node_ptr = entry.second;
            std::cout << "Node ID: " << node_id << std::endl;
            node_ptr->printNode();
        }
    }

};

#endif // NFA_H
