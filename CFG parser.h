#ifndef PROJECT_CFG_PARSER_TEST_H
#define PROJECT_CFG_PARSER_TEST_H

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

    void generate_production(string& non_terminal, string& terminal, vector<rule>& cur_prods, rule& head){
        bool flag = false;
        if (!non_terminal.empty()){
            rule r = rule(non_terminal, false);
            cur_prods.push_back(r);
            non_terminal = "";
            flag = true;
        }
        if (!terminal.empty()){
            rule r = rule(terminal, true);
            cur_prods.push_back(r);
            terminal = "";
            flag = true;
        }
//        if (flag)
//            head.add_productions(cur_prods);
    }
    int get_productions(const string& production, int i) {
        string non_terminal;
        string terminal;
        bool change;
//        vector<vector<rule>> all_prods;
        vector<rule> cur_prods;
        rule head(production, false);
        while (i < n && all_lines[i] != '#'){
            if(all_lines[i] == '|'){
                generate_production(non_terminal, terminal, cur_prods, head);
                head.add_productions(cur_prods);
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
                generate_production(non_terminal, terminal, cur_prods, head);
            }
            i++;
        }
        generate_production(non_terminal, terminal, cur_prods, head);
        head.add_productions(cur_prods);
        productions.push_back(head);
        return i-1;
    }


public:
    vector<rule> productions;

    void read_lines(const string& rules_file_path){
        get_lines(rules_file_path);
        string name_of_production;
        for (int i = 0; i < all_lines.size(); i++) {
            if(all_lines[i] == '#'){
                name_of_production = "";
            }
            else if (all_lines[i] == '='){
                int next_index = get_productions(name_of_production, i+1);
                i = next_index;
            }
            else if (all_lines[i] != ' '){
                name_of_production += all_lines[i];
            }
        }
    }

};

#endif //PROJECT_CFG_PARSER_TEST_H
