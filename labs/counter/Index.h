#ifndef INDEX_H
#define INDEX_H

#include "List.h"

// TODO...
class Index{
    size_t capacity;
    Node** table;
    size_t count;
    

public:
    mutable Node* last;
    // Index();
    // ~Index();
    // size_t get_count() const;
    // void resize(size_t n_cap);
    // unsigned int hash_value(const std::string& key, size_t cap) const;
    // void insert(Node* node);
    // Node* lookup(const std::string& key) const;
    // void remove(Node* node);
    Index(){
    capacity = 524288;
    table = new Node*[capacity]();
    count = 0;
    last = nullptr;
}

~Index(){
    delete [] table;
}

size_t get_count() const{
    return count;
}

void resize(size_t n_cap){
    Node** n_table = new Node*[n_cap]();
    size_t o_cap = capacity;
    capacity = n_cap;
    for(size_t i = 0; i < o_cap; i ++){
        Node* current = table[i];
        while(current){
            Node* x = current->next;
            unsigned int index = hash_value(current->key, n_cap);
            current->next = n_table[index];
            n_table[index] = current;
            current = x;
        }
    }
    delete [] table;
    table = n_table;
}

void insert(Node* node){
    unsigned int index = hash_value(node->key, capacity);
    if(!table[index]){
        table[index] = node;
    }
    else{
        node->next = table[index];
        table[index] = node;
    }
    count ++;
    if(count > capacity * 0.7){
        resize(capacity * 2);
    }
}

Node* lookup(const std::string& key) const{
    if(last){
        if(last->key == key){
            return last;
        }
    }
    unsigned int index = hash_value(key, capacity);
    Node* current = table[index];
    while(current){
        if(current->key == key){
            last = current;
            return current;
        }
        current = current->next;
    }
    last = nullptr;
    return nullptr;
}

void remove(Node* node){
    unsigned int index = hash_value(node->key, capacity);
    Node* current = table[index];
    // if(!current){
    //     return;
    // }
    if(current == node){
        table[index] = current->next;
    }
    else{
        while(current){
            if(current->next == node){
                current->next = node->next;
                break;
            }
            current = current->next;
        }
    }
    node->next = nullptr;
    // Node* follow = current->next;
    // while(current){
    //     follow = current->next;
    //     if(current == node){
    //         if(current == table[index]){
    //             table[index] = follow;
                
    //         }
    //         else{
    //             Node* traverse = table[index];
    //             while(traverse){
    //                 if(traverse->next == current){
    //                     traverse->next = follow;
    //                     break;
    //                 }
    //                 traverse = traverse->next;
    //             }  
    //         }
    //         count --;
    //         return;
    //     }
    //     current = current->next;
    // }
}



unsigned int hash_value(const std::string& key, size_t cap) const {
    const unsigned int fnv_prime = 0x01000193;
    const unsigned int offset_basis = 0x811C9DC5;
    unsigned int hash = offset_basis;

    for (size_t i = 0; i < key.size(); ++i) {
        hash ^= static_cast<unsigned char>(key[i]);
        hash *= fnv_prime;
    }

    return hash & (cap-1);
    // return hash % cap;
}
};


#endif
