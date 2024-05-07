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
// // Number subclass
// Number::Number(double val){
//   num = val;
// }

// std::string Number::prefix() const{
//   return std::to_string(num);
// }

// std::string Number::postfix() const{
//   return std::to_string(num);
// }

// double Number::value() const{
//   return num;
// }


// // Add subclass
// Add::Add(){
//   left = nullptr;
//   right = nullptr;
// }

// void Add::left_operand(AST* node){
//   left = node;
// }

// void Add::right_operand(AST* node){
//   right = node;
// }

// std::string Add::prefix() const{
//   return "+ " + left->prefix() + " " + right->prefix();
// }

// std::string Add::postfix() const{
//   return left->prefix() + " " + right->prefix() + " +";
// }

// double Add::value() const{
//   return left->value() + right->value();
// }


// // Subtract subclass
// Subtract::Subtract(){
//   left = nullptr;
//   right = nullptr;
// }

// void Subtract::left_operand(AST* node){
//   left = node;
// }

// void Subtract::right_operand(AST* node){
//   right = node;
// }

// std::string Subtract::prefix() const{
//   return "- " + left->prefix() + " " + right->prefix();
// }

// std::string Subtract::postfix() const{
//   return left->prefix() + " " + right->prefix() + " -";
// }

// double Subtract::value() const{
//   return left->value() - right->value();
// }


// // Multiply subclass
// Multiply::Multiply(){
//   left = nullptr;
//   right = nullptr;
// }

// void Multiply::left_operand(AST* node){
//   left = node;
// }

// void Multiply::right_operand(AST* node){
//   right = node;
// }

// std::string Multiply::prefix() const{
//   return "* " + left->prefix() + " " + right->prefix();
// }

// std::string Multiply::postfix() const{
//   return left->prefix() + " " + right->prefix() + " *";
// }

// double Multiply::value() const{
//   return left->value() * right->value();
// }


// // Divide subclass
// Divide::Divide(){
//   left = nullptr;
//   right = nullptr;
// }

// void Divide::left_operand(AST* node){
//   left = node;
// }

// void Divide::right_operand(AST* node){
//   right = node;
// }

// std::string Divide::prefix() const{
//   return "/ " + left->prefix() + " " + right->prefix();
// }

// std::string Divide::postfix() const{
//   return left->prefix() + " " + right->prefix() + " /";
// }

// double Divide::value() const{
//   return left->value() / right->value();
// }



// // Modulo subclass
// Modulo::Modulo(){
//   left = nullptr;
//   right = nullptr;
// }

// void Modulo::left_operand(AST* node){
//   left = node;
// }

// void Modulo::right_operand(AST* node){
//   right = node;
// }

// std::string Modulo::prefix() const{
//   return "% " + left->prefix() + " " + right->prefix();
// }

// std::string Modulo::postfix() const{
//   return left->prefix() + " " + right->prefix() + " %";
// }

// double Modulo::value() const{
//   return fmod(left->value(),right->value());
// }



// // Negate subclass
// Negate::Negate(){
//   left = nullptr;
// }

// void Negate::left_operand(AST* node){
//   left = node;
// }

// std::string Negate::prefix() const{
//   return "~ " + left->prefix();
// }

// std::string Negate::postfix() const{
//   return left->prefix() + " ~";
// }

// double Negate::value() const{
//   return -1 * left->value();
// }


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

void Node::set_operator(char x){
  operation = x;
}

void Node::left_operand(Node* node){
  left = node;
}

void Node::right_operand(Node* node){
  right = node;
}

std::string Node::prefix() const{
  if(operation == '\0'){
    return std::to_string(number);
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
    return std::to_string(number);
  }
  else if(operation == '+'){
    return left->prefix() + " " + right->prefix() + " +";
  }
  else if(operation == '-'){
    return left->prefix() + " " + right->prefix() + " -";
  }
  else if(operation == '*'){
    return left->prefix() + " " + right->prefix() + " *";
  }
  else if(operation == '/'){
    return left->prefix() + " " + right->prefix() + " /";
  }
  else if(operation == '%'){
    return left->prefix() + " " + right->prefix() + " %";
  }
  else{
    return left->prefix() + " ~";
  }
}

double Node::value() const{
  if(operation == '\0'){
    return number;
  }
  else if(operation == '+'){
    std::cout << "h" << '\n';
    return left->value() + right->value();
  }
  else if(operation == '-'){
    return left->value() - right->value();
  }
  else if(operation == '*'){
    return left->value() * right->value();
  }
  else if(operation == '/'){
    return left->value() / right->value();
  }
  else if(operation == '%'){
    return fmod(left->value(),right->value());
  }
  else{
    return -1 * left->value();
  }
}