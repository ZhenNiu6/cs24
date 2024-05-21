#include "List.h"
#include <iostream>

// List Member Functions
Node::Node(std::string node_key, int node_value){
    key = node_key;
    value = node_value;
    before = nullptr;
    after = nullptr;
}



List::List(){
    head = nullptr;
    tail = nullptr;
}

List::~List(){
    Node* current = head;
    while(current != tail){
        Node* next = current->after;
        delete current;
        current = next;
    }
    delete current;
    head = nullptr;
    tail = nullptr;
}

void List::insert(std::string node_key, int node_value){
    Node* x = new Node(node_key, node_value);
    if(head != nullptr){
        tail->after = x;
        x->before = tail;
        tail = x;
    }
    else{
        head = x;
        tail = x;
    }
}

Node* List::lookup(std::string x) const{
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

void List::remove(Node* node){
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
    delete node;
}

void List::clear(){
    Node* current = head;
    while(current){
        Node* next = current->after;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
}