#include "node.cpp"
#include "NFA.cpp"
#include <cassert>
#include <iostream>
#include <set>
#include<stack>

using namespace std;

NFA concat_NFA(NFA& nfa1, NFA& nfa2){
    if (nfa1.end_node == nullptr || nfa2.start_node == nullptr) {
        std::cerr << "Assertion failed: nfa1.end_node != nullptr && nfa2.start_node != nullptr\n";
        return ;
    }

    if (nfa1.start_node == nullptr || nfa2.end_node == nullptr) {
            std::cerr << "Assertion failed: nfa1.start_node != nullptr && nfa2.end_node != nullptr\n";
            return ;
    }
    nfa1.end_node->acceptance = false;
    nfa2.end_node->acceptance = true;

    nfa1.end_node->add_next_node(nfa2.start_node);
    NFA res(*nfa1.start_node, *nfa2.end_node);
    update_IDs(res);
    return res;
}




NFA star_NFA(NFA& nfa){
    if (nfa.start_node == nullptr || nfa.end_node == nullptr) {
        std::cerr << "Assertion failed: nfa.start_node != nullptr && nfa.end_node != nullptr\n";
        return ;
    }
    Node start;
    Node end;
    nfa.end_node->acceptance = false;
    end.acceptance = true;

    nfa.end_node->add_next_node(&end);
    nfa.end_node->add_next_node(nfa.start_node);

    start.add_next_node(&end);
    start.add_next_node(nfa.start_node);

    NFA res(start, end);
    update_IDs(res);
    return res;
}




NFA or_NFA(NFA& nfa1, NFA& nfa2){
    if (nfa1.start_node == nullptr || nfa2.start_node == nullptr) {
        std::cerr << "Assertion failed: nfa1.start_node != nullptr && nfa2.start_node != nullptr\n";
        return ;
    }
    if (nfa1.end_node == nullptr || nfa2.end_node == nullptr) {
        std::cerr << "Assertion failed: nfa1.end_node != nullptr && nfa2.end_node != nullptr\n";
        return ;
    }
    Node start;
    start.add_next_node(nfa1.start_node);
    start.add_next_node(nfa2.start_node);

    Node end;
    nfa1.end_node->add_next_node(&end);
    nfa2.end_node->add_next_node(&end);

    nfa1.end_node->acceptance = false;
    nfa2.end_node->acceptance = false;
    end.acceptance = true;

    NFA res(start, end);
    update_IDs(res);

    return res;
}



void update_IDs(NFA& nfa){
    set<Node*> visited;
    stack<Node*> not_visited;
    not_visited.push(nfa.start_node);
    int counter = 0;
    while(!not_visited.empty()){
        Node* n = not_visited.top();
        not_visited.pop();

        if(visited.find(n) == visited.end()){
            n->id = counter;
            nfa.node_map[n->id] = n;
            counter++;
            visited.insert(n);
            for(auto it : n->transitions){
                for(Node* x : it.second){
                    not_visited.push(x);
                }
            }
            for(Node* x : n->epsilon_transitions){
                not_visited.push(x);
            }
        }
    }
}

