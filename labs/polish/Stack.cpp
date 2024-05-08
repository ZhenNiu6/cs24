#include "Stack.h"

#include <iostream>

// Implement your Stack member functions here.

Stack::Stack(){
    num = 0;
    cap = 2;
    tree = new Node*[cap];
}

Stack::Stack(const Stack& other){
    num = other.num;
    cap = other.cap;
    tree = new Node*[cap];
    for(size_t i = 0; i < num; i ++){
        tree[i] = other.tree[i];
    }
}

Stack::~Stack(){
    for(size_t i = 0; i < num; i ++){
        delete tree[i];
    }
    delete [] tree;
}

size_t Stack::count() const{
    return num;
}

void Stack::push(Node* node){
    size_t n_cap = cap;
    if(num == cap){
        n_cap = 2*cap;
    }
    Node** temp = new Node*[n_cap];
    for(size_t i = 0; i < num; i ++){
        temp[i] = tree[i];
    }
    temp[num] = node;
    // for(size_t i = 0; i < num; i ++){
    //     delete tree[i];
    // }
    delete [] tree;
    tree = temp;
    cap = n_cap;
    num ++;
    // std::cout << "after push " << num << '\n';
    // std::cout << "number " << node.value() << '\n';
}

Node* Stack::pop(){ 
    if(num == 0){
        throw std::runtime_error("Not enough operands.");
    }
    size_t n_cap = cap;
    Node** temp = new Node*[n_cap];
    for(size_t i = 0; i < num - 1; i ++){
        temp[i] = tree[i];
    }
    // delete tree[num-1];
    Node* x = tree[num-1];
    // for(size_t i = 0; i < num - 1; i ++){
    //     delete tree[i];
    // }
    delete [] tree;
    tree = temp;
    cap = n_cap;
    num --;
    return x;
    // std::cout << "after pop " << num << '\n';
}

// Node* Stack::top(){
//     if(num >= 1){
//         // std::cout << "num-1 " << num-1 << '\n';
//         // std::cout << "top value " << tree[num-1].value() << '\n';;
//         return tree[num-1];
//     }
//     throw std::runtime_error("No input.");
// }

// void Stack::see_top() const{
//     std::cout << "top value " << tree[num-1]->value() << '\n';
//     std::cout << "prefix " << tree[num-1]->prefix() << '\n';
//     tree[num-1]->see_var();
// }

// Node* Stack::lookup(size_t index) const{
//     if(index < num){
//         return tree[index];
//     }
//     return nullptr;
// }