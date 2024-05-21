#include "Counter.h"
#include <iostream>

// Counter Member Functions
Counter::Counter(){
    mCount = 0;
    mTotal = 0;
}
Counter::~Counter(){}

size_t Counter::count() const{
    // Node* current = list.head;
    // size_t num = 0;
    // while(current){
    //     num ++;
    //     current = current->after;
    // }
    // return num;
    return mCount;
}

int Counter::total() const{
    // Node* current = list.head;
    // int num = 0;
    // while(current){
    //     num += current->value;
    //     current = current->after;
    // }
    // return num;
    return mTotal;
}

void Counter::inc(const std::string& key, int by){
    Node* target = index.table_lookup(key);
    if(target){
        target->value += by;
    }
    else{
        list.insert(key, by);
        index.table_insert(key, by);
        mCount ++;
    }
    mTotal += by;
    // std::cout << "inc: key=" << key << ", by=" << by << ", mTotal=" << mTotal << std::endl;
}

void Counter::dec(const std::string& key, int by){
    Node* target = index.table_lookup(key);
    if(target){
        target->value -= by;
    }
    else{
        list.insert(key, -by);
        index.table_insert(key, -by);
        mCount ++;
    }
    mTotal -= by;
    // std::cout << "dec: key=" << key << ", by=" << by << ", mTotal=" << mTotal << std::endl;
}

void Counter::del(const std::string& key){
    Node* target = index.table_lookup(key);
    if(target){
        mTotal -= target->value;
        // list.remove(target);
        index.table_remove(target->key);
        mCount --;
    }
    // std::cout << "del: key=" << key << ", mTotal=" << mTotal << std::endl;
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
        mTotal -= target->value;
        target->value = count;
        mTotal += count;
    }
    else{
        list.insert(key, count);
        // std::cout << "here" << '\n';
        index.table_insert(key, count);
        // std::cout << "here2" << '\n';
        mCount ++;
        mTotal += count;
    }
    // std::cout << "set: key=" << key << ", count=" << count << ", mTotal=" << mTotal << std::endl;
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