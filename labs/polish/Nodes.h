#ifndef NODES_H
#define NODES_H

#include "AST.h"
using namespace std;

// Declare your AST subclasses here.
// Implement their member functions in Nodes.cpp.

class Node: public AST {

public:

    Node* left;
    Node* right;
    double mNum;
    char mOperator;

    Node();
    ~Node();
    Node(double mNum);
    Node(char mOperator);
    string prefix() const;
    string postfix() const;
    double value() const;

};


#endif
