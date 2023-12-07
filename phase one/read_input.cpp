#include "utilities.h"
#include <fstream>
#include <string>
#include "NFA.h"
#include "node.h" 
#include <iostream>
#include <unordered_set>
#include <algorithm>

class read_input
{
public:
    set<string> Keywords;
    set<string> Punctuations;
    map<string, NFA*> regular_definations;
    map<string, NFA*> regular_expressions;
    NFA routing_nfa;

    void read_lines(const string& rules_file_path){
        string line;
        ifstream file(rules_file_path);
        if (file.is_open()) {
            while (getline(file, line)) {
                string name_of_regular;
                for(int i=0; i < line.size(); i++){
                    if(line[i] == '{'){
                        get_keywords(line, i+1);
                        break;
                    }
                    else if(line[i] == '['){
                        get_punctuations(line, i+1);
                        break;
                    }
                    else if(line[i] == '='){
                        get_reg_def(line, i+1, name_of_regular);
                        break;
                    }
                    else if(line[i] == ':'){
                        evaluate_expression(line, i+1, name_of_regular, true);
                        break;
                    }
                    else{
                        if(line[i] != ' ')
                            name_of_regular += line[i];
                    }
                }
            }
        }
        file.close();
//        finalize();
    }

private:
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
        if(!key.empty()) Keywords.insert(key);
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
        if(!key.empty()) Punctuations.insert(key);
    }

    void reset_word(string& word, stack<NFA*>& operands){
        if(regular_definations.find(word) != regular_definations.end()){
            operands.push(regular_definations[word]);
        }else{
            if(!word.empty()){
                operands.push(utilities::build_NFA(word));
            }
        }
        word = "";
    }

    static void remove_char_with_space(string &inputString, char c) {
        string targetString(1, c);  // Convert char to string
        // Find and replace c + " " with c
        size_t pos = 0;
        while ((pos = inputString.find(targetString + " ", pos)) != string::npos) {
            inputString.replace(pos, 2, targetString);
            pos += 1; // Move past the replaced character
        }
        // Find and replace " " + c with c
        pos = 0;
        while ((pos = inputString.find(" " + targetString, pos)) != string::npos) {
            inputString.replace(pos, 2, targetString);
            pos += 1; // Move past the replaced character
        }
    }

    void evaluate_expression(string& line, int start_index, string& name, bool type){
        while(line[start_index] == ' ')
            start_index++;
        remove_char_with_space(line, '|');
        remove_char_with_space(line, '(');
        remove_char_with_space(line, ')');
        string word;
        stack<NFA*> operands;
        stack<char> operators;
        for(int i = start_index; i < line.size(); i++){
            if(line[i] == '|'){
                reset_word(word, operands);
                while(!operators.empty() && (operators.top() == '*' || operators.top() == '+' || operators.top() == '&')){
                    do_one_operation(operands, operators);
                }
                operators.push(line[i]);
            }else if(line[i] == '*' || line[i] == '+'){
                reset_word(word, operands);
                operators.push(line[i]);
            }else if(line[i] == '\\'){
                i++;
                if(line[i] == 'L'){
                    if(word.empty()){
                        operands.push(utilities::build_empty_NFA());
                    }
                }else {
                    word += line[i];
                }
            }else if(line[i] == '('){
                reset_word(word, operands);
                while(!operators.empty() && (operators.top() == '*' || operators.top() == '+')){
                    do_one_operation(operands, operators);
                }
                operators.push('&');
                operators.push(line[i]);
            }else if(line[i] == ')'){
                reset_word(word, operands);
                while (!operators.empty() && operators.top() != '('){
                    do_one_operation(operands, operators);
                }
                operators.pop();
            }else if(line[i] == ' '){
                reset_word(word, operands);
                while(!operators.empty() && (operators.top() == '*' || operators.top() == '+')){
                    do_one_operation(operands, operators);
                }
                operators.push('&');
            }else{
                word += line[i];
            }
        }
        reset_word(word, operands);
        while (!operators.empty()){
            do_one_operation(operands, operators);
        }
        if(operands.size() != 1){
            std::cerr << "Assertion failed: nfa1.end_node != nullptr && nfa2.start_node != nullptr\n";
            abort();
        }
        operands.top()->name = name;
        if(type){
            regular_expressions[name] = operands.top();
        }else{
            regular_definations[name] = operands.top();
        }
    }

    static void do_one_operation(stack<NFA*>& operands, stack<char>& operators){
        char op = operators.top();
        operators.pop();
        NFA* nfa1 = operands.top();
        operands.pop();

        NFA* nfa;
        if (op == '&' || op == '|'){
            NFA* nfa2 = operands.top();
            operands.pop();
            if(op == '&'){
                nfa = utilities::concat_NFA(nfa1, nfa2);
            }
            if(op == '|'){
                nfa = utilities::or_NFA(nfa1, nfa2);
            }
        }
        else if(op == '*'){
            nfa = utilities::star_NFA(nfa1);
        }
        else if(op == '+'){
            nfa = utilities::plus_NFA(nfa1);
        }
        operands.push(nfa);
    }


    void get_reg_def(string line, int index, string name){
    size_t found = line.find('-');
    if (found != string::npos){
        vector<char> splitted;
        vector<NFA*> nfas;
        for(int i = index; i < line.size(); i++){
            if(line[i] != ' '){
                splitted.push_back(line[i]);
            }
        }
        for(int i=1; i < splitted.size(); i+=2){
            if(splitted[i] == '-'){   
                Node* s = new Node(false);
                Node* e = new Node(true);
                for(char x = splitted[i-1]; x <= splitted[i+1]; x++){
                    s->add_next_node(x, e);
                }
                NFA* nfa = new NFA(s, e);
                nfa->node_map[s->id] = s;
                nfa->node_map[e->id] = e;
                nfas.push_back(nfa);
            } else if(splitted[i] == '|'){
                continue;
            }
        }
        if(nfas.size() == 1){
            nfas[0]->name = name;
            regular_definations[name] = nfas[0];
        } else {
            NFA* result = utilities::or_NFA(nfas[0], nfas[1]);
            result->name = name;
            // Apply or_NFA operation on all NFAs in the vector
            for (int n = 2; n < nfas.size(); n++) {
                result = utilities::or_NFA(result, nfas[n]);
            }
            regular_definations[name] = result;
        }

    } else {
        evaluate_expression(line, index+1, name, false);
    }
}

    void finalize(){
        for(auto it : regular_definations){
            utilities::update_node_map(it.second);
        }
        for(auto it : regular_expressions){
            utilities::update_node_map(it.second);
        }
    }


};

int Node::counter = 1;
int main()
{
    read_input r;
    r.read_lines(R"(E:\4th-1st\Compilers\project\phase one\input_example.txt)");
    for(const string& s : r.Keywords){
        cout << s << "    " ;
    }
    cout << endl;
    for(const string& s : r.Punctuations){
        cout << s << "    " ;
    }
    cout << endl;
    
    for (const auto& it : r.regular_definations) {
        cout << "Regular Definition: " << it.first << endl;
        if (it.second != nullptr) {
            // Assuming your NFA class has a printNFA function
            it.second->printNFA();
        } else {
            cout << "NFA is nullptr" << endl;
        }
    }

    cout << endl;
    for (const auto& it : r.regular_expressions) {
        cout << "Regular Expression: " << it.first << endl;
        if (it.second != nullptr) {
            // Assuming your NFA class has a printNFA function
            it.second->printNFA();
        } else {
            cout << "NFA is nullptr" << endl;
        }
    }
    cout << endl;

    return 0;
}