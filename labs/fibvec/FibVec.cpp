#include "FibVec.h"

// This provides exception types:
#include <stdexcept>
#include <iostream>

// FibVec Function Implementations

using namespace std;

FibVec::FibVec() {

    mycapacity = 1;
    mylength = 0;
    myvector = new int[mycapacity];

}

FibVec::~FibVec() {

    delete [] myvector;

}

size_t FibVec::capacity() const {

    return mycapacity;

}

size_t FibVec::count() const {
    
    return mylength;

}

void FibVec::insert(int value, size_t index) {

    if(index > mylength) {
        throw out_of_range("insert()");
    }
    else {
        if(mycapacity == mylength) {
            size_t result = add(mycapacity);
            mycapacity = result;
        }
        int* temp = new int[mycapacity];
        size_t original = 0;
        for(size_t i = 0; i < mylength + 1; ++i) {
            if(i == index) {
                temp[i] = value;
            }
            else {
                temp[i] = myvector[original];
                original += 1;
            }
        }
        mylength += 1;
        delete [] myvector;
        myvector = temp;
    }

}

int FibVec::lookup(size_t index) const {

    if(index >= mylength) {
        throw out_of_range("lookup()");
    }
    else {
        int result = myvector[index];
        return result;
    }

}

int FibVec::pop() {

    if(mylength == 0) {
        throw underflow_error("pop()");
    }
    else {
        int result = myvector[mylength - 1];
        size_t middle = substract(mycapacity);
        size_t target = substract(middle);
        if(mylength - 1 < target) {
            mycapacity = middle;
            int* temp = new int[mycapacity];
            for(size_t i = 0; i < mylength - 1; ++i) {
                temp[i] = myvector[i];
            }
            mylength -= 1;
            delete [] myvector;
            myvector = temp;
            return result;
        }
        else {
            int* temp = new int[mycapacity];
            for(size_t i = 0; i < mylength - 1; ++i) {
                temp[i] = myvector[i];
            }
            mylength -= 1;
            delete [] myvector;
            myvector = temp;
            return result;
        } 
    }

}

void FibVec::push(int value) {

    if(mycapacity == mylength) {
        size_t result = add(mycapacity);
        mycapacity = result;
        int* temp = new int[mycapacity];
        for(size_t i = 0; i < mylength; ++i) {
            temp[i] = myvector[i];
        }
        temp[mylength] = value;
        mylength += 1;
        delete [] myvector;
        myvector = temp;
    }
    else {
        int* temp = new int[mycapacity];
        for(size_t i = 0; i < mylength; ++i) {
            temp[i] = myvector[i];
        }
        temp[mylength] = value;
        mylength += 1;
        delete [] myvector;
        myvector = temp;
    }

}

int FibVec::remove(size_t index) {

    if(index >= mylength) {
        throw out_of_range("remove()");
    }
    else {
        int result = myvector[index];
        size_t middle = substract(mycapacity);
        size_t target = substract(middle);
        if(mylength - 1 < target) {
            mycapacity = middle;
        }
        int* temp = new int[mycapacity];
        for(size_t i = 0; i < index; ++i) {
            temp[i] = myvector[i];
        }
        for(size_t i = index + 1; i < mylength; ++i) {
            temp[i - 1] = myvector[i];
        }
        mylength -= 1;
        delete [] myvector;
        myvector = temp;
        return result;
    }

}

size_t FibVec::add(size_t currentcapacity) const {

    size_t first = 1;
    size_t second = 2;
    size_t temp = 0;

    if(currentcapacity == 1) {
        return 2;
    }
    else if(currentcapacity == 2) {
        return 3;
    }
    else {
        while(currentcapacity != first && currentcapacity > first) {
            temp = first + second;
            first = second;
            second = temp;
            temp = 0;
        }
        return second;
    }
    return second;

}

size_t FibVec::substract(size_t currentcapacity) const {

    size_t first = 1;
    size_t second = 2;
    size_t temp = 0;

    if(currentcapacity == 2) {
        return 1;
    }
    else {
        while(currentcapacity != second && currentcapacity > second) {
            temp = first + second;
            first = second;
            second = temp;
            temp = 0;
        }
        return first;
    }
    return first;

}
