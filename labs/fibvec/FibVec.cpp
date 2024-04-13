#include "FibVec.h"

// This provides exception types:
#include <stdexcept>



// FibVec Function Implementations
FibVec::FibVec(){
    num = 0;
    cap = 1;
    n = 2;
    fibs = new int[cap];
}

FibVec::FibVec(const FibVec& other){
    num = other.num;
    cap = other.cap;
    n = other.n;
    fibs = new int[cap];
    for(size_t i = 0; i < num; i ++){
        fibs[i] = other.fibs[i];
    }
}


FibVec::~FibVec(){
    delete [] fibs;
}

size_t FibVec::capacity() const{
    return cap;
}

size_t FibVec::count() const{
    return num;
}

void FibVec::insert(int value, size_t index){
    if(num != 0){
        if(index >= num){
            throw std::out_of_range("insert()");
        }
    }
    if(index > num){
        throw std::out_of_range("insert()");
    }
    size_t n_cap = cap;
    if((num+1) > cap){
        n_cap = fib(n+1);
        n ++;
    }
    int* temp = new int[n_cap];
    if(num == 0){
        temp[index] = value;
        num ++;
    }
    else{
        for(size_t i = 0; i < index; i ++){
            temp[i] = fibs[i];
        }
        temp[index] = value;
        num ++;
        for(size_t i = index + 1; i < num; i ++){
            temp[i] = fibs[i-1];
        }
    }
    delete [] fibs;
    fibs = temp;
    cap = n_cap;
}

int FibVec::lookup(size_t index) const{
    if(index >= num){
        throw std::out_of_range("lookup()");
    }
    return fibs[index];
}

int FibVec::pop(){
    if(num == 0){
        throw std::underflow_error("pop()");
    }
    size_t n_cap = cap;
    if(n >= 2){
        if((num - 1) < fib(n-2)){
            n_cap = fib(n-1);
            n --;
        }
    }
    int* temp = new int[n_cap];
    for(size_t i = 0; i < num - 1; i ++){
        temp[i] = fibs[i];
    }
    int value = fibs[num-1];
    delete [] fibs;
    fibs = temp;
    cap = n_cap;
    num --;
    return value;
}

void FibVec::push(int value){
    size_t n_cap = cap;
    if(num == cap){
        n_cap = fib(n+1);
        n ++;
    }
    int* temp = new int[n_cap];
    for(size_t i = 0; i < num; i ++){
        temp[i] = fibs[i];
    }
    temp[num] = value;
    delete [] fibs;
    fibs = temp;
    cap = n_cap;
    num ++;
}

int FibVec::remove(size_t index){
    if(index >= num){
        throw std::out_of_range("remove()");
    }
    size_t n_cap = cap;
    if(n >= 2){
        if((num - 1) < fib(n-2)){
            n_cap = fib(n-1);
            n --;
        }
    }
    int* temp = new int[n_cap];
    for(size_t i = 0; i < index; i ++){
        temp[i] = fibs[i];
    }
    int value = fibs[index];
    for(size_t i = index; i < num; i ++){
        temp[i] = fibs[i+1];
    }
    delete [] fibs;
    fibs = temp;
    cap = n_cap;
    num --;
    return value;

}