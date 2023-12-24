//
// Created by zizoa on 12/24/2023.
//
#include "CFG parser_test.h"

int main(int argc, char* argv[]){
    string relative_path = "../CFG_input.txt";
    CFG_parser ob;
    ob.read_lines(relative_path);
    cout << "compiled successfully" << endl;
    return 0;
}