#include "Nodes.h"

#include <sstream>
#include <string>
#include <cmath>
#include <iostream>

// This creates the number format the autograder expects:
std::string format(double number) {
  std::ostringstream stream;
  stream << number;
  return stream.str();
}


// Implement your AST subclasses' member functions here.


Node::Node(){
  left = nullptr;
  right = nullptr;
  number = 0;
  operation = '\0';
}

Node::Node(double val){
  left = nullptr;
  right = nullptr;
  number = val;
  operation = '\0';
}

Node::~Node(){
  delete left;
  delete right;
}

void Node::see_var() const{
  
  std::cout << "number " << number << '\n';
  std::cout << "operator " << operation << '\n';
  std::cout << "left " << left->value() << '\n';
}

void Node::set_operator(char x){
  operation = x;
}

void Node::set_value(double val){
  number = val;
}

Node* Node::get_right(){
  return right;
}

void Node::left_operand(Node* node){
  left = node;
}

void Node::right_operand(Node* node){
  right = node;
}

std::string Node::prefix() const{
  if(operation == '\0'){
    return format(number);
  }
  else if(operation == '+'){
    return "+ " + left->prefix() + " " + right->prefix();
  }
  else if(operation == '-'){
    return "- " + left->prefix() + " " + right->prefix();
  }
  else if(operation == '*'){
    return "* " + left->prefix() + " " + right->prefix();
  }
  else if(operation == '/'){
    return "/ " + left->prefix() + " " + right->prefix();
  }
  else if(operation == '%'){
    return "% " + left->prefix() + " " + right->prefix();
  }
  else{
    return "~ " + left->prefix();
  }
}

std::string Node::postfix() const{
  if(operation == '\0'){
    return format(number);
  }
  else if(operation == '+'){
    return left->postfix() + " " + right->postfix() + " +";
  }
  else if(operation == '-'){
    return left->postfix() + " " + right->postfix() + " -";
  }
  else if(operation == '*'){
    return left->postfix() + " " + right->postfix() + " *";
  }
  else if(operation == '/'){
    
    return left->postfix() + " " + right->postfix() + " /";
  }
  else if(operation == '%'){
    
    return left->postfix() + " " + right->postfix() + " %";
  }
  else{
    return left->postfix() + " ~";
  }
}

double Node::value() const{
  if(operation == '\0'){
    return number;
  }
  else if(operation == '+'){
    return left->value() + right->value();
  }
  else if(operation == '-'){
    return left->value() - right->value();
  }
  else if(operation == '*'){
    return left->value() * right->value();
  }
  else if(operation == '/'){
    if(right->value() == 0){
      throw std::runtime_error("Division by zero.");
    }
    return left->value() / right->value();
  }
  else if(operation == '%'){
    if(right->value() == 0){
      throw std::runtime_error("Division by zero.");
    }
    return fmod(left->value(),right->value());
  }
  else{
    return -1 * left->value();
  }
}



double Node::get_value() const{
  if(operation == '\0'){
    return number;
  }
  else if(operation == '+'){
    return left->get_value() + right->get_value();
  }
  else if(operation == '-'){
    return left->get_value() - right->get_value();
  }
  else if(operation == '*'){
    return left->get_value() * right->get_value();
  }
  else if(operation == '/'){
    return left->get_value() / right->get_value();
  }
  else if(operation == '%'){
    return fmod(left->get_value(),right->get_value());
  }
  else{
    return -1 * left->get_value();
  }
}