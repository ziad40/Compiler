//
// Created by zizoa on 12/26/2023.
//

#ifndef PROJECT_CFG_INPUT_PARSER_H
#define PROJECT_CFG_INPUT_PARSER_H
#include "parsing_table.h"
#include <stack>

class cfg_input_parser{
public:
    map<rule*, map<string, vector<vector<rule*>>>> parsing_map;
    map<rule*, map<string, string>> status_map;
    std::stack<rule*> stack;

    cfg_input_parser(const map<rule*, map<string , vector<vector<rule*>>>>& parsing_map,
                     const map<rule*, map<string , string>>& status_map,
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


        if(stack.empty()){
            // error, stack empty although we still have input
            cout << "error, stack empty although we still have input" << endl;
            exit(1);
        }

        rule* top_rule = stack.top();

        if(token == "$"){
            // handle this case, input end
            stack.pop();
            if(top_rule->name == "$"){
                cout << "Parsed Successfully" << endl;
            }
            else{
                cout << "error, stack still have rules at input end" << endl;
                exit(1);
            }
        }

        if(top_rule->terminal){
            if(top_rule->name == token){
                stack.pop();
                return;
            }
            else{
                // error top rule != token
                cout << "error top rule != token" << endl;
            }
        }
        else{ // top rule NT
            if(status_map[top_rule][token] != "Production"){
                // empty entry either sync or error
                cout << "not found";
                exit(1);
            }
            stack.pop();
            for(rule* sub : *parsing_map[top_rule][token].begin()){
                stack.push(sub);
            }
        }
    }
};
#endif //PROJECT_CFG_INPUT_PARSER_H
