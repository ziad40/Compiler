# include "production.h"
#include <string>
#include <utility>
#include <vector>
#include <set>
#include <map>

using namespace std;

class parsing_table{
public:
    set<rule*> NT;
    set<rule*> T;
    map<rule*, map<rule*, vector<vector<rule*>>>> parsing_map;
    map<rule*, map<rule*, string>> status_map;

    bool isFailed;

    parsing_table(set<rule*> NT, set<rule*> T){
        this->NT = std::move(NT);
        this->T = std::move(T);
        isFailed = false;
    }

    void get_parsing_table(){
        for(rule* non_terminal : NT){
            // S -> iCtSE | a
            for(vector<rule*> current_rule : non_terminal->productions){
                // S -> iCtSE
                cout << non_terminal->name << " -> ";
                for(rule* r : current_rule){
                    cout << r->name;
                }
                cout << endl;
            }
        }

        for(rule* non_terminal : NT){
            // S -> iCtSE | a
            for(rule* first_terminal : non_terminal->first){
                // for each first of S: i,a
                if(first_terminal->epsilon){
                    // there is no epsilon terminal in map
                    continue;
                }
                vector<rule*> exp = non_terminal->first_to_expression[first_terminal];
                // iCtSE
                if(!parsing_map[non_terminal][first_terminal].empty()) {
                    isFailed = true;
                }
                parsing_map[non_terminal][first_terminal].push_back(exp);

                if(has_epsilon_first(exp)){
                    for(rule* follow_terminal : non_terminal->follow){
                        if(!parsing_map[non_terminal][first_terminal].empty()){
                            isFailed = true;
                        }
                        parsing_map[non_terminal][follow_terminal].push_back(exp);
                    }
                }
            }

            if(has_epsilon_rule(non_terminal)){
                vector<rule*> vec;
                rule* eps_rule = new rule("eps", true);
                eps_rule->epsilon = true;
                vec.push_back(eps_rule);
                for(rule* follow_terminal : non_terminal->follow){
                    if(!parsing_map[non_terminal][follow_terminal].empty()){
                        isFailed = true;
                    }
                    parsing_map[non_terminal][follow_terminal].push_back(vec);
                }
            }
        }

    }

    static bool has_epsilon_first(const vector<rule*>& exp){
        for(rule* r : exp){
            if(r->terminal || !r->has_epsilon_first)
                return false;
        }
        return true;
    }

    static bool has_epsilon_rule(rule* non_terminal){
        for(vector<rule*> vec : non_terminal->productions){
            if(vec.size() == 1 && vec[0]->epsilon)
                return true;
        }
        return false;
    }

    void print_parsing_table(){
        cout << endl;
        cout << "\t\t\t";
        for(rule* terminal : T)
            cout << terminal->name << "\t\t\t";
        for (auto &entry : parsing_map) {
            cout << endl;
            rule* non_terminal = entry.first;
            cout << non_terminal->name << "\t\t\t";
            map<rule*, vector<vector<rule*>>> map = entry.second;
            for(rule* terminal : T){
                int dist = 12;
                if(map[terminal].empty()){
                    cout << "Error";
                    cout << "\t\t";
                    continue;
                }
                vector<vector<rule*>> vec = map[terminal];
                for(const vector<rule*>& v : vec) {
                    for (rule *r: v) {
                        cout << r->name;
                        dist -= r->name.size();
                    }
                    if(vec.size() > 1) {
                        cout << ",";
                        dist--;
                    }
                }
                for(int i = 0; i < dist; i++)
                    cout << " ";
            }
        }
        if(isFailed){
            cout << "\n" << "Failed, Ambiguous Grammar";
        }
        else{
            cout << "\n" << "Done, Not Ambiguous Grammar";
        }
    }
};