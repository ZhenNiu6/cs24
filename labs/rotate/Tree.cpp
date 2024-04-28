#include "Tree.h"
#include <iostream>

// Tree Function Implementations
Tree::Tree(){
    root = nullptr;
    num = 0;
}

Tree::~Tree(){
    clear();
    root = nullptr;
}

void Tree::clear(){
    if(root != nullptr){
        clear_helper(root);
    }
    root = nullptr;
    num = 0;
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
    if(index >= num){
        throw std::out_of_range("index");
    }
    if(root == nullptr){
        throw std::out_of_range("null");
    }
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



void Tree::print() const{
    // std::cout << root->value << '\n';
    print_helper(root);
    std::cout << '\n';
}


void Tree::remove(size_t index){
    std::cout << "." << '\n';
}