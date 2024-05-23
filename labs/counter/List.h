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
    Node* next;

    // Node(std::string node_key, int node_value);
    Node(std::string node_key, int node_value){
    key = node_key;
    value = node_value;
    before = nullptr;
    after = nullptr;
    next = nullptr;
}
};

class List{
public:
    Node* head;
    Node* tail;

    // List();
    // ~List();
    // void insert(Node* node);
    // Node* lookup(std::string x) const;
    // void remove(Node* node);
    // void clear();
    List(){
    head = nullptr;
    tail = nullptr;
}

~List(){
    Node* current = head;
    if(!current){
        return;
    }
    while(current != tail){
        Node* next = current->after;
        delete current;
        current = next;
    }
    delete current;
    head = nullptr;
    tail = nullptr;
}

void insert(Node* node){
    if(head != nullptr){
        tail->after = node;
        node->before = tail;
        tail = node;
    }
    else{
        head = node;
        tail = node;
    }
}

Node* lookup(std::string x) const{
    Node* current = head;
    if(!current){
        return nullptr;
    }
    while(current->key != x){
        if(!current->after){
            return nullptr;
        }
        current = current->after;
    }
    return current;
}

void remove(Node* node){
    if((!head) || (!node)){
        return;
    }
    if(node == head){
        head = node->after;
    }
    else{
        if(node->before){
            node->before->after = node->after;
        }
        // node->before->after = node->after;
    }

    if(node == tail){
        tail = node->before;
    }
    else{
        if(node->after){
            node->after->before = node->before;
        }
        // node->after->before = node->before;
    }
    // std::cout << node << '\n';
    delete node;
    // node->before = nullptr;
    // node->after = nullptr;
}

// void clear(){
//     Node* current = head;
//     while(current){
//         Node* next = current->after;
//         delete current;
//         current = next;
//     }
//     head = nullptr;
//     tail = nullptr;
// }
};

#endif
