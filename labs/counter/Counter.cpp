#include "Counter.h"
#include <iostream>

// Counter Member Functions
Counter::Counter(){
    mCount = 0;
    mTotal = 0;
}
Counter::~Counter(){}

size_t Counter::count() const{
    return mCount;
}

int Counter::total() const{
    return mTotal;
}

void Counter::inc(const std::string& key, int by){
    if((key.size() == 1) && (isalpha(key[0]))){
        index.inc_char(key[0]);
        mCount ++;
        mTotal += by;
        return;
    }
    Node* target = index.lookup(key);
    if(target){
        target->value += by;
    }
    else{
        Node* x = new Node(key, by);
        list.insert(x);
        index.insert(x);
        mCount ++;
    }
    mTotal += by;
}

void Counter::dec(const std::string& key, int by){
    if((key.size() == 1) && (isalpha(key[0]))){
        index.dec_char(key[0]);
        mCount ++;
        mTotal -= by;
        return;
    }
    Node* target = index.lookup(key);
    if(target){
        target->value -= by;
    }
    else{
        Node* x = new Node(key, -by);
        list.insert(x);
        index.insert(x);
        mCount ++;
    }
    mTotal -= by;
}

void Counter::del(const std::string& key){
    if((key.size() == 1) && (isalpha(key[0]))){
        index.del_char(key[0]);
        if(mTotal != 0){
            mTotal --;
        }
        mCount --;
        return;
    }
    Node* target = index.lookup(key);
    if(target){
        mTotal -= target->value;
        index.remove(target);
        list.remove(target);
        mCount --;
        index.last = nullptr;
    }
}

int Counter::get(const std::string& key) const{
    if((key.size() == 1) && (isalpha(key[0]))){
        // return index.get_char(key[0]);
    }
    Node* target = index.lookup(key);
    if(target){
        return target->value;
    }
    else{
        return 0;
    }
}

void Counter::set(const std::string& key, int count){
    // if((key.size() == 1) && (isalpha(key[0]))){
    //     if
    //     index.inc_char(key[0]);
    //     return;
    // }
    Node* target = index.lookup(key);
    if(target){
        mTotal -= target->value;
        target->value = count;
        mTotal += count;
    }
    else{
        Node* x = new Node(key, count);
        list.insert(x);
        index.insert(x);
        mCount ++;
        mTotal += count;
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