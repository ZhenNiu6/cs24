#include "AST.h"
#include "Nodes.h"
#include "Stack.h"

#include <sstream>
#include <iostream>

AST* AST::parse(const std::string& expression) {
    std::string token;
    std::istringstream stream(expression);
    Stack stack;

    while(stream >> token) {
        std::cout << token << '\n';
        if((token == "+") || (token == "-") || (token == "*") || (token == "/") || (token == "%")){
            if(stack.count() < 2){
                std::runtime_error("Not enough operands.");
            }
        }
        else if(token == "~"){
            if(stack.count() < 1){
                std::runtime_error("Not enough operands.");
            }
        }


        if(token == "+"){
            // std::cout << "hhh" << '\n';
            Node add; 
            add.set_operator('+'); 
            // std::cout << "iii" << '\n';
            add.right_operand(stack.lookup(stack.count()-1));
            
            // std::cout << "h" << '\n';
            add.left_operand(stack.lookup(stack.count()-2));
            // std::cout << "hh" << '\n';
            
            double ans = add.value(); 
            // std::cout << "hi" << '\n';
            stack.pop();
            stack.pop();
            Node add_ans(ans);
            stack.push(add_ans);
        }
        else if(token == "-"){
            Node subtract; 
            subtract.set_operator('-'); 
            subtract.right_operand(stack.lookup(stack.count()-1));
            
            subtract.left_operand(stack.lookup(stack.count()-2));
            
            double ans = subtract.value(); 
            stack.pop(); 
            stack.pop(); 
            Node subtract_ans(ans);
            stack.push(subtract_ans);
        }
        else if(token == "*"){
            Node multiply; 
            multiply.set_operator('*'); 
            multiply.right_operand(stack.lookup(stack.count()-1));
            
            multiply.left_operand(stack.lookup(stack.count()-2));
            
            double ans = multiply.value(); 
            stack.pop(); 
            stack.pop(); 
            Node multiply_ans(ans);
            stack.push(multiply_ans);
        }
        else if(token == "/"){
            Node divide; 
            divide.set_operator('/'); 
            divide.right_operand(stack.lookup(stack.count()-1));
            
            divide.left_operand(stack.lookup(stack.count()-2));
            
            double ans = divide.value(); 
            stack.pop(); 
            stack.pop(); 
            Node divide_ans(ans);
            stack.push(divide_ans);
        }
        else if(token == "%"){
            Node modulo; 
            modulo.set_operator('%'); 
            modulo.right_operand(stack.lookup(stack.count()-1));
            
            modulo.left_operand(stack.lookup(stack.count()-2));
            
            double ans = modulo.value(); 
            stack.pop(); 
            stack.pop(); 
            Node modulo_ans(ans);
            stack.push(modulo_ans);
        }
        else if(token == "~"){
            Node negate; 
            negate.set_operator('~'); 
            negate.left_operand(stack.lookup(stack.count()-1));
            
            double ans = negate.value(); 
            stack.pop(); 
            Node negate_ans(ans);
            stack.push(negate_ans);
        }
        else{
            for(size_t i = 0; i < token.length(); i ++){
                if(!isdigit(token[i])){
                    if((token[i] == '+') || (token[i] == '-')){
                        if(i == 0){
                            continue;
                        }
                    }
                    else if(token[i] == '.'){
                        if(i != token.length() - 1){
                            continue;
                        }
                    }
                    else{
                        throw std::runtime_error("Invalid token: " + token);
                    }
                }
            }
            double val = std::stod(token);
            Node number(val);
            std::cout << "here" << '\n';
            stack.push(number);
            std::cout << "count " << stack.count() << '\n';
            stack.see_top();
        }
    }
    if(stack.count() == 0){
        throw std::runtime_error("No input.");
    }
    if(stack.count() > 1){
        throw std::runtime_error("Too many operands.");
    }
    return stack.top();

    // ...
}
