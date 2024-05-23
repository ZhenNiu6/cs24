#ifndef COUNTER_H
#define COUNTER_H

#include <cstddef>
#include <string>
#include "List.h"
#include "Index.h"

// This is the Counter class you need to implement.
// It includes the Counter::Iterator as a nested class.

class Counter {
public:
  class Iterator {
    // Member Variables

  public:
    Node* itr;

    // Iterator(Node* node);
    // const std::string& key() const;
    // int value() const;

    // void operator ++ ();
    // bool operator == (const Iterator& other) const;
    // bool operator != (const Iterator& other) const;

    Iterator(Node* node){
    itr = node;
}

const std::string& key() const{
    return itr->key;
}

int value() const{
    return itr->value;
}

void operator ++(){
    itr = itr->after;
}

bool operator == (const Iterator& other) const{
    if(itr == other.itr){
        return true;
    }
    else{
        return false;
    }
}

bool operator != (const Iterator& other) const{
    if(itr != other.itr){
        return true;
    }
    else{
        return false;
    }
}



  };

private:
  // Member Variables
  List list;
  Index index;
  size_t mCount;
  size_t mTotal;

private:
  // Helper Functions

public:
  // Counter();
  // ~Counter();

  // size_t count() const;
  // int    total() const;

  // void inc(const std::string& key, int by = 1);
  // void dec(const std::string& key, int by = 1);
  // void del(const std::string& key);
  // int  get(const std::string& key) const;
  // void set(const std::string& key, int count);

////


Counter(){
    mCount = 0;
    mTotal = 0;
}
~Counter(){}

size_t count() const{
    return mCount;
}

int total() const{
    return mTotal;
}

void inc(const std::string& key, int by){
    Node* target = index.lookup(key);
    if(target){
        target->value += by;
    }
    else{
        Node* x = new Node(key, by);
        list.insert(x);
        index.insert(x);
        mCount ++;
    }
    mTotal += by;
}

void dec(const std::string& key, int by){
    Node* target = index.lookup(key);
    if(target){
        target->value -= by;
    }
    else{
        Node* x = new Node(key, -by);
        list.insert(x);
        index.insert(x);
        mCount ++;
    }
    mTotal -= by;
}

void del(const std::string& key){
    Node* target = index.lookup(key);
    if(target){
        mTotal -= target->value;
        index.remove(target);
        list.remove(target);
        mCount --;
        index.last = nullptr;
    }
}

int get(const std::string& key) const{
    Node* target = index.lookup(key);
    if(target){
        return target->value;
    }
    else{
        return 0;
    }
}

void set(const std::string& key, int count){
    Node* target = index.lookup(key);
    if(target){
        mTotal -= target->value;
        target->value = count;
        mTotal += count;
    }
    else{
        Node* x = new Node(key, count);
        list.insert(x);
        index.insert(x);
        mCount ++;
        mTotal += count;
    }
}
  // Iterator begin() const;
  // Iterator end() const;

  Iterator begin() const{
    return Iterator(list.head);
}

  Iterator end() const{
    return Iterator(nullptr);
}


};

#endif
