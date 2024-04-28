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
    std::cout << "." << '\n';
}

size_t Tree::count() const{
    return num;
}

bool Tree::contains(const std::string& s) const{
    Node* node = root;
    return contains_helper(node, s);
}

size_t Tree::find(const std::string& s) const{
    return 1;
}

std::string Tree::lookup(size_t index) const{
    return "";
}

void Tree::insert(const std::string& s){
    if(root == nullptr){
        root = new Node(s);
    }
    else{
        insert_helper(root, s);
    }
    

}

void Tree::print() const{
    std::cout << root->value << '\n';
    print_helper(root);
    std::cout << '\n';
}


void Tree::remove(size_t index){
    std::cout << "." << '\n';
}