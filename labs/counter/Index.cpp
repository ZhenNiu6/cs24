#include "Index.h"
#include <functional>

// Index Member Functions
Index::Index(){
    capacity = 100;
    table = new List[capacity];
    // for(size_t i = 0; i < capacity; i ++){
    //     table[i] = List();
    // }
}

Index::~Index(){
    delete [] table;
}

unsigned int Index::hash_value(const std::string& key) const{
    std::hash<std::string> hasher;
    unsigned int temp = hasher(key);
    return temp % capacity;
}

void Index::table_insert(const std::string& key, int value){
    unsigned int index = hash_value(key);
    table[index].insert(key, value);
}

Node* Index::table_lookup(const std::string& key) const{
    unsigned int index = hash_value(key);
    return table[index].lookup(key);
}

void Index::table_remove(const std::string& key){
    unsigned int index = hash_value(key);
    Node* target = table[index].lookup(key);
    if(target){
        table[index].remove(target);
    }
    
}

