#ifndef STACK_H
#define STACK_H
#include <cstddef>
#include "AST.h"
#include "Nodes.h"

// Use this file to define your Stack type.
// Implement its member functions in Stack.cpp.

class Stack{
    size_t num;
    size_t cap;
    Node** tree;

public:
    Stack();
    Stack(const Stack& other);
    ~Stack();
    size_t count() const;
    void see_top() const;
    Node* pop();
    void push(Node* node);
    Node* top();
    Node* lookup(size_t index) const;
};


#endif
