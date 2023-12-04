#include "node.h"
#include "NFA.h"
#include "utilities.h"
#include <iostream>
#include <fstream>
#include <string>


class read_input
{
private:

    utilities util;
    void get_keywords(string &line, int i){
        string key;
        while(line[i] != '}'){
            
            if(line[i] != ' '){
                key += line[i];
            }else{
                if(!key.empty()) Keywords.insert(key);
                key = "";
            }
            i++;
        }
        Keywords.insert(key);
    }

    void get_punctuations(string &line, int i){
        string key;
        while(line[i] != ']'){
            if(line[i] != ' '){
                if(line[i] != '\\'){
                    key += line[i];
                } 
            }else{
                if(!key.empty()) Punctuations.insert(key);
                key = "";
            }
            i++;
        }
        Punctuations.insert(key);
    }

    /*
    pirority : from highet to lowest -->
                    *
                    &     |
    */
   NFA minus_op(stack<string> &operators, stack<string> &operands, string name){
        char end = operands.top()[0]; operands.pop();
        char start = operands.top()[0]; operands.pop();
        node s;
        node e(true);
        for(char x = start; x < end; x++){
            s.add_next_node(x, &e);
        }
        NFA res(s, e);
        res.name = name;
        return res;
   }

   NFA star_op(stack<string> &operators, stack<string> &operands, string name){
        string nfa_name = operands.top(); operands.pop();
        if(regular_definations.find(nfa_name) != regular_definations.end()){
            return util.star_NFA(regular_definations[nfa_name]);
        }
        if(regular_expressions.find(nfa_name) != regular_expressions.end()){
            return util.star_NFA(regular_expressions[nfa_name]);
        }
        cout << "error : no NFA found for star operation" << endl;
        abort();
   }


    void get_reg_def(string line, int i, string name){
        stack<string> operators;
        stack<string> operands;
        string word;
        while(i < line.size()){
            if(line[i] == '-'){
                operators.push("-");
            }
            else if(line[i] == '*'){
                operators.push("*");
            }
            else if(line[i] == '|'){
                if(operators.top() == "-"){
                    regular_definations[name] = minus_op(operators, operands, name);
                }
                if(operators.top() == "*"){
                    regular_definations[name] = star_op(operators, operands, name);
                }
                operators.push("|");
            }
        }
        
    }

    void get_reg_exp(string line, int i, string name){
        
    }
public:
    set<string> Keywords;
    set<string> Punctuations;
    map<string, NFA> regular_definations;
    map<string, NFA> regular_expressions;
    NFA routing_nfa;

    void read_lines(string rules_file_path){
    string line;
    ifstream file(rules_file_path);
    if (file.is_open()) {
        while (getline(file, line)) {
            string name;
            for(int i=0; i < line.size(); i++){
                if(line[i] == '{'){
                    get_keywords(line, i+1);
                }
                else if(line[i] == '['){
                    get_punctuations(line, i+1);
                }
                else if(line[i] == '='){
                    get_reg_def(line, i+1, name);
                }
                else if(line[i] == ':'){
                    get_reg_exp(line, i+1, name);
                }
                else{
                    if(line[i] != ' ')
                        name += line[i];
                }
            }
        }      
    }
    file.close();
}

};


int main(int argc, char const *argv[])
{
    read_input r;
    r.read_lines("input_example.txt");
    for(string s : r.Keywords){
        cout << s << "    " ;
    }
    cout << endl;
    for(string s : r.Punctuations){
        cout << s << "    " ;
    }
    cout << endl;
    return 0;
}
