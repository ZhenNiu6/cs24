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
    Index();
    ~Index();
    size_t get_count() const;
    void resize(size_t n_cap);
    unsigned int hash_value(const std::string& key, size_t cap) const;
    void insert(Node* node);
    Node* lookup(const std::string& key) const;
    void remove(Node* node);
};

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

#endif
