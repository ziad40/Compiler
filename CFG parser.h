#ifndef PROJECT_CFG_PARSER_H
#define PROJECT_CFG_PARSER_H

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include "production.h"
using namespace std;
class CFG_parser {
private:
    string all_lines;
    size_t n;
    map<string, rule*> table;

    void get_lines(const string& rules_file_path){
        string line;
        ifstream file(rules_file_path);
        if (file.is_open()) {
            while (getline(file, line)) {
                all_lines += line;
            }
        }
        file.close();
        n = all_lines.size();
    }

    void generate_production(string& non_terminal, string& terminal, vector<rule*>& cur_prods){
        if (!non_terminal.empty()){
            if(non_terminal == "\\L"){
                if(table.find("epsilon") == table.end())
                    table["epsilon"] = new rule();
                cur_prods.push_back(table["epsilon"]);
            }else{
                if(table.find(non_terminal) == table.end())
                    table[non_terminal] = new rule(non_terminal, false);
                cur_prods.push_back(table[non_terminal]);
            }
            non_terminal = "";
        }
        if (!terminal.empty()){
            if(table.find(terminal) == table.end())
                table[terminal] = new rule(terminal, true);
            cur_prods.push_back(table[terminal]);
            terminal = "";
        }
    }
    int forward_path(string& production, int i) {
        string non_terminal;
        string terminal;
        vector<rule*> cur_prods;
        if(table.find(production) == table.end()){
            table[production] = new rule(production, false);
        }
        while (i < n && all_lines[i] != '#'){
            if(all_lines[i] == '|'){
                generate_production(non_terminal, terminal, cur_prods);
                table[production]->add_productions(cur_prods);
                cur_prods.clear();
            }
            else if(all_lines[i] == '\''){
                i++;
                while(i < n && all_lines[i] != '\''){
                    terminal += all_lines[i];
                    i++;
                }
            }
            else if(all_lines[i] != ' '){
                non_terminal += all_lines[i];
            }
            else if(all_lines[i] == ' '){
                generate_production(non_terminal, terminal, cur_prods);
            }
            i++;
        }
        generate_production(non_terminal, terminal, cur_prods);
        table[production]->add_productions(cur_prods);
        productions.push_back(table[production]);
        return i-1;
    }
public:
    vector<rule*> productions;
    void read_lines(const string& rules_file_path){
        get_lines(rules_file_path);
        string name_of_production;
        for (int i = 0; i < all_lines.size(); i++) {
            if(all_lines[i] == '#'){
                name_of_production = "";
            }
            else if (all_lines[i] == '='){
                int next_index = forward_path(name_of_production, i+1);
                i = next_index;
            }
            else if (all_lines[i] != ' '){
                name_of_production += all_lines[i];
            }
        }
        string s = "$";
        productions[0]->follow.insert(new rule(s, true));
    }
};
#endif //PROJECT_CFG_PARSER_H