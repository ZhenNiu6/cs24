#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "AST.h"
#include "Nodes.h"
using namespace std;

// Use this file to define your Stack type.
// Implement its member functions in Stack.cpp.

class stack {

    Node** mStack;
    size_t mycapacity;
    size_t mylength;

public:

    stack();
    ~stack();
    Node* pop();
    void push(Node* current);
    size_t return_capacity();
    size_t return_length();;

};

#endif
