//
// Created by zizoa on 12/24/2023.
//
#include "CFG parser.h"
#include "parsing_table.h"

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
    cout << "\n\n";
    for(rule* r : ob.NonTerminal){
        cout << r->name << ": " << endl;
        cout << "first: ";
        for(rule* first : r->first){
            cout << first->name << " ";
        }
        cout << "\nfollow: ";
        for(rule* follow : r->follow){
            cout << follow->name << " ";
        }
        cout << "\n\n";
    }

    pt.print_parsing_table();
    cout << "\nDone";
    cout << "\ncompiled successfully" << endl;
    return 0;
}