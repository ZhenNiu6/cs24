#include "Index.h"
#include <functional>
#include <iostream>

// Index Member Functions

Index::Index(){
    capacity = 8;
    table = new Node*[capacity]();
    count = 0;
}

Index::~Index(){
    delete [] table;
}

size_t Index::get_count() const{
    return count;
}

void Index::resize(size_t n_cap){
    Node** n_table = new Node*[n_cap];
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

void Index::insert(const std::string& key, int value){
    unsigned int index = hash_value(key, capacity);
    Node* node = new Node(key, value);
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

Node* Index::lookup(const std::string& key) const{
    unsigned int index = hash_value(key, capacity);
    Node* current = table[index];
    while(current){
        if(current->key == key){
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void Index::remove(const std::string& key){
    unsigned int index = hash_value(key, capacity);
    Node* current = table[index];
    Node* prev = nullptr;
    while(current){
        if(current->key == key){
            if(prev){
                prev->next = current->next;
            }
            else{
                table[index] = current->next;
            }
            delete current;
            count --;
            return;
        }
        prev = current;
        current = current->next;
    }
}



// Index::Index(){
//     capacity = 982451653;
//     table = new Node*[capacity]();
//     count = 0;
// }

// Index::~Index(){
//     for(size_t i = 0; i < capacity; i ++){
//         if(table[i]){
//             if(table[i]->key == "already dirty"){
//                 delete table[i];
//             }
//         }
//     }
//     delete [] table;
// }


// size_t Index::get_count() const{
//     return count;
// }

// void Index::remove(const std::string& key){
//     unsigned int index = hash_value(key, capacity);
//     for(size_t i = 0; i < capacity; i ++){
//         unsigned int probe = (index + i*i) % capacity;
//         // dirty or nullptr
//         if(!table[probe]){
//             return;
//         }
//         if(table[probe]->key == key){
//             delete table[probe];
//             Node* occupy = new Node("already dirty", 0);
//             table[probe] = occupy;
//             count --;
//         }
//     }
// }


// void Index::insert(const std::string& node_key, int node_value){
//     unsigned int index = hash_value(node_key, capacity);
//     for(size_t i = 0; i < capacity; i ++){
//         unsigned int probe = (index + i*i) % capacity;
//         if(!table[probe]){
//             Node* node = new Node(node_key, node_value);
//             table[probe] = node;
//             count ++;
//             if(count > capacity * 0.7){
//                 resize(capacity * 2);
//             }
//             break;
//         }
//     }
// }


// void Index::resize(size_t n_cap){
//     Node** n_table = new Node*[n_cap]();
//     size_t o_cap = capacity;
//     capacity = n_cap;
//     for(size_t i = 0; i < o_cap; i ++){
//         Node* current = table[i];
//         if(current){
//             if(n_table[i]->key == "already dirty"){
//                 delete n_table[i];
//                 continue;
//             }
//             unsigned int index = hash_value(current->key, n_cap);
//             for(size_t j = 0; j < n_cap; j ++){
//                 unsigned int probe = (index + j*j) % n_cap;
//                 if(!n_table[probe]){
//                     n_table[probe] = current;
//                     break;
//                 }
//             }
//         }
//     }
//     delete [] table;
//     table = n_table;
// }


// Node* Index::lookup(const std::string& key) const{
//     unsigned int index = hash_value(key, capacity);
//     for(size_t i = 0; i < capacity; i ++){
//         unsigned int probe = (index + i*i) % capacity;
//         if(!table[probe]){
//             return nullptr;
//         }
//         else{
//             if(table[probe]->key == key){
//                 return table[probe];
//             }
//         }
//     }
//     return nullptr;
// }


unsigned int Index::hash_value(const std::string& key, size_t cap) const{
    std::hash<std::string> hasher;
    unsigned int temp = hasher(key);
    return temp % cap;
}

// void Index::table_insert(const std::string& key, int value){
//     unsigned int index = hash_value(key, capacity);
//     table[index].insert(key, value);
//     // Node* node = new Node(key, value);
//     // node->after = table[index];
//     // if(table[index]){
//     //     table[index]->before = node;
//     // }
//     // table[index] = node;
//     count ++;
//     if(count > capacity * 0.7){
//         resize(capacity * 2);
//     }
// }

// Node* Index::table_lookup(const std::string& key) const{
//     unsigned int index = hash_value(key, capacity);
//     return table[index].lookup(key);
//     // Node* current = table[index];
//     // while(current){
//     //     if(current->key == key){
//     //         return current;
//     //     }
//     //     current = current->after;
//     // }
//     // return nullptr;
// }

// void Index::table_remove(const std::string& key){
//     unsigned int index = hash_value(key, capacity);
//     Node* target = table[index].lookup(key);

//     if(target){
//         table[index].remove(target);
//         count --;
//     }
//     // Node* current = table[index];
//     // while(current){
//     //     if(current->key == key){
//     //         // std::cout << "1" << '\n';
//     //         if(current->before){
//     //             current->before->after = current->after;
//     //             // std::cout << "2" << '\n';
//     //         }
//     //         else{
//     //             table[index] = current->after;
//     //             // std::cout << "3" << '\n';
//     //         }
//     //         if(current->after){
//     //             current->after->before = current->before;
//     //             // std::cout << "4" << '\n';
//     //         }
//     //         delete current;
//     //         // std::cout << "5" << '\n';
//     //         count --;
//     //         // std::cout << "count - 1" << '\n';
//     //         return;
//     //     }
//     //     current = current->after;
//     // }
// }


// // void Index::resize(size_t n_capacity){
// //     Node** n_table = new Node*[n_capacity];
// //     count = 0;
// //     for(size_t i = 0; i < capacity; i ++){
// //         Node* current = table[i];
// //         while(current){
// //             unsigned int index = hash_value(current->key, current->value);
// //             Node* next = current->after;
// //             current->after = nullptr;
// //             current->before = nullptr;
// //             if(n_table[index]){
// //                 n_table[index]->before = current;
// //             }
// //             current->after = n_table[index];
// //             n_table[index] = current;
// //             current = next;
// //             count ++;
// //         }
// //     }
// //     delete [] table;
// //     table = n_table;
// //     capacity = n_capacity;
// // }

