#include "Heap.h"
#include <utility>
#include <stdexcept>

Heap::Heap(size_t capacity){
    mCapacity = capacity;
    mCount = 0;
    mData = new Entry[mCapacity];
}

Heap::Heap(const Heap& other){
    mCapacity = other.mCapacity;
    mCount = other.mCount;
    mData = new Entry[mCapacity];
    for(size_t i = 0; i < mCount; i ++){
        mData[i] = other.mData[i];
    }
}

Heap::~Heap(){
    delete [] mData;
}

size_t Heap::capacity() const{
    return mCapacity;
}

size_t Heap::count() const{
    return mCount;
}

const Heap::Entry& Heap::lookup(size_t index) const{
    if(index >= mCount){
        throw std::out_of_range("");
    }
    return mData[index];
}

Heap::Entry Heap::pop(){
    if(mCount == 0){
        throw std::underflow_error("");
    }
    Entry smallest = mData[0];
    mData[0] = mData[mCount - 1]; // replaced the root by the last entry
    mCount --;
    size_t l_index = 1;
    size_t r_index = 2;
    size_t p_index = 0;
    while(l_index < mCount){ // l_index is valid
        int smaller = l_index;
        if((r_index < mCount) && (mData[r_index].score < mData[l_index].score)){ // r_index is valid
            smaller = r_index; // right child is smaller
        }
        if(mData[smaller].score < mData[p_index].score){
            std::swap(mData[smaller], mData[p_index]); // swap with the smaller child
            p_index = smaller;
            l_index = smaller * 2 + 1;
            r_index = smaller * 2 + 2;
        }
        else{ // parent is smaller than both children
            break;
        }
    }
    return smallest;
}

Heap::Entry Heap::pushpop(const std::string& value, float score){
    if(mCount == 0){
        throw std::underflow_error("");
    }
    Entry smallest = mData[0];
    mData[0].value = value;
    mData[0].score = score;
    size_t l_index = 1;
    size_t r_index = 2;
    size_t p_index = 0;
    while(l_index < mCount){ // l_index is valid
        int smaller = l_index;
        if((r_index < mCount) && (mData[r_index].score < mData[l_index].score)){ // r_index is valid
            smaller = r_index; // right child is smaller
        }
        if(mData[smaller].score < mData[p_index].score){
            std::swap(mData[smaller], mData[p_index]); // swap with the smaller child
            p_index = smaller;
            l_index = smaller * 2 + 1;
            r_index = smaller * 2 + 2;
        }
        else{ // parent is smaller than both children
            break;
        }
    }
    return smallest;
}

void Heap::push(const std::string& value, float score){
    if(mCount == mCapacity){
        throw std::overflow_error("");
    }
    mData[mCount].value = value;
    mData[mCount].score = score;
    size_t c_index = mCount;
    size_t p_index = (c_index - 1) / 2;
    if(c_index == 0){ // No parent
        mCount ++;
        return;
    }
    while((c_index > 0) && (mData[p_index].score > mData[c_index].score)){
        std::swap(mData[c_index], mData[p_index]);
        c_index = p_index;
        p_index = (c_index - 1) / 2;
    }
    mCount ++;
}

const Heap::Entry& Heap::top() const{
    if(mCount == 0){
        throw std::underflow_error("");
    }
    return mData[0];
}