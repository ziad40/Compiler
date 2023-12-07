#include "parser.h"

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
        string temp(token.begin(), token.end());
        cout <<  temp << endl;
        initialize(starting);
    }else if (!current_node_acceptance && token.size() != 0){
        string temp(token.begin(), token.end());
        cout << "error: "<< temp << endl;
        initialize(starting);
    }
}

void Parser::check_brackets(Node*& starting, char c){
    if(current_node_acceptance){
        string temp(token.begin(), token.end());
        cout <<  temp << endl;
        initialize(starting);
    }
    cout << c << endl;
}

void Parser::check_symbols(Node*& starting, char c){
    string temp(token.begin(), token.end());
    cout <<  temp << endl;
    cout << c << endl;
    initialize(starting);
}

void Parser::parse(vector<Node *> dfa, string path){
    string file = read_java_file(path);
    initialize(dfa[0]);

    for(char c : file){
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
                token.push_back(c);
                prev_node = current_node;
                prev_node_acceptance = prev_node->acceptance;
                current_node = entry.second[0];
                current_node_acceptance = current_node->acceptance;
                break;
            }
        }

        if (symbols && current_node_acceptance){
            check_symbols(dfa[0], c);
            continue;
        }
        else if (symbols && !current_node_acceptance){
            cout << "error" << endl;
        }
        if (prev_node_acceptance && !current_node_acceptance){
            string temp(token.begin(), token.end() - 1);
            cout << "prev_accepted:" << temp << endl;
            initialize(dfa[0]);
            continue;
        }
    }
}