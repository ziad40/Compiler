//#include "utilities.h"
//#include <fstream>
//#include <string>
//#include "NFA.h"
//#include "node.h"
//#include <iostream>
//
//int Node::counter = 1;
//
//class read_input
//{
//private:
//    utilities util;
//    void get_keywords(string &line, int i){
//        string key;
//        while(line[i] != '}'){
//
//            if(line[i] != ' '){
//                key += line[i];
//            }else{
//                if(!key.empty()) Keywords.insert(key);
//                key = "";
//            }
//            i++;
//        }
//        Keywords.insert(key);
//    }
//
//    void get_punctuations(string &line, int i){
//        string key;
//        while(line[i] != ']'){
//            if(line[i] != ' '){
//                if(line[i] != '\\'){
//                    key += line[i];
//                }
//            }else{
//                if(!key.empty()) Punctuations.insert(key);
//                key = "";
//            }
//            i++;
//        }
//        Punctuations.insert(key);
//    }
//
//    void evaluate_expression(string& line, int i, string& name, bool type){
//
//    }
//
//    void do_one_operation(stack<string>& operands, stack<char>& operators){
//
//    }
//
//    void get_reg_def(string line, int index, string name){
//    // cout << line << "  " << index << "   " << name << endl;
//
//    size_t found = line.find('-');
//    if (found != string::npos){
//        vector<char> splitted;
//        vector<NFA*> nfas;
//        for(int i = index; i < line.size(); i++){
//            if(line[i] != ' '){
//                splitted.push_back(line[i]);
//            }
//        }
//        for(int i=1; i < splitted.size(); i+=2){
//            if(splitted[i] == '-'){
//                Node* s = new Node(false);
//                Node* e = new Node(true);
//                for(char x = splitted[i-1]; x <= splitted[i+1]; x++){
//                    s->add_next_node(x, e);
//                    // s->printNode();
//                }
//                nfas.push_back(new NFA(s, e));
//            } else if(splitted[i] == '|'){
//                continue;
//            }
//        }
//        if(nfas.size() == 1){
//            nfas[0]->name = name;
//            regular_definations[name] = nfas[0];
//        } else {
//            NFA* result = util.or_NFA(nfas[0], nfas[1]);
//            // Apply or_NFA operation on all NFAs in the vector
//            for (int n = 2; n < nfas.size(); n++) {
//                result = util.or_NFA(result, nfas[n]);
//            }
//            result->name = name;
//            regular_definations[name] = result;
//        }
//
//        // Free the dynamically allocated NFA instances
//        // for (NFA* nfa : nfas) {
//        //     delete nfa;
//        // }
//    } else {
//        evaluate_expression(line, index+1, name, false);
//    }
//}
//
//
//
//public:
//    set<string> Keywords;
//    set<string> Punctuations;
//    map<string, NFA*> regular_definations;
//    map<string, NFA*> regular_expressions;
//    NFA routing_nfa;
//
//    void read_lines(string rules_file_path){
//    string line;
//    ifstream file(rules_file_path);
//    if (file.is_open()) {
//        while (getline(file, line)) {
//            string name_of_regular = "";
//            for(int i=0; i < line.size(); i++){
//                if(line[i] == '{'){
//                    get_keywords(line, i+1);
//                    break;
//                }
//                else if(line[i] == '['){
//                    get_punctuations(line, i+1);
//                    break;
//                }
//                else if(line[i] == '='){
//                    get_reg_def(line, i+1, name_of_regular);
//                    break;
//                }
//                else if(line[i] == ':'){
//                    evaluate_expression(line, i+1, name_of_regular, true);
//                    break;
//                }
//                else{
//                    if(line[i] != ' ')
//                        name_of_regular += line[i];
//                }
//            }
//        }
//    }
//    file.close();
//}
//
//};
//
//
//int main()
//{
//    read_input r;
//    r.read_lines(R"(/media/elsharawy/Data/CSED/level 4 term 1/Compilers/compilers project/Compiler/phase one/input_example.txt)");
//    for(string s : r.Keywords){
//        cout << s << "    " ;
//    }
//    cout << endl;
//    for(string s : r.Punctuations){
//        cout << s << "    " ;
//    }
//    cout << endl;
//
//    for (auto it : r.regular_definations) {
//        cout << "Regular Definition: " << it.first << endl;
//        if (it.second != nullptr) {
//            // Assuming your NFA class has a printNFA function
//            it.second->printNFA();
//        } else {
//            cout << "NFA is nullptr" << endl;
//        }
//    }
//    cout << endl;
//
//    return 0;
//};