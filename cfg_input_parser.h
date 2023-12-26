//
// Created by zizoa on 12/26/2023.
//

#ifndef PROJECT_CFG_INPUT_PARSER_H
#define PROJECT_CFG_INPUT_PARSER_H
#include "parsing_table.h"
#include <stack>

class cfg_input_parser{
public:
    map<rule*, map<rule*, vector<vector<rule*>>>> parsing_map;
    map<rule*, map<rule*, string>> status_map;
    std::stack<rule*> stack;

    cfg_input_parser(const map<rule*, map<rule*, vector<vector<rule*>>>>& parsing_map,
                     const map<rule*, map<rule*, string>>& status_map,
                     rule* start){
        this->parsing_map  =parsing_map;
        this->status_map = status_map;
        string name = "$";
        rule* dollar = new rule(name,true);
        stack.push(dollar);
        stack.push(start);
    }

    void parse_lexicial(string token){
        ofstream myFile("../parsing output.txt", ios::app);
        if (!myFile.is_open()) {
            cout << "Error: Unable to open the file." << endl;
            exit(1);
        }
        myFile << token << " ";

        rule* top_rule = stack.top();
    }
};
#endif //PROJECT_CFG_INPUT_PARSER_H
