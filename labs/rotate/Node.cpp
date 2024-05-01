#include "Node.h"
#include <iostream>

// Node Function Implementations
Node::Node(){
    value = "";
    weight = 0;
    child[0] = nullptr;
    child[1] = nullptr;
}

Node::Node(std::string s){
    value = s;
    weight = 1;
    child[0] = nullptr;
    child[1] = nullptr;
    parent = nullptr;
}

Node::~Node(){
    for(size_t i = 0; i < 2; i ++){
        delete child[i];
    }
}


size_t Node::find_weight(){
    size_t subweight1, subweight2;
    if(child[0] == nullptr){
        subweight1 = 0;
    }
    else{
        subweight1 = child[0]->weight;
    }
    if(child[1] == nullptr){
        subweight2 = 0;
    }
    else{
        subweight2 = child[1]->weight;
    }
    // subweight1 = child[0] != nullptr ? child[0]->weight:0;
    // subweight2 = child[1] != nullptr ? child[1]->weight:0;
    weight = 1 + subweight1 + subweight2;
    return weight;

}

