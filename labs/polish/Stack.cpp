#include "Stack.h"

// Implement your Stack member functions here.

stack::stack() {
    mycapacity = 4;
    mylength = 0;
    mStack = new Node*[mycapacity];
}

stack::~stack() {
    for(size_t i = 0; i < mylength; ++i) {
        delete mStack[i];
    }
    delete [] mStack;
}

Node* stack::pop() {
    Node** temp = new Node*[mycapacity];
    for(size_t i = 0; i < mylength - 1; ++i) {
        temp[i] = mStack[i];
    }
    Node* target = mStack[mylength - 1];
    mylength -= 1;
    delete [] mStack;
    mStack = temp;
    return target;
}

void stack::push(Node* current) {
    if(mycapacity == mylength) {
        mycapacity *= 2;
    }
    Node** temp = new Node*[mycapacity];
    for(size_t i = 0; i < mylength; ++i) {
        temp[i] = mStack[i];
    }
    temp[mylength] = current;
    mylength += 1;
    delete [] mStack;
    mStack = temp;
}

size_t stack::return_capacity() {
    return mycapacity;
}

size_t stack::return_length() {
    return mylength;
}
