#include <cassert>
#include <iostream>
#include <set>
#include <stack>
#include "NFA.h"
#include "node.h"

class utilities
{
public:
    utilities (){}
    // NFA* concat_NFA(NFA* nfa1, NFA* nfa2){
    //     if (nfa1->end_node == nullptr || nfa2->start_node == nullptr) {
    //         std::cerr << "Assertion failed: nfa1.end_node != nullptr && nfa2.start_node != nullptr\n";
    //         return nullptr;
    //     }

    //     if (nfa1->start_node == nullptr || nfa2->end_node == nullptr) {
    //             std::cerr << "Assertion failed: nfa1.start_node != nullptr && nfa2.end_node != nullptr\n";
    //             return nullptr;
    //     }
    //     nfa1.end_node->acceptance = false;
    //     nfa2.end_node->acceptance = true;

    //     nfa1.end_node->add_next_node(nfa2.start_node);
    //     NFA res(nfa1.start_node, nfa2.end_node);
    //     // update_IDs(res);
    //     return &res;
    // }




    // NFA* star_NFA(NFA& nfa){
    //     if (nfa.start_node == nullptr || nfa.end_node == nullptr) {
    //         std::cerr << "Assertion failed: nfa.start_node != nullptr && nfa.end_node != nullptr\n";
    //         return nullptr;
    //     }
    //     node start;
    //     node end(true);
    //     nfa.end_node->add_next_node(&end);
    //     nfa.end_node->add_next_node(nfa.start_node);
    //     start.add_next_node(&end);
    //     start.add_next_node(nfa.start_node);
    //     NFA res(&start, &end);
    //     // update_IDs(res);
    //     return &res;
    // }

    NFA* or_NFA(NFA* nfa1, NFA* nfa2) {
        if (nfa1->start_node == nullptr || nfa2->start_node == nullptr) {
            std::cerr << "Assertion failed: nfa1.start_node != nullptr && nfa2.start_node != nullptr\n";
            return nullptr;
        }

        if (nfa1->end_node == nullptr || nfa2->end_node == nullptr) {
            std::cerr << "Assertion failed: nfa1.end_node != nullptr && nfa2.end_node != nullptr\n";
            return nullptr;
        }

        Node* start = new Node(false);
        start->add_next_node(nfa1->start_node);
        start->add_next_node(nfa2->start_node);

        Node* end = new Node(true);
        nfa1->end_node->add_next_node(end);
        nfa2->end_node->add_next_node(end);

        nfa1->end_node->acceptance = false;
        nfa2->end_node->acceptance = false;
        end->acceptance = true;

        NFA* res = new NFA(start, end);
        // update_IDs(res);

        return res;
    }



    // void update_IDs(NFA& nfa){
    //     set<node*> visited;
    //     stack<node*> not_visited;
    //     not_visited.push(nfa.start_node);
    //     int counter = 0;
    //     while(!not_visited.empty()){
    //         node* n = not_visited.top();
    //         not_visited.pop();

    //         if(visited.find(n) == visited.end()){
    //             n->id = counter;
    //             nfa.node_map[n->id] = n;
    //             counter++;
    //             visited.insert(n);
    //             for(auto it : n->transitions){
    //                 for(node* x : it.second){
    //                     not_visited.push(x);
    //                 }
    //             }
    //             for(node* x : n->epsilon_transitions){
    //                 not_visited.push(x);
    //             }
    //         }
    //     }
    // }




};


