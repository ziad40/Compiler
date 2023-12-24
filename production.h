//
// Created by zizoa on 12/24/2023.
//

#ifndef PROJECT_PRODUCTION_H
#define PROJECT_PRODUCTION_H

#include <string>
#include <vector>
#include <set>

using namespace std;
class rule{
public:
    string name;
    bool terminal;
    bool has_epsilon_first ;
    bool epsilon;
    bool first_found ;
    set<rule*> first;
    set<rule*> follow;
    vector<vector<rule*>> productions;
    map<rule*, vector<rule*>> first_to_expression;
    rule(string& name, bool terminal){
        this->terminal = terminal;
        this->name = name;
        this->epsilon = false;
    }
    rule(){
        this->epsilon = true;
        this->terminal = true;
        this->name = "epsilon";
    }
    void add_productions(const vector<rule*>& p){
        this->productions.push_back(p);
    }
    void get_first(){

    }

    void get_follow(){

    }
};
#endif //PROJECT_PRODUCTION_H
