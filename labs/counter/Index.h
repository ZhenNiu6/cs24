#ifndef INDEX_H
#define INDEX_H

#include "List.h"

// TODO...
class Index{
    size_t capacity;
    Node** table;
    size_t count;

public:
    Index();
    ~Index();
    size_t get_count() const;
    void resize(size_t n_capacity);
    unsigned int hash_value(const std::string& key, size_t cap) const;
    void insert(const std::string& node_key, int node_value);
    Node* lookup(const std::string& key) const;
    void remove(const std::string& key);
};


#endif
