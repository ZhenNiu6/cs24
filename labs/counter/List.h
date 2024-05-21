#ifndef LIST_H
#define LIST_H

#include <string>

// TODO...

class Node{
public:
    std::string key;
    int value;
    Node* before;
    Node* after;

    Node(std::string node_key, int node_value);
};

class List{
public:
    Node* head;
    Node* tail;

    List();
    ~List();
    void insert(std::string node_key, int node_value);
    Node* lookup(std::string x) const;
    void remove(Node* node);
    void clear();
};

#endif
