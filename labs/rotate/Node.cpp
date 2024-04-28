#include "Node.h"

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

size_t Node::add_weight(Node* node){
    if(node == nullptr){
        return 0;
    }
    else{
        return 1 + node->add_weight(node->child[0]);
    }
}