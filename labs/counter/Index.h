#ifndef INDEX_H
#define INDEX_H

#include "List.h"

// TODO...
class Index{
    size_t capacity;
    Node** table;
    // Node** c_table;
    size_t count;
    // size_t c_count;
    

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


#endif
