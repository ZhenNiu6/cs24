#ifndef NODE_H
#define NODE_H

#include <string>

struct Node {
    std::string value;
    size_t weight;
    Node* child[2];

    Node(); // constructor
    ~Node();
    Node(std::string s);
    // void add_weight_entire(Node* node);
    // void add_index(Node* node, Node* target);
    void find_weight();

};

#endif
