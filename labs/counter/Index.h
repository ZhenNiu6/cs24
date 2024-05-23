#ifndef INDEX_H
#define INDEX_H

#include "List.h"

// TODO...
class Index{
    size_t capacity;
    Node** table;
    // Node** c_table;
    size_t count;
    int c_table[52];
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
    void inc_char(char c);
    void dec_char(char c);
    int get_char(char c) const;
    void del_char(char c);
    
};


#endif
