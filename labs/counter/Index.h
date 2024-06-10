#ifndef INDEX_H
#define INDEX_H

#include <cstddef>
#include <functional>
#include <string>
#include <iostream>

#include "List.h"

class Index {

public:

    size_t iCount;
    size_t iCapacity;
    Node** index_list;

    Index();
    ~Index();
    size_t hash_map(string input, size_t iCapacity) const;
    void reinsert(Node* current, Node** list);
    void resize();
    void hash_insert(Node* current);
    Node* hash_find(string input) const;
    void hash_delete(Node* current);

};

#endif