#include "FibVec.h"
#include <iostream>

// Use this file to test your FibVec class!
// This file won't be graded - do whatever you want.

int main() {
  FibVec fibvec;
  // for(size_t i = 0; i < fibvec.count(); i ++){
  //   std::cout << " " << fibvec.lookup(i);
  // }
  // std::cout << '\n';

  fibvec.push(12);
  fibvec.push(10);
  fibvec.push(2);

  std::cout << "Array contents:";
    for (size_t i = 0; i < fibvec.count(); ++i) {
        std::cout << " " << fibvec.lookup(i);
    }
    std::cout << '\n';
  
  fibvec.insert(1, 2);
  std::cout << "Array contents:";
  for (size_t i = 0; i < fibvec.count(); ++i) {
      std::cout << " " << fibvec.lookup(i);
  }
  std::cout << '\n';

  return 0;
}
