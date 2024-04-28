#ifndef NODE_H
#define NODE_H

#include <string>

struct Node {
    std::string value;
    size_t subweight;
    Node* child[2];

    Node(); // constructor
    ~Node();
    Node(std::string s);
    void add_weight_entire(Node* node);
    void add_weight(Node* node, Node* target);

};

#endif
