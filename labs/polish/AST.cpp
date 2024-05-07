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
        // std::cout << token << '\n';
        if((token == "+") || (token == "-") || (token == "*") || (token == "/") || (token == "%")){
            if(stack.count() < 2){
                while(stack.count() > 0){
                    delete stack.pop();
                }
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
            Node* add = new Node(); 
            add->set_operator('+'); 
            // std::cout << "iii" << '\n';
            add->right_operand(stack.pop());
            add->left_operand(stack.pop());
            // std::cout << "hh" << '\n';
            // add->see_var();
            double ans = add->get_value(); 
            // add.see_var();
            
            add->set_value(ans);
            stack.push(add);
            
        }
        else if(token == "-"){
            Node* subtract = new Node(); 
            subtract->set_operator('-'); 
            // std::cout << "iii" << '\n';
            subtract->right_operand(stack.pop());
            subtract->left_operand(stack.pop());
            // std::cout << "hh" << '\n';
            // subtract->see_var();
            double ans = subtract->get_value(); 
            // add.see_var();
            
            subtract->set_value(ans);
            stack.push(subtract);
            
        }
        else if(token == "*"){
            Node* multiply = new Node(); 
            multiply->set_operator('*'); 
            multiply->right_operand(stack.pop());
            
            multiply->left_operand(stack.pop());
            
            double ans = multiply->get_value(); 
            multiply->set_value(ans);
            stack.push(multiply);
        }
        else if(token == "/"){
            Node* divide = new Node(); 
            divide->set_operator('/'); 
            divide->right_operand(stack.pop());
            
            divide->left_operand(stack.pop());
            // Node* r_operand = divide->get_right();
            // if(r_operand->value() == 0){
            //     throw std::runtime_error("Division by zero.");
            // }
            
            double ans = divide->get_value(); 
            
            divide->set_value(ans);
            stack.push(divide);
        }
        else if(token == "%"){
            Node* modulo = new Node(); 
            modulo->set_operator('%'); 
            modulo->right_operand(stack.pop());
            
            modulo->left_operand(stack.pop());
            
            double ans = modulo->get_value(); 
            modulo->set_value(ans);
            stack.push(modulo);
        }
        else if(token == "~"){
            Node* negate = new Node(); 
            negate->set_operator('~'); 
            negate->left_operand(stack.pop());
            
            double ans = negate->get_value(); 
            
            negate->set_value(ans);
            stack.push(negate);
        }
        else{
            bool dot = false;
            for(size_t i = 0; i < token.length(); i ++){
                if(!isdigit(token[i])){
                    if((token[i] == '+') || (token[i] == '-')){
                        if(i == 0){
                            continue;
                        }
                        else{
                            throw std::runtime_error("Invalid token: " + token);
                        }
                    }
                    else if(token[i] == '.'){
                        if(i != token.length() - 1){
                            if(dot != true){ // only one dot 
                                dot = true;
                                continue;
                            }
                            throw std::runtime_error("Invalid token: " + token);
                        }
                        else{
                            throw std::runtime_error("Invalid token: " + token);
                        }
                    }
                    else{
                        while(stack.count() > 0){
                            delete stack.pop();
                        }
                        throw std::runtime_error("Invalid token: " + token);
                    }
                }
            }
            double val = std::stod(token);
            Node* number = new Node(val);
            // std::cout << "here" << '\n';
            stack.push(number);
            // std::cout << "count " << stack.count() << '\n';
            // stack.see_top();
        }
    }
    if(stack.count() == 0){
        throw std::runtime_error("No input.");
    }
    if(stack.count() > 1){
        while(stack.count() > 0){
            delete stack.pop();
        }
        throw std::runtime_error("Too many operands.");
    }

    return stack.pop();

    // ...
}
