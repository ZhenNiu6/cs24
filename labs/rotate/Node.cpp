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
    subweight1 = child[0] ? child[0]->weight:0;
    subweight2 = child[1] ? child[1]->weight:0;
    weight = 1 + subweight1 + subweight2;
    return weight;

}

// void Node::add_weight_entire(Node* node){
//     if(node != nullptr){
//         node->index_ ++;
//         std::cout << "current node: " << node->value << " index: " << node->index_ << '\n';
//         if(node->child[0] != nullptr){
//             add_weight_entire(node->child[0]);
//             add_weight_entire(node->child[1]);
//         }
//     }   
// }

// void Node::add_index(Node* node, Node* target){
//     if(node != nullptr){
//         std::cout << "node: " << node->index_ << '\n';
//         // node->index_ ++;
//         // if(node->child[1] != nullptr){
//         //     add_weight_entire(node->child[1]);
//         // }
//         if(node->value > target->value){
//             node->index_ ++;
//             add_weight_entire(node->child[1]);
//             add_index(node->child[0], target);
//         }
//         else{
//             add_index(node->child[1], target);
//         }
//         // add_weight(node->child[0], target);
//     // }
//     }
    
// }

