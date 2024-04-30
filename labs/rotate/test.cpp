#include "Tree.h"
#include <iostream>

// This file is for you to test your tree functions.
// It won't be graded - do whatever you want.

int main() {
  
  Tree tree;
  tree.insert("d");
  tree.insert("b");
  tree.insert("f");
  tree.insert("a");
  tree.insert("c");
  tree.insert("e");
  tree.insert("g");
  // tree.insert("m");
  // tree.insert("b");
  // tree.insert("s");
  // tree.insert("b");
  // tree.insert("m");
  // tree.insert("s");
  // tree.insert("b");
  // tree.insert("m");
  tree.print();

  // size_t result = tree.find("f");
  tree.remove(0);
  tree.print();
  // std::cout << result << '\n';


  // Do tree things!

  return 0;
}
