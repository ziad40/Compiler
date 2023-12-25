//
// Created by zizoa on 12/24/2023.
//
#include "CFG parser.h"
#include "parsing_table.h"
/*
int main(int argc, char* argv[]){
    string relative_path = "../cleaned.txt";
    CFG_parser ob;
    ob.read_lines(relative_path);
    vector<rule*> prod = ob.productions;
    for(rule* r : prod){
        r->get_first();
        r->get_follow(prod);
    }
    parsing_table pt = parsing_table(ob.NonTerminal, ob.Terminals);
    pt.get_parsing_table();
    pt.print_parsing_table();
    cout << "\nDone";
    cout << "\ncompiled successfully" << endl;
    return 0;
}*/