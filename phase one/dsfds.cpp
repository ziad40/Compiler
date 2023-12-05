// NFA star_op(stack<string> &operators, stack<string> &operands, string name){
    //     string nfa_name = operands.top(); operands.pop();
    //     if(regular_definations.find(nfa_name) != regular_definations.end()){
    //         operands.push(name);
    //         return util.star_NFA(regular_definations[nfa_name]);
    //     }
    //     if(regular_expressions.find(nfa_name) != regular_expressions.end()){
    //         operands.push(name);
    //         return util.star_NFA(regular_expressions[nfa_name]);
    //     }
    //     node s;
    //     node* s_tmp = &s;
    //     node e(false);
    //     for(char x : nfa_name){
    //         s.add_next_node(x, &)
    //     }
        
    // }

    // void evaluate_expression(string line, int i, string name){
        // stack<string> operators;
        // stack<string> operands;
        // string word;
        // while(i < line.size()){
        //     if(line[i] == '-'){
        //         operators.push("-");
        //     }
        //     else if(line[i] == '*'){
        //         operators.push("*");
        //     }
        //     else if(line[i] == '|' || line[i] == '+'){
        //         if(operators.top() == "-"){
        //             regular_definations[name] = minus_op(operators, operands, name);
        //         }
        //         if(operators.top() == "*"){
        //             regular_definations[name] = star_op(operators, operands, name);
        //         }
        //         if(line[i] == '|'){
        //             operators.push("|");
        //         }        
        //         else{
        //             operators.push("&");
        //             operators.push("*");
        //             operands.push(operands.top());
        //         }
        //     }
        //     else if (line[i] == ')'){
        //         while (operators.top() != "(")
        //         {
        //             string t = operators.top();operators.pop();
        //             if(t == "-"){
        //                 regular_definations[name] = star_op(operators, operands, name);
        //             }else if(t == "*"){
        //                 regular_definations[name] = star_op(operators, operands, name);
        //             }
        //             else if(t == "&"){
        //                 regular_definations[name] = concat_op(operators, operands, name);
        //             }else if(t == "|"){
        //                 regular_definations[name] = or_op(operators, operands, name);
        //             }
        //         }
        //         operators.pop();
                
        //     }
        //     else if (line[i] == '('){
        //         operators.push("&");
        //         operators.push("(");
        //     }
        //     else{
        //         if(line[i] == ' '){
        //             operands.push(word);
        //             word = "";
        //         }else{
        //             word+= line[i];
        //         }
        //     }
        // }
        // if(!word.empty()) operands.push(word);
    // }