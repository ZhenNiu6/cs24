#include "Counter.h"
#include "Index.h"

Counter::Iterator::Iterator(Node* current) {
    myitr = current;
}

const std::string& Counter::Iterator::key() const {
    return myitr->mKey;
}

int Counter::Iterator::value() const {
    return myitr->mValue;
}

void Counter::Iterator::operator ++ () {
    if(myitr != nullptr) {
        myitr = myitr->mAfter;
    }
}

bool Counter::Iterator::operator == (const Iterator& other) const {
    if(myitr == other.myitr) {
        return true;
    }
    else {
        return false;
    }
}

bool Counter::Iterator::operator != (const Iterator& other) const {
    if(myitr != other.myitr) {
        return true;
    }
    else {
        return false;
    }
}


Counter::Counter() {
    mTotal = 0;
    mCount = 0;
}

Counter::~Counter() {
    mTotal = 0;
    mCount = 0;
}

size_t Counter::count() const {
    return mCount;
}

int Counter::total() const {
    return mTotal;
}

void Counter::inc(const std::string& key, int by) {
    Node* target = myIndex.hash_find(key);
    if(target != nullptr) {
        target->mValue += by;
    }
    else {
        Node* temp = new Node(by, key);
        mylist.insert(temp);
        myIndex.hash_insert(temp);
        mCount += 1;
    }
    mTotal += by;
}

void Counter::dec(const std::string& key, int by) {
    Node* target = myIndex.hash_find(key);
    if(target != nullptr) {
        target->mValue -= by;
    }
    else {
        Node* temp = new Node(- by, key);
        mylist.insert(temp);
        myIndex.hash_insert(temp);
        mCount += 1;
    }
    mTotal -= by;
}

void Counter::del(const std::string& key) {
    Node* target = myIndex.hash_find(key);
    if(target != nullptr) {
        mTotal -= target->mValue;
        mCount -= 1;
        myIndex.hash_delete(target);
        mylist.remove(target);
    }
}

int Counter::get(const std::string& key) const {
    Node* target = myIndex.hash_find(key);
    if(target == nullptr) {
        return 0;
    }
    else {
        return target->mValue;
    }
}

void Counter::set(const std::string& key, int count) {
    Node* target = myIndex.hash_find(key);
    if(target == nullptr) {
        Node* temp = new Node(count, key);
        mylist.insert(temp);
        myIndex.hash_insert(temp);
        mCount += 1;
        mTotal += count;
        
    }
    else {
        int difference = target->mValue - count;
        mTotal -= difference;
        target->mValue = count;
    }
}

Counter::Iterator Counter::begin() const {
    return Iterator(mylist.mStart);
}

Counter::Iterator Counter::end() const {
    return Iterator(nullptr);
}