#include "parser.h"


Parser::Parser(read_input r) {
    keywords = r.Keywords;
}
string Parser::read_java_file(string path)
{
    ifstream f(path);
    string str;
    if (f)
    {
        ostringstream ss;
        ss << f.rdbuf(); // reading data
        str = ss.str();
    }
    return str;
}

void Parser::initialize(Node*& starting){
    token.clear();
    prev_node = nullptr;
    current_node = starting;
    prev_node_acceptance = false;
    current_node_acceptance = current_node->acceptance;
}

void Parser::check_spaces(Node*& starting){
    if(current_node_acceptance){
        print_node_type(current_node);
        initialize(starting);
    }else if (!current_node_acceptance && token.size() != 0){
        string temp(token.begin(), token.end());
        cout << "error: "<< temp << endl;
        initialize(starting);
    }
}

void Parser::check_brackets(Node*& starting, char c){
    if(current_node_acceptance){
        print_node_type(current_node);
        initialize(starting);
    }
    cout << c << endl;
}

void Parser::check_symbols(Node*& starting, char c){
    print_node_type(current_node);
    cout << c << endl;
    initialize(starting);
}

void Parser::print_node_type(Node*& node){
    string temp(token.begin(), token.end());
    for (auto keyword: keywords){
        if (temp == keyword){
            cout << keyword  << endl;
            return;
        }
    }
    for (auto type : node->types){
        if (type != "" && type != "digit" && type != "digits" && type != "letter"){
            if (type == "addop"){
                if ((temp == "+" || temp == "-")){
                    cout << type  << endl;
                    return;
                }
            }
            else if (type == "mulop"){
                if (temp == "*" || temp == "/"){
                    cout << type  << endl;
                    return;
                }
            }else if (type == "assign"){
                if (temp == "="){
                    cout << type  << endl;
                    return;
                }
            }
            else{
                cout << type  << endl;
                return;
            }
        }
    }
}

void Parser::parse(vector<Node *> dfa, string path){
    string file = read_java_file(path);
    initialize(dfa[0]);
    bool not_more = true;
    for(char c : file){
        not_more = true;
        bool symbols = (c == ',' || c == ';');
        bool spaces = (c == '\t' || c == ' ' || c == '\n');
        bool brackets = (c == '(' || c == '{' || c == '}' || c == ')');
        if (spaces){
            check_spaces(dfa[0]);
            continue;
        }
        if (brackets){
            check_brackets(dfa[0], c);
            continue;
        }

        for(auto &entry : current_node->transitions){
            char t = entry.first;
            if(t == c){
                not_more = false;
                token.push_back(c);
                prev_node = current_node;
                prev_node_acceptance = prev_node->acceptance;
                current_node = entry.second[0];
                current_node_acceptance = current_node->acceptance;
                break;
            }
        }
        if(symbols && token.size() == 0){
            check_symbols(dfa[0], c);
            continue;
        }
        if (symbols && current_node_acceptance){
            check_symbols(dfa[0], c);
            continue;
        }
        else if (symbols && !current_node_acceptance){
            cout << "error" << endl;
        }
        if (not_more && current_node_acceptance){
            print_node_type(current_node);
            initialize(dfa[0]);
            continue;
        }
    }
}