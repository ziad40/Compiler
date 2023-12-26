#include "lexical_analyzer.h"
#include "parser.h"
#include "cfg_input_parser.h"
#include "CFG parser.cpp"
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

void Parser::check_spaces(Node*& starting, cfg_input_parser cfgInputParser){
    if(current_node_acceptance){
        print_node_type(current_node,cfgInputParser);
        initialize(starting);
    }else if (!current_node_acceptance && token.size() != 0){
        string temp(token.begin(), token.end());
        output.append("error: ");
        output.append(temp);  // temp to phase 2 -------------------------------
        cfgInputParser.parse_lexicial(temp);
        output.append("\n");
        initialize(starting);
    }
}

void Parser::check_brackets(Node*& starting, char c, cfg_input_parser cfgInputParser){
    if(current_node_acceptance){
        print_node_type(current_node,cfgInputParser);
        initialize(starting);
    }
    output+= c;      // c to phase 2 -------------------------------
    string s = string(1,c);
    cfgInputParser.parse_lexicial(s);
    output.append("\n");
}

void Parser::check_symbols(Node*& starting, char c, cfg_input_parser cfgInputParser){
    print_node_type(current_node,cfgInputParser);
    output+= c;         // c to phase 2 -------------------------------
    string s = string(1,c);
    cfgInputParser.parse_lexicial(s);
    output.append("\n");
    initialize(starting);
}

void Parser::print_node_type(Node*& node, cfg_input_parser cfgInputParser){
    string temp(token.begin(), token.end());
    for (auto keyword: keywords){
        if (temp == keyword){
            output.append(keyword);   // keyword to phase 2 -------------------------------
            cfgInputParser.parse_lexicial(keyword);
            output.append("\n");
            return;
        }
    }
    for (auto type : node->types){
        if (type != "" && type != "digit" && type != "digits" && type != "letter"){
            if (type == "addop"){
                if ((temp == "+" || temp == "-")){
                    output.append(type);    // type to phase 2 -------------------------------
                    cfgInputParser.parse_lexicial(type);
                    output.append("\n");
                    return;
                }
            }
            else if (type == "mulop"){
                if (temp == "*" || temp == "/"){
                    output.append(type);      // type to phase 2 -------------------------------
                    cfgInputParser.parse_lexicial(type);
                    output.append("\n");
                    return;
                }
            }else if (type == "assign"){
                if (temp == "="){
                    output.append(type);     // type to phase 2 -------------------------------
                    cfgInputParser.parse_lexicial(type);
                    output.append("\n");
                    return;
                }
            }
            else{
                output.append(type);         // type to phase 2 -------------------------------
                cfgInputParser.parse_lexicial(type);
                output.append("\n");
                return;
            }
        }
    }
}

void Parser::write_output_file() const{
    ofstream file;
    file.open ("../output.txt");
    file << output;
    file.close();
}

void Parser::parse(vector<Node *> dfa, string path, Node* start_point, cfg_input_parser cfgInputParser){
    string file = read_java_file(path);
    initialize(start_point);
    bool not_more = true;
    for (int i = 0; i < file.size();){
        char c = file[i];
        not_more = true;
        bool symbols = (c == ',' || c == ';');
        bool spaces = (c == '\t' || c == ' ' || c == '\n');
        bool brackets = (c == '(' || c == '{' || c == '}' || c == ')');
        if (spaces){
            check_spaces(start_point, cfgInputParser);
            i++;
            continue;
        }
        if (brackets){
            check_brackets(start_point, c, cfgInputParser);
            i++;
            continue;
        }

        bool step_taken = false;
        for(auto &entry : current_node->transitions){
            char t = entry.first;
            if(t == c){
                not_more = false;
                step_taken = true;
                token.push_back(c);
                prev_node = current_node;
                prev_node_acceptance = prev_node->acceptance;
                current_node = entry.second[0];
                current_node_acceptance = current_node->acceptance;
                break;
            }
        }
        if(symbols && token.size() == 0){
            check_symbols(start_point, c,cfgInputParser);
            i++;
            continue;
        }
        if (symbols && current_node_acceptance){
            check_symbols(start_point, c,cfgInputParser);
            i++;
            continue;
        }
        else if (symbols && !current_node_acceptance){
            output.append("error\n");
        }
        if (not_more && current_node_acceptance){
            print_node_type(current_node,cfgInputParser);
            initialize(start_point);
            continue;
        }
        if(!step_taken && !symbols && !spaces && !brackets){
            output.append("error: ");
            output += c;
            string s = string(1,c);
            cfgInputParser.parse_lexicial(s);
            output.append("\n");
        }
        if(i == file.size() - 1 && token.size() != 0 && step_taken && current_node_acceptance){
            print_node_type(current_node,cfgInputParser);
        }
        i++;
    }
    cfgInputParser.parse_lexicial("$");
    write_output_file();
}


int Node::counter = 1;

int main(int argc, char* argv[])
{
    string relative_path = "../input_example.txt";
    read_input r;
    cfg_input_parser cfgInputParser = prepare_parsing_table();
    r.read_lines(relative_path);
    NFA* s = r.routing_nfa; //regular_expressions["relop"]; //routing_nfa;
    cout << s->node_map.size()<< endl;

    DFA dfa_2 = DFA(s);
    Node* res = dfa_2.convert_to_DFA();
    cout << "Intital Node ID = " << dfa_2.DFA_start_node.id << endl;
    cout << "Number of States = " << dfa_2.DFA_node_map.size() << endl;
    dfa_2.print_dfa();
    cout << "-------------------------------------------------------------------------------" << endl;
    vector<Node*> minimized_dfa = dfa_2.minimize();
    cout << "--------------------------------------------------------------------------------" << endl;
    dfa_2.print_dfa();
    cout << "-----------------------------------------------------------------------------------" << endl;


    vector<Node*> nn;
    for(auto &entry : minimized_dfa)
        nn.push_back(entry);

    cout <<"minimzed finished, \n" << "nn.size: " << nn.size()<<endl;
    cout << "first node id: " << dfa_2.DFA_start_node.id << endl;
    //vector<Node*> dfa = lexical_analysis(relative_path, r);
    string file = "../Main.java";
    Parser parser(r);
    parser.parse(nn, file, &dfa_2.DFA_start_node,cfgInputParser);
    cout << "\nDone Done";
    return 0;
}
