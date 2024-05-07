#ifndef NODES_H
#define NODES_H

#include "AST.h"

// Declare your AST subclasses here.
// Implement their member functions in Nodes.cpp.
// class Number: public AST{
//     double num; 

// public:
//     Number(double val);
//     std::string prefix() const;
//     std::string postfix() const;
//     double value() const;
// };

// class Add: public AST{
//     AST* left;
//     AST* right;

// public:
//     Add();
//     void left_operand(AST* node);
//     void right_operand(AST* node);
//     std::string prefix() const;
//     std::string postfix() const;
//     double value() const;
// };

// class Subtract: public AST{
//     AST* left;
//     AST* right;
// public:
//     Subtract();
//     void left_operand(AST* node);
//     void right_operand(AST* node);
//     std::string prefix() const;
//     std::string postfix() const;
//     double value() const;

// };

// class Multiply: public AST{
//     AST* left;
//     AST* right;
// public:
//     Multiply();
//     void left_operand(AST* node);
//     void right_operand(AST* node);
//     std::string prefix() const;
//     std::string postfix() const;
//     double value() const;

// };

// class Divide: public AST{
//     AST* left;
//     AST* right;
// public:
//     Divide();
//     void left_operand(AST* node);
//     void right_operand(AST* node);
//     std::string prefix() const;
//     std::string postfix() const;
//     double value() const;

// };

// class Modulo: public AST{
//     AST* left;
//     AST* right;
// public:
//     Modulo();
//     void left_operand(AST* node);
//     void right_operand(AST* node);
//     std::string prefix() const;
//     std::string postfix() const;
//     double value() const;
// };

// class Negate: public AST{
//     AST* left;
// public:
//     Negate();
//     void left_operand(AST* node);
//     std::string prefix() const;
//     std::string postfix() const;
//     double value() const;
// };


class Node: public AST{
    Node* left;
    Node* right;
    double number;
    char operation;

public:
    Node();
    Node(double val);
    void see_var() const;
    void set_operator(char x);
    void set_value(double val);
    void left_operand(Node* node);
    void right_operand(Node* node);
    std::string prefix() const;
    std::string postfix() const;
    double value() const;
};



#endif
