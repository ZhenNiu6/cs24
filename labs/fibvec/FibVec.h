#ifndef FIBVEC_H
#define FIBVEC_H

// This provides the size_t type:
#include <cstddef>

class FibVec {

  size_t mycapacity;
  size_t mylength;
  int* myvector;

public:

  FibVec();

  ~FibVec();

  size_t capacity() const;

  size_t count() const;

  void insert(int value, size_t index);

  int lookup(size_t index) const;

  int pop();

  void push(int value);

  int remove(size_t index);

  size_t add(size_t currentcapacity) const;

  size_t substract(size_t currentcapacity) const;

};

#endif
