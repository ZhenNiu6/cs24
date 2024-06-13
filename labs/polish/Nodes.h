#ifndef NODES_H
#define NODES_H

#include "AST.h"
// #include <memory>

// Declare your AST subclasses here.
// Implement their member functions in Nodes.cpp.



class Node: public AST{
    Node* left;
    Node* right;
    
    double number;
    char operation;

public:
    Node();
    Node(double val);
    ~Node();
    void see_var() const;
    void set_operator(char x);
    void set_value(double val);
    Node* get_right();
    double get_value() const;
    void left_operand(Node* node);
    void right_operand(Node* node);
    std::string prefix() const;
    std::string postfix() const;
    double value() const;
};



#endif
