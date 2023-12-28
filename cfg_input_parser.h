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
        ofstream myFile("../parsing output.txt");
        myFile << start->name << endl;
    }

    void parse_lexicial(string token){
        ofstream myFile("../parsing output.txt", ios::app);
        if (!myFile.is_open()) {
            cout << "Error: Unable to open the file." << endl;
            exit(1);
        }
//        myFile << token << endl;
//        cout << token << " ";

        if(stack.empty()){
            // error, stack empty although we still have input
            cout << "error, stack empty although we still have input" << endl;
            exit(1);
        }

        rule* top_rule = stack.top();

        if(token == "$" && top_rule->name == "$"){
            // handle this case, input end
            stack.pop();
//            if(top_rule->name == "$"){
                cout << "\nParsed Successfully" << endl;
                myFile << "Parsed Successfully" << endl;
                return;
//            }
//            else{
//                cout << "error, stack still have rules at input end" << endl;
//                exit(1);
//            }
        }

        if(top_rule->terminal){
            if(top_rule->name == token){
                stack.pop();
                return;
            }
            else{
                // error top rule != token, pop input token (return)
                myFile << "Error: top stack rule " << top_rule->name <<  " != token " << token << ", Stack Pop " << top_rule->name << endl;
                stack.pop();
                parse_lexicial(token);
            }
        }
        else{ // top rule NT
            if(status_map[top_rule][token] == "Sync"){
//                cout << "Sync";
                myFile << "Error: parsing table[" << top_rule->name << "][" << token << "] is Sync, Discard input token " << token << endl;
                stack.pop();
                parse_lexicial(token);
                return;
            }
            if(status_map[top_rule][token] != "Production"){
                // empty entry either sync or error
                myFile << "Error: parsing table[" << top_rule->name << "][" << token << "] is Empty, Discard input token " << token << endl;
                return;
            }
            stack.pop();
            vector<rule*> vec = *parsing_map[top_rule][token].begin();
//            vec.reserve(vec.begin());
//            for(rule* sub : vec){
            myFile << top_rule->name << " -> ";
            for(int i = 0; i < vec.size(); i++){
                rule* sub = vec[i];
                myFile << sub->name << " ";
            }
            for(int i = vec.size()-1; i >= 0; i--){
                rule* sub = vec[i];
                if(sub->epsilon)
                    continue;
                stack.push(sub);
            }
            myFile << endl;
            parse_lexicial(token);
        }
    }
};
#endif //PROJECT_CFG_INPUT_PARSER_H
