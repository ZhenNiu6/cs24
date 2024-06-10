#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include <cmath>
using namespace std;

class Tree {
  // Member Variables
  // Private Helper Functions

public:
  Node* root;
  size_t mLength;
  Tree();
  ~Tree();
  // Public Member Functions
  void        clear_helper(Node* current);
  void        clear();
  Node*       return_root();
  size_t      count() const;
  bool        contains_helper(const string& s, Node* current) const;
  bool        contains(const std::string& s) const;
  void        calculate_weight(Node* current);
  void        set_index(Node* current);
  size_t      find_helper(const string& s, Node* current) const;
  size_t      find(const std::string& s) const;
  void        compare_Node(Node* target, Node* Node);
  void        insert(const std::string& s);
  string      lookup_helper(Node* current, size_t index) const;
  std::string lookup(size_t index) const;
  void        print_Tree(Node* root) const;
  void        print() const;
  Node*       return_node(size_t index, Node* current);
  void        remove_zero(size_t index, Node* current);
  void        remove_one(size_t index, Node* current);
  void        remove_two(size_t index, Node* current);
  void        remove_helper(size_t index);
  void        remove(size_t index);
  void        left_rotation(Node*& current);
  void        right_rotation(Node*& current);
  void        rotate(Node*& current);
};

#endif
