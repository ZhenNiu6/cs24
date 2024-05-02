#include "Tree.h"
#include <iostream>

// This file is for you to test your tree functions.
// It won't be graded - do whatever you want.

int main() {
  
  Tree tree;
  // tree.insert("d");
  // tree.insert("b");
  // tree.insert("f");
  // tree.insert("a");
  // tree.insert("c");
  // tree.insert("e");
  // tree.insert("g");
  // tree.insert("a");
  // tree.insert("b");
  // tree.insert("c");
  // tree.insert("d");
  // tree.insert("e");
  // tree.insert("f");
  // tree.insert("g");
  // tree.insert("m");
  // tree.insert("b");
  // tree.insert("s");
  // tree.insert("b");
  // tree.insert("m");
  // tree.insert("s");
  // tree.insert("b");
  // tree.insert("m");
  // tree.insert("selenium");
  // tree.insert("sulfur");
  // tree.insert("tellurium");
  // tree.insert("polonium");
  // tree.insert("oxygen");
  // tree.insert("a");
  // tree.insert("b");
  // tree.insert("c");
  // tree.insert("d");
  // tree.insert("e");
  // tree.insert("f");
  // tree.insert("g");
  // tree.insert("h");
  // tree.insert("i");
  // tree.insert("j");
    tree.insert("Aphrodite");
    tree.insert("Apollo");
    tree.insert("Ares");
    tree.insert("Artemis");
    tree.insert("Athena");
    tree.insert("Demeter");
    tree.insert("Dionysus");
    tree.insert("Hades");
    tree.insert("Hephaestus");
    tree.insert("Hera");
    tree.insert("Hermes");
    tree.insert("Hestia");
    tree.insert("Poseidon");
    tree.insert("Zeus");
  
  tree.print();

  tree.remove(0);
  tree.remove(2);
  tree.print();

  // size_t result = tree.find("f");
  // tree.remove(0);
  // tree.print();
  // std::cout << result << '\n';


  // Do tree things!

  return 0;
}
