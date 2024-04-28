#include "Tree.h"
#include <iostream>

// This file is for you to test your tree functions.
// It won't be graded - do whatever you want.

int main() {
  
  Tree tree;
  // tree.insert("beta");
  // tree.insert("alpha");
  // tree.insert("omega");
  tree.insert("d");
  tree.insert("b");
  tree.insert("e");
  tree.insert("a");
  tree.insert("c");
  tree.insert("f");
  tree.print();
  tree.clear();
  tree.print();

  // Do tree things!

  return 0;
}
