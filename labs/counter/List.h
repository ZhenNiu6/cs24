#ifndef LIST_H
#define LIST_H

#include <string>
#include <iostream>

using namespace std;

class Node {

public:
    int mValue;
    string mKey;
    Node* mBefore;
    Node* mAfter;
    Node* hash_after;

    Node();
    Node(int value, string key);
    
};

class List {

public:
    Node* mStart;
    Node* mEnd;

    List();
    void destruct_helper(Node* current);
    ~List();
    void insert(Node* node);
    Node* find_helper(string input, Node* current) const;
    Node* find(string input) const;
    void remove(Node* current);
};

#endif
