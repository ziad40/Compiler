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
    bool has_epsilon_first;
    bool epsilon;
    bool first_found;
    set<rule*> first;
    set<rule*> follow;
    vector<vector<rule*>> productions;

    rule(string name, bool terminal){
        this->terminal = terminal;
        this->name = name;
    }
    void add_productions(const vector<rule*> p){
        this->productions.push_back(p);
    }

    void get_first(){

        if(!(this -> first_found)){
            //terminals has them selves as first 
            if(this -> terminal){
                this -> first.insert(this);
            }
            else{
                //go through all productes and if they are non terminals get their first otherwise the terminal is the first
                for(auto p: this->productions){
                    //recursivly calculate the first of all needed productions 
                    if(p[0]-> first.size() == 0){
                        p[0] -> get_first();
                    }

                    //non-terminal 
                    if(p[0]->terminal){
                        set<rule*>::iterator it = p[0]-> first.begin();
                        this->first.insert(*it);
                    }

                    if(p[0]->epsilon)
                        this-> has_epsilon_first = true;
                        int i = 0;
                    if(!(p[0]->terminal) && i < p.size()){
                        for(rule* r: p[0]->first){
                            this-> first.insert(r);
                        }
                        while(p[i]->has_epsilon_first)
                        i++;
                        for(rule* r: p[i]->first)
                            this -> first.insert(r);
                    }
                }
            }
            first_found = true;
        }
    }



   


    void get_follow(){

    }
};
#endif //PROJECT_PRODUCTION_H