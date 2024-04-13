#ifndef FIBVEC_H
#define FIBVEC_H

// This provides the size_t type:
#include <cstddef>

class FibVec {
  // Member Variables
    size_t num;
    size_t cap;
    size_t n;
    int* fibs;

  // Helper Functions
    size_t fib(n){
      if(n <= 1){
        return n;
      }
    return fib(n - 1) + fib(n - 2);
    }
    

public:
  // Constructor and Destructor
    FibVec();
    FibVec(const FibVec& other);
    ~FibVec();

  // Member Functions
    size_t capacity() const;
    size_t count() const;
    void insert(int value, size_t index);
    int lookup(size_t index) const;
    int pop();
    void push(int value);
    int remove(size_t index);
};

#endif
