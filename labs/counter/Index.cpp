#include "Index.h"
#include <functional>

// Index Member Functions
Index::Index(){
    capacity = 5;
    table = new List[capacity];
    count = 0;
}

Index::~Index(){
    delete [] table;
}

void Index::resize(size_t n_capacity){
    List* n_table = new List[n_capacity];
    for(size_t i = 0; i < capacity; i ++){
        Node* current = table[i].head;
        while(current){
            unsigned int index = hash_value(current->key, n_capacity);
            n_table[index].insert(current->key, current->value);
            current = current->after;
        }
        table[i].clear();
    }
    delete [] table;
    table = n_table;
    capacity = n_capacity;
}

unsigned int Index::hash_value(const std::string& key, size_t cap) const{
    std::hash<std::string> hasher;
    unsigned int temp = hasher(key);
    return temp % cap;
}

void Index::table_insert(const std::string& key, int value){
    unsigned int index = hash_value(key, capacity);
    table[index].insert(key, value);
    count ++;
    if(count >= capacity / 2){
        resize(capacity * 2);
    }
}

Node* Index::table_lookup(const std::string& key) const{
    unsigned int index = hash_value(key, capacity);
    return table[index].lookup(key);
}

void Index::table_remove(const std::string& key){
    unsigned int index = hash_value(key, capacity);
    Node* target = table[index].lookup(key);
    if(target){
        table[index].remove(target);
        count --;
    }
}

