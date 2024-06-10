#include "Index.h"
#include "List.h"

Index::Index() {
    iCount = 0;
    iCapacity = 2;
    index_list = new Node*[iCapacity]();
}

Index::~Index() {
    delete [] index_list;
}

size_t Index::hash_map(string input, size_t iCapacity) const {
    size_t result = hash<string>{}(input);
    return result % iCapacity;
}

void Index::reinsert(Node* current, Node** list) {
    if(current->hash_after != nullptr) {
        reinsert(current->hash_after, list);
    }
    current->hash_after = nullptr;
    size_t hash_value = hash_map(current->mKey, iCapacity);
    if(index_list[hash_value] == nullptr) {
        index_list[hash_value] = current;
    }
    else {
        current->hash_after = index_list[hash_value];
        index_list[hash_value] = current;
    }
}

void Index::resize() {
    iCapacity *= 2;
    Node** old = index_list;
    index_list = new Node*[iCapacity]();
    for(size_t i = 0; i < iCapacity / 2; ++i) {       
        if(old[i] != nullptr) {
            reinsert(old[i], index_list);
        }
    }
    delete [] old;
}

void Index::hash_insert(Node* current) {
    size_t hash_value = hash_map(current->mKey, iCapacity);
    if(index_list[hash_value] == nullptr) {
        index_list[hash_value] = current;
    }
    else {
        current->hash_after = index_list[hash_value];
        index_list[hash_value] = current;
    }
    iCount += 1;
    if(iCount == iCapacity * 0.5) {
        resize();
    }
}

Node* Index::hash_find(string input) const {
    size_t hash_value = hash_map(input, iCapacity);
    Node* hash_start = index_list[hash_value];
    while(hash_start != nullptr) {
        if(hash_start->mKey == input) {
            return hash_start;
        }
        hash_start = hash_start->hash_after;
    }
    return nullptr;
}

void Index::hash_delete(Node* current) {
    size_t hash_value = hash_map(current->mKey, iCapacity);
    Node* hash_start = index_list[hash_value];
    if(hash_start == current) {
        index_list[hash_value] = hash_start->hash_after;
    }
    else {
        while(hash_start != nullptr) {
            if(hash_start->hash_after == current) {
                hash_start->hash_after = current->hash_after;
                break;
            }
            hash_start = hash_start->hash_after;
        }
    }
    current->hash_after = nullptr;
}