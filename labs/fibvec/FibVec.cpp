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
    if(index >= num){
        throw std::out_of_range("insert()");
    }
    else{
        if((num+1) == cap){
            int* temp = new int[fib(n+1)];
            cap = fib(n+1);
            n ++;
            for(size_t i = 0; i < index; i ++){
                temp[i] = fibs[i];
            }
            for(size_t i = index; i < num; i ++){
                temp[i+1] = fibs[i];
            }
            temp[index] = value;
            delete [] fibs;
            fibs = temp;
            num ++;
        }
        else{
            for(size_t i = index; i < num; i ++){
                fibs[i+1] = fibs[i];
            }
            fibs[index] = value;
            num ++;
        }
    }
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
    if((num - 1) < fib(n-2)){
        cap = fib(n-1);
        n --;
    }
    int* temp = new int[cap];
    for(size_t i = 0; i < num - 1; i ++){
        temp[i] = fibs[i];
    }
    int value = fibs[num];
    delete [] fibs;
    fibs = temp;
    num --;
    return value;
}

void FibVec::push(int value){
    if(num == cap){
        cap = fib(n+1);
        n ++;
    }
    int* temp = new int[cap];
    for(size_t i = 0; i < num; i ++){
        temp[i] = fibs[i];
    }
    temp[num] = value;
}

int FibVec::remove(size_t index){
    if(index >= num){
        throw std::out_of_range("remove()");
    }
    if((num - 1) < fib(n-2)){
        cap = fib(n-1);
        n --;
    }
    int* temp = new int[cap];
    for(size_t i = 0; i < index; i ++){
        temp[i] = fibs[i];
    }
    int value = fibs[index];
    for(size_t i = index; i < num; i ++){
        temp[i] = fibs[i+1];
    }
    delete [] fibs;
    fibs = temp;
    num --;
    return value;

}