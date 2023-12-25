//
// Created by zizoa on 12/24/2023.
//

#ifndef PROJECT_PRODUCTION_H
#define PROJECT_PRODUCTION_H

#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

class rule{
public:
    string name;
    bool terminal;
    bool has_epsilon_first = false; //if current rule has epsilon
    bool epsilon;           //if the current is epsilon --> we will try to delete it later
    bool first_found = false;       //if the first is found for the current token
    set<rule*> first;
    set<rule*> follow;
    vector<vector<rule*>> productions;
    map<rule*, vector<rule*>> first_to_expression;
    rule(string& name, bool terminal){
        this->terminal = terminal;
        this->name = name;
        this->epsilon = false;
        has_epsilon_first = false;
        first_found = false;
    }
    rule(){
        this->epsilon = true;
        this->terminal = true;
        this->name = "epsilon";
        has_epsilon_first = false;
        first_found = false;
    }
    void add_productions(const vector<rule*>& p){
        this->productions.push_back(p);
    }

    void get_first(){

        if(!(this -> first_found)){
            //terminals has themselves as first
            if(this -> terminal){
                this -> first.insert(this);
            }
            else{

                //go through all products and if they are non-terminals get their first otherwise the terminal is the first
                for(auto p: this->productions){
                    //recursively calculate the first of all needed productions
                    if(p[0]-> first.size() == 0){
                        p[0] -> get_first();
                    }

                    //non-terminal just add them
                    if(p[0]->terminal){
                        auto it = p[0]-> first.begin();
                        this->first.insert(*it);
                        this->first_to_expression[*it] = p;
                    }

                    if(p[0]->epsilon)
                        this-> has_epsilon_first = true;

                    int i = 0;
                    if(!(p[0]->terminal) && i < p.size()){
                        for(rule* r: p[0]->first){
                            this-> first.insert(r);
                            this-> first_to_expression[r]= p;
                        }
                        while(p[i]->has_epsilon_first) {
                            i++;
                            for (rule *r: p[i]->first) {
                                this->first.insert(r);
                                this->first_to_expression[r] = p;
                            }
                            if(i == p.size()-1){
                                rule temp = rule("epsilon", true);
                                temp.epsilon = true;
                                this->first.insert(&temp);
                                this-> has_epsilon_first = true;
                            }
                        }
                    }
                }
            }
            first_found = true;
        }
    }

    void get_follow(const vector<rule*>& full_productions){
        if(!(this->terminal)) {
            for (auto p: full_productions) {
                for (auto v: p->productions) {
                    for (int i = 0; i < v.size(); i++) {
                        if (v[i] == this){
                            int index = i;
                            bool follow_rule = true;
                            if(i != v.size()-1) {
                                if(v[i+1]->terminal){
                                    this->follow.insert(v[i+1]);
                                }
                                else{
                                    for(auto j : v[i+1]->first) {
                                        if (!(j->epsilon)) {
                                            this->follow.insert(j);
                                        }
                                    }
                                }
                            }else{
                                if(p->follow.size() == 0)
                                    p->get_follow(full_productions);

                                this->follow.insert(p->follow.begin(), p->follow.end());
                            }

                            for(int j = index+1; j < v.size(); j++){
                                follow_rule &= v[j]->has_epsilon_first;
                            }
                            if(follow_rule){
                                this->follow.insert(p->follow.begin(), p->follow.end());
                            }
                        }
                    }

                }
            }
        }
/*
        if(!(this-> terminal)){
            for(auto p: productions){
                for (int i = 0; i < p.size(); i++){
                    if(p[i] == this){
                        if(i != p.size()-1) {
                            //if the following is terminal then it's the following
                            if (p[i + 1]->terminal) {
                                this->follow.insert(p[i + 1]);
                            //if the following is not terminal then all then its first is following for the current token
                            } else {
                                this-> follow.insert(p[i+1]->first.begin(),p[i+1]->first.end());
                            }
                        }
                    }
                }
            }

            for(auto p: this -> productions){
                if(!(p[p.size()-1]->terminal)){
                    p[p.size()-1] ->follow.insert(this->follow.begin(), this->follow.end());
                }
            }

        }
    */}
};
#endif //PROJECT_PRODUCTION_H