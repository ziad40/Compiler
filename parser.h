//
// Created by AbdelRahman AbdelFattah on 08/12/2023.
//

#ifndef PARSER_H
#define PARSER_H

#include "lexical_analyzer.h"
#include <sstream>

using namespace std;

class Parser{
public:
    vector<char> token;
    Node* prev_node = nullptr;
    Node* current_node = nullptr;
    bool prev_node_acceptance = false;
    bool current_node_acceptance = false;
    set<string> keywords;
    string output;

    Parser(read_input r);

    static string read_java_file(string path);
    void add_to_output(string str);
    void initialize(Node*& starting);
    void check_spaces(Node*& starting);
    void check_brackets(Node*& starting, char c);
    void check_symbols(Node*& starting, char c);
    void print_node_type(Node*&);
    void write_output_file() const;
    void parse(vector<Node *> dfa, string file);
};

#endif //PARSER_H
