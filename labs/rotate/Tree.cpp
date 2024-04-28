#include "Tree.h"
#include <iostream>

// Tree Function Implementations
Tree::Tree(){
    root = nullptr;
    num = 0;
}

Tree::~Tree(){
    num = 0;
}

void Tree::clear(){
    if(root != nullptr){
        clear_helper(root);
    }
}

size_t Tree::count() const{
    return num;
}

bool Tree::contains(const std::string& s) const{
    return contains_helper(root, s);
}

size_t Tree::find(const std::string& s) const{
    return find_helper(root, s);
}

std::string Tree::lookup(size_t index) const{
    return lookup_helper(root, index);
}

void Tree::insert(const std::string& s){
    Node* x = new Node(s);
    if(root == nullptr){
        root = x;
        num ++;
    }
    else{
        insert_helper(root, x);
        num ++;
    }
    

}

// void insert_h(Node* root, Node* thing){
//     root->add_weight();
//     //std::cout << "inserting " << thing->value << " to " << root->value << "\n";
//     //left tree
//     if(thing->value <= root->value){
//         if(root->child[0] == nullptr){
//             root->add_weight(h);
//             root->child[0] = thing;
//             thing->subweight = root->subweight - 1;
//             //std::cout << "inserted: " << thing->value << thing->subweight;
//         }
//         else{
//             root->add_weight(h);
//             insert_h(root->child[0], thing);
//         }
//     }
//     //right tree
//     else{
//         if(root->child[1] == nullptr){
//             root->child[1] = thing;
//             thing->subweight = root->subweight + 1;
//             //std::cout << "data: " << thing->value << "\n";
//             //std::cout << "left: " << root->child[0]->value << " right: " << root->child[1]->value << "\n";
//         }
//         else{
//             insert_h(root->child[1], thing);
//         }
//     }
// }

// void Tree::insert(const std::string& s){
//     Node* n = new Node(s);
//     if(this->root == nullptr){
//         this->root = n;
//     }
//     else{
//         insert_h(this->root, n);
//     }
// }

void Tree::print() const{
    // std::cout << root->value << '\n';
    print_helper(root);
    std::cout << '\n';
}


void Tree::remove(size_t index){
    std::cout << "." << '\n';
}