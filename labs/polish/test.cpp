#include "AST.h"
#include <iostream>

// If you want a different main function, write it here!
// This file won't be graded - do whatever you want.

int main() {
  std::cout << "This program doesn't do anything yet...\n";

  return 0;
}


AST* AST::parse(const std::string& expression) {
    std::string token;
    std::istringstream stream(expression);
    Stack stack;

    while(stream >> token) {
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
            // Node* add = dynamic_cast<Node*>(stack.top());
            // Node* add = new Node();
            // add->set_operator('+');
            // Node* r_operand = stack.top();
            // add->right_operand(r_operand);
            // stack.pop();
            // Node* l_operand = stack.top();
            // add->left_operand(l_operand);
            // stack.pop();
            // double ans = add->value();
            // Node* add_ans = new Node(ans);
            // stack.push(add_ans);
            // delete add;
            Node add; 
            add.set_operator('+'); 
            Node r_operand = stack.top();
            add.right_operand(&r_operand);
            stack.pop(); 
            Node l_operand = stack.top();
            add.left_operand(&l_operand);
            stack.pop(); 
            double ans = add.value(); 
            Node add_ans(ans);
            stack.push(add_ans);
        }
        else if(token == "-"){
            Node subtract; 
            subtract.set_operator('-'); 
            Node r_operand = stack.top();
            subtract.right_operand(&r_operand);
            stack.pop(); 
            Node l_operand = stack.top();
            subtract.left_operand(&l_operand);
            stack.pop(); 
            double ans = subtract.value(); 
            Node subtract_ans(ans);
            stack.push(subtract_ans);
        }
        else if(token == "*"){
            Node multiply; 
            multiply.set_operator('*'); 
            Node r_operand = stack.top();
            multiply.right_operand(&r_operand);
            stack.pop(); 
            Node l_operand = stack.top();
            multiply.left_operand(&l_operand);
            stack.pop(); 
            double ans = multiply.value(); 
            Node multiply_ans(ans);
            stack.push(multiply_ans);
        }
        else if(token == "/"){
            Node divide; 
            divide.set_operator('/'); 
            Node r_operand = stack.top();
            divide.right_operand(&r_operand);
            stack.pop(); 
            Node l_operand = stack.top();
            divide.left_operand(&l_operand);
            stack.pop(); 
            double ans = divide.value(); 
            Node divide_ans(ans);
            stack.push(divide_ans);
        }
        else if(token == "%"){
            Node modulo; 
            modulo.set_operator('%'); 
            Node r_operand = stack.top();
            modulo.right_operand(&r_operand);
            stack.pop(); 
            Node l_operand = stack.top();
            modulo.left_operand(&l_operand);
            stack.pop(); 
            double ans = modulo.value(); 
            Node modulo_ans(ans);
            stack.push(modulo_ans);
        }
        else if(token == "~"){
            Node negate; 
            negate.set_operator('~'); 
            Node l_operand = stack.top();
            negate.left_operand(&l_operand);
            stack.pop(); 
            double ans = negate.value(); 
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
            stack.push(number);
        }
    }
    if(stack.count() == 0){
        throw std::runtime_error("No input.");
    }
    if(stack.count() > 1){
        throw std::runtime_error("Too many operands.");
    }
    Node* answer = new stack.top();
    return answer;

    // ...
}
