#ifndef INDEX_H
#define INDEX_H

#include "List.h"

// TODO...
class Index{
    size_t capacity;
    List* table;
    size_t count;

public:
    Index();
    ~Index();
    void resize(size_t n_capacity);
    unsigned int hash_value(const std::string& key, size_t cap) const;
    void table_insert(const std::string& node_key, int node_value);
    Node* table_lookup(const std::string& key) const;
    void table_remove(const std::string& key);
};


#endif
