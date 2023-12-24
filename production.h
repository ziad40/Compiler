//
// Created by zizoa on 12/24/2023.
//

#ifndef PROJECT_PRODUCTION_H
#define PROJECT_PRODUCTION_H

#include <string>
#include <vector>

using namespace std;
class rule{
public:
    string name;
    bool terminal;
    vector<rule> first;
    vector<rule> follow;
    vector<vector<rule>> productions;
    rule(string name, bool terminal){
        this->terminal = terminal;
        this->name = name;
    }
    void add_productions(const vector<rule> p){
        this->productions.push_back(p);
    }
    void get_first(){

    }

    void get_follow(){

    }
};
#endif //PROJECT_PRODUCTION_H
