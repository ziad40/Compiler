# include "production.h"
#include <string>
#include <utility>
#include <vector>
#include <set>
#include <map>
#include <fstream>

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

        for(rule* non_terminal : this->NT) {
            for(rule* terminal : this->T){
                status_map[non_terminal][terminal] = "Error";
            }
        }
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
                status_map[non_terminal][first_terminal] = "Production";

                if(has_epsilon_first(exp)){
                    for(rule* follow_terminal : non_terminal->follow){
                        if(!parsing_map[non_terminal][first_terminal].empty()){
                            isFailed = true;
                        }
                        parsing_map[non_terminal][follow_terminal].push_back(exp);
                        status_map[non_terminal][follow_terminal] = "Production";

                    }
                }

                // add sync
                for(rule* follow_terminal : non_terminal->follow){
                    if(status_map[non_terminal][follow_terminal] != "Production")
                        status_map[non_terminal][follow_terminal] = "Sync";
                }
            }

            if(has_epsilon_rule(non_terminal)){
                vector<rule*> vec;
                string name = "eps";
                rule* eps_rule = new rule(name, true);
                eps_rule->epsilon = true;
                vec.push_back(eps_rule);
                for(rule* follow_terminal : non_terminal->follow){
                    if(!parsing_map[non_terminal][follow_terminal].empty()){
                        isFailed = true;
                    }
                    parsing_map[non_terminal][follow_terminal].push_back(vec);
                    status_map[non_terminal][follow_terminal] = "Production";
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
        string csvFilePath = "../parsing table.csv";
        ofstream outputFile(csvFilePath);
        if (!outputFile.is_open()) {
            cout << "Error, can't open file";
            return;
        }
        cout << endl;
        outputFile << "\t";
        cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t";
        for(rule* terminal : T) {
            int terminal_dist = 52;
            cout << terminal->name;
            terminal_dist -= terminal->name.size();
            for(int i = 0; i < terminal_dist; i++)
                cout << " ";
            outputFile << terminal->name << "\t";
        }
        for (auto &entry : parsing_map) {
            int initial_dist = 52;
            cout << endl;
            outputFile << endl;
            rule* non_terminal = entry.first;
            cout << non_terminal->name;
            initial_dist -= non_terminal->name.size();
            for(int i = 0; i < initial_dist; i++)
                cout << " ";
            outputFile << non_terminal->name << "\t";
            map<rule*, vector<vector<rule*>>> map = entry.second;
            for(rule* terminal : T){
                int dist = 52;
//                if(map[terminal].empty()){
                if(status_map[non_terminal][terminal] != "Production"){
                    cout << status_map[non_terminal][terminal];
                    outputFile << status_map[non_terminal][terminal] << "\t";
                    cout << "\t\t\t\t\t\t\t\t\t\t\t\t";
                    continue;
                }
                vector<vector<rule*>> vec = map[terminal];
                for(const vector<rule*>& v : vec) {
                    for (rule *r: v) {
                        cout << r->name;
                        cout << " ";
                        outputFile << r->name;
                        outputFile << " ";
                        // we can add space between each rule if wanted
                        dist -= r->name.size()+1;
                    }
                    if(vec.size() > 1) {
                        cout << "-";
                        outputFile << "-";
                        dist--;
                    }
                }
                outputFile << "\t";
                for(int i = 0; i < dist; i++) {
                    cout << " ";
                }
            }
        }
        if(isFailed){
            cout << "\n\n" << "Failed, Ambiguous Grammar";
        }
        else{
            cout << "\n\n" << "Done, Not Ambiguous Grammar";
        }
    }
};