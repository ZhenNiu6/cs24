#include "Counter.h"
#include <iostream>

// Counter Member Functions
Counter::Counter(){}
Counter::~Counter(){}

size_t Counter::count() const{
    Node* current = list.head;
    size_t num = 0;
    while(current){
        num ++;
        current = current->after;
    }
    return num;
}

int Counter::total() const{
    Node* current = list.head;
    int num = 0;
    while(current){
        num += current->value;
        current = current->after;
    }
    return num;
}

void Counter::inc(const std::string& key, int by){
    Node* target = index.table_lookup(key);
    if(target){
        target->value += by;
    }
    else{
        list.insert(key, by);
        index.table_insert(key, by);
    }
}

void Counter::dec(const std::string& key, int by){
    Node* target = index.table_lookup(key);
    if(target){
        target->value -= by;
    }
    else{
        list.insert(key, -by);
        index.table_insert(key, -by);
    }
}

void Counter::del(const std::string& key){
    Node* target = index.table_lookup(key);
    if(target){
        list.remove(target);
        index.table_remove(target->key);
    }
}

int Counter::get(const std::string& key) const{
    Node* target = index.table_lookup(key);
    if(target){
        return target->value;
    }
    else{
        return 0;
    }
}

void Counter::set(const std::string& key, int count){
    Node* target = index.table_lookup(key);
    // Node* target = list.lookup(key);
    if(target){
        target->value = count;
    }
    else{
        // list.insert(key, count);
        index.table_insert(key, count);
    }
}


Counter::Iterator::Iterator(Node* node){
    itr = node;
}

const std::string& Counter::Iterator::key() const{
    return itr->key;
}

int Counter::Iterator::value() const{
    return itr->value;
}

void Counter::Iterator::operator ++(){
    itr = itr->after;
}

bool Counter::Iterator::operator == (const Iterator& other) const{
    if(itr == other.itr){
        return true;
    }
    else{
        return false;
    }
}

bool Counter::Iterator::operator != (const Iterator& other) const{
    if(itr != other.itr){
        return true;
    }
    else{
        return false;
    }
}

Counter::Iterator Counter::begin() const{
    return Iterator(list.head);
}

Counter::Iterator Counter::end() const{
    return Iterator(nullptr);
}