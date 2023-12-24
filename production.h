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
    
     bool operator<(const rule& other) const {
        // Compare based on the 'name' attribute
        return name < other.name;
    }

   /* void get_first(set<rule>& visited) {
        if (!first_found) {
            visited.insert(*this); // To handle cyclic dependencies
            
            if (terminal) {
                first.push_back(*this);
            } else {
                for (auto p : productions) {
                    bool allHaveEpsilon = true;
                    for (auto r : p) {
                        if (r.first_found) {
                            // Avoid infinite recursion using visited set
                            if (visited.find(r) != visited.end()) {
                                continue;
                            }
                        }
                        r.get_first(visited);
                        if (r.epsilon) {
                            for (auto f : r.first) {
                                if (f.epsilon) continue;
                                first.push_back(f);
                            }
                        } else {
                            allHaveEpsilon = false;
                            for (auto f : r.first) {
                                first.push_back(f);
                            }
                            break;
                        }
                    }
                    if (allHaveEpsilon) {
                        has_epsilon_first = true;
                    }
                }
            }

            first_found = true;
        }
    }

    void calculate_first() {
        //set<rule> visited; // To handle cyclic dependencies
        //get_first();
    }*/

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