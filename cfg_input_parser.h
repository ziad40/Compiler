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
    stack<string> stack;
    cfg_input_parser(const map<rule*, map<rule*, vector<vector<rule*>>>>& parsing_map,
                     const map<rule*, map<rule*, string>>& status_map){
        this->parsing_map  =parsing_map;
        this->status_map = status_map;
    }

    void parse_lexicial(string token){

    }
};
#endif //PROJECT_CFG_INPUT_PARSER_H
