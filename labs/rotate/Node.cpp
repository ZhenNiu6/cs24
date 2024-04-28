#include "Node.h"
#include <iostream>

// Node Function Implementations
Node::Node(){
    value = "";
    subweight = 0;
    child[0] = nullptr;
    child[1] = nullptr;
}

Node::Node(std::string s){
    value = s;
    subweight = 1;
    child[0] = nullptr;
    child[1] = nullptr;
}

Node::~Node(){
    for(size_t i = 0; i < 2; i ++){
        delete child[i];
    }
}


void Node::add_weight_entire(Node* node){
    if(node != nullptr){
        node->subweight ++;
        if(node->child[0] != nullptr){
            add_weight_entire(node->child[0]);
            add_weight_entire(node->child[1]);
        }
    }   
}

void Node::add_weight(Node* node, Node* target){
    if(node != nullptr){
        // std::cout << "node: " << node->subweight << '\n';
        // node->subweight ++;
        // if(node->child[1] != nullptr){
        //     add_weight_entire(node->child[1]);
        // }
        if(node->value > target->value){
            node->subweight ++;
            add_weight_entire(node->child[1]);
        }
        
        add_weight(node->child[0], target);
    // }
    }
    
}