#include "Index.h"
#include <functional>
#include <iostream>

// Index Member Functions
Index::Index(){
    capacity = 3;
    table = new List[capacity];
    // table = new Node*[capacity]();
    count = 0;
}

Index::~Index(){
    // for(size_t i = 0; i < count; i ++){
    //     delete table[i];
    // }
    delete [] table;
}

size_t Index::get_count() const{
    return count;
}

void Index::resize(size_t n_capacity){
    List* n_table = new List[n_capacity];
    count = 0;
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

// void Index::resize(size_t n_capacity){
//     Node** n_table = new Node*[n_capacity];
//     count = 0;
//     for(size_t i = 0; i < capacity; i ++){
//         Node* current = table[i];
//         while(current){
//             unsigned int index = hash_value(current->key, current->value);
//             Node* next = current->after;
//             current->after = nullptr;
//             current->before = nullptr;
//             if(n_table[index]){
//                 n_table[index]->before = current;
//             }
//             current->after = n_table[index];
//             n_table[index] = current;
//             current = next;
//             count ++;
//         }
//     }
//     delete [] table;
//     table = n_table;
//     capacity = n_capacity;
// }

unsigned int Index::hash_value(const std::string& key, size_t cap) const{
    std::hash<std::string> hasher;
    unsigned int temp = hasher(key);
    return temp % cap;
}

void Index::table_insert(const std::string& key, int value){
    unsigned int index = hash_value(key, capacity);
    table[index].insert(key, value);
    // Node* node = new Node(key, value);
    // node->after = table[index];
    // if(table[index]){
    //     table[index]->before = node;
    // }
    // table[index] = node;
    count ++;
    if(count > capacity * 0.7){
        resize(capacity * 2);
    }
}

Node* Index::table_lookup(const std::string& key) const{
    unsigned int index = hash_value(key, capacity);
    return table[index].lookup(key);
    // Node* current = table[index];
    // while(current){
    //     if(current->key == key){
    //         return current;
    //     }
    //     current = current->after;
    // }
    // return nullptr;
}

void Index::table_remove(const std::string& key){
    // std::cout << "1" << '\n';
    unsigned int index = hash_value(key, capacity);
    Node* target = table[index].lookup(key);
    if(target){
        table[index].remove(target);
        count --;
    }
    // Node* current = table[index];
    // while(current){
    //     if(current->key == key){
    //         // std::cout << "1" << '\n';
    //         if(current->before){
    //             current->before->after = current->after;
    //             // std::cout << "2" << '\n';
    //         }
    //         else{
    //             table[index] = current->after;
    //             // std::cout << "3" << '\n';
    //         }
    //         if(current->after){
    //             current->after->before = current->before;
    //             // std::cout << "4" << '\n';
    //         }
    //         delete current;
    //         // std::cout << "5" << '\n';
    //         count --;
    //         // std::cout << "count - 1" << '\n';
    //         return;
    //     }
    //     current = current->after;
    // }
}

