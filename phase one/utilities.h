#include "node.h"
#include "NFA.h"
#include <cassert>
#include <iostream>

NFA concat_NFA(NFA& nfa1, NFA& nfa2){
    if (nfa1.end_node == nullptr || nfa2.start_node == nullptr) {
        std::cerr << "Assertion failed: nfa1.end_node != nullptr && nfa2.start_node != nullptr\n";
    }

    nfa1.end_node->add_next_node(*nfa2.start_node);

    if (nfa1.start_node == nullptr || nfa2.end_node == nullptr) {
        std::cerr << "Assertion failed: nfa1.start_node != nullptr && nfa2.end_node != nullptr\n";
    }
    
    return NFA (*nfa1.start_node, *nfa2.end_node);
}


NFA star_NFA(NFA& nfa){
    if (nfa.start_node == nullptr || nfa.end_node == nullptr) {
        std::cerr << "Assertion failed: nfa.start_node != nullptr && nfa.end_node != nullptr\n";
    }
    node start;
    node end;
    nfa.end_node->add_next_node(end);
    nfa.end_node->add_next_node(*nfa.start_node);
    start.add_next_node(end);
    start.add_next_node(*nfa.start_node);
    return NFA(start, end);
}

NFA or_NFA(NFA& nfa1, NFA& nfa2){
    if (nfa1.start_node == nullptr || nfa2.start_node == nullptr) {
        std::cerr << "Assertion failed: nfa1.start_node != nullptr && nfa2.start_node != nullptr\n";
    }
    if (nfa1.end_node == nullptr || nfa2.end_node == nullptr) {
        std::cerr << "Assertion failed: nfa1.end_node != nullptr && nfa2.end_node != nullptr\n";
    }
    node start;
    start.add_next_node(*nfa1.start_node);
    start.add_next_node(*nfa2.start_node);
    node end;
    nfa1.end_node->add_next_node(end);
    nfa2.end_node->add_next_node(end);
    return NFA (start, end);
}