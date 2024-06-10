#ifndef NODE_H
#define NODE_H

#include <string>
#include <iostream>
using namespace std;

struct Node {

  string content;
  Node* left;
  Node* right;
  size_t mIndex;
  size_t weight;

  Node();
  Node(string input);

};

#endif
