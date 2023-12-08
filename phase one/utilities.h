#include <cassert>
#include <iostream>
#include <set>
#include <stack>
#include "NFA.h"
#include "node.h"

class utilities
{
public:

    static NFA* build_NFA(string& str){
        Node* start = new Node(false);
        Node* cur = start;
        for(int i=0; i < str.size()-1; i++){
            Node* created_node = new Node(false);
            cur->add_next_node(str[i], created_node);
            cur = created_node;
        }
        Node* end = new Node(true);
        cur->add_next_node(str.back(), end);
        NFA* res = new NFA(start, end);
        update_node_map(res);
        return res;
    }

    static NFA* build_empty_NFA(){
        Node* start = new Node(false);
        Node* end = new Node(true);
        start->add_next_node(end);
        NFA* res = new NFA(start, end);
        update_node_map(res);
        return res;
    }

    static NFA* concat_NFA(NFA* nfa11, NFA* nfa22){
        NFA* nfa1 = nfa11->clone();
        NFA* nfa2 = nfa22->clone();
        if (nfa1->end_node == nullptr || nfa2->start_node == nullptr) {
            std::cerr << "Assertion failed: nfa1.end_node != nullptr && nfa2.start_node != nullptr\n";
            return nullptr;
        }
        if (nfa1->start_node == nullptr || nfa2->end_node == nullptr) {
            std::cerr << "Assertion failed: nfa1.start_node != nullptr && nfa2.end_node != nullptr\n";
            return nullptr;
        }

        nfa2->end_node->acceptance = false;
//        nfa1->end_node->acceptance = true;
        nfa2->end_node->add_next_node(nfa1->start_node);
        NFA* res = new NFA(nfa2->start_node, nfa1->end_node);

        update_node_map(res);
        return res;
    }


    static NFA* star_NFA(NFA* nfa1){
        NFA* nfa = nfa1->clone();
        if (nfa->start_node == nullptr || nfa->end_node == nullptr) {
            std::cerr << "Assertion failed: nfa.start_node != nullptr && nfa.end_node != nullptr\n";
            return nullptr;
        }
        Node* start = new Node(false);
        Node* end = new Node(true);
        nfa->end_node->add_next_node(end);
        nfa->end_node->add_next_node(nfa->start_node);
        start->add_next_node(end);
        start->add_next_node(nfa->start_node);
//        nfa->end_node->acceptance = false;
        NFA* res = new NFA(start, end);
        update_node_map(res);
        return res;
    }

    static NFA* plus_NFA(NFA* nfa1){
//         NFA* nfa_for_star = nfa1->clone();
//         NFA* nfa_for_concat = nfa1->clone();
        if (nfa1->start_node == nullptr || nfa1->end_node == nullptr) {
            std::cerr << "Assertion failed: nfa.start_node != nullptr && nfa.end_node != nullptr\n";
            return nullptr;
        }
//         NFA* res1 = new NFA(nfa1->start_node, nfa1->end_node);
        NFA* starred_nfa = star_NFA(nfa1);
        NFA* res = concat_NFA(nfa1, starred_nfa);
        update_node_map(res);
        return res;
    }

    static NFA* or_NFA(NFA* nfa11, NFA* nfa22) {
        NFA* nfa1 = nfa11->clone();
        NFA* nfa2 = nfa22->clone();
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

//        nfa1->end_node->acceptance = false;
//        nfa2->end_node->acceptance = false;
        NFA* res = new NFA(start, end);
        update_node_map(res);
        return res;
    }

    static NFA* or_all_NFAs(const vector<NFA*>& nfas) {
        vector<NFA*> cloned_nfas;

        for(NFA* nfa : nfas){
            cloned_nfas.push_back(nfa->clone());
        }

        Node* start = new Node(false);
        Node* end = new Node(true);

        for(NFA* nfa : cloned_nfas){
            start->add_next_node(nfa->start_node);
//            nfa->end_node->acceptance = false;
            nfa->end_node->add_next_node(end);
            for(const string& x : nfa->end_node->types)
                end->types.insert(x);
        }
        NFA* res = new NFA(start, end);
        update_node_map(res);
        return res;
    }



    static void update_node_map(NFA*& nfa){
        nfa->node_map.clear();
        set<int> visited;
        stack<Node*> not_visited;
        not_visited.push(nfa->start_node);
        while(!not_visited.empty()){
            Node* cur = not_visited.top();
            not_visited.pop();
            if(visited.find(stoi(cur->id)) == visited.end()){
                visited.insert(stoi(cur->id));
                for(const auto& it : cur->transitions){
                    for(Node* x : it.second){
                        not_visited.push(x);
                    }
                }
                for(Node* x : cur->epsilon_transitions){
                    not_visited.push(x);
                }
                nfa->node_map[cur->id] = cur;
            }
        }
    }
};