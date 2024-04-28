#ifndef NODE_H
#define NODE_H

#include <string>

struct Node {
    std::string value;
    size_t subweight;
    Node* child[2];

    Node(); // constructor
    Node(std::string s);
    size_t add_weight(Node* node);

};

#endif
