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


size_t Tree::count() const{
    return num;
}


// bool Tree::contains(const std::string& s) const{
    
// }

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