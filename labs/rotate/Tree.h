#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include <iostream>

class Tree {
  // Member Variables
  Node* root;
  size_t num;


  // Private Helper Functions
  // void rotate(Node* node){
  //   if(node->)
  // }
  size_t imbalance(Node* node){
    if(node == nullptr){
      return 0;
    }
    return node->subweight - imbalance(node->child[1]);
  }

  void insert_helper(Node* node, const std::string& s){
    if((s < node->value) || (s == node->value)){
      if(node->child[0] == nullptr){
        node->child[0] = new Node(s);
        node->subweight ++;
      }
      else{
        insert_helper(node->child[0], s);
      }
    }
    else{
      if(node->child[1] == nullptr){
        node->child[1] = new Node(s);
        node->subweight ++;
      }
      else{
        insert_helper(node->child[1], s);
      }
    }
  }

  void print_helper(Node* node) const{
    // std::cout << node->child[0]->value << '\n';
    if((node->child[0] != nullptr) || (node->child[1] != nullptr)){
      std::cout << "(";
      if(node->child[0] != nullptr){
        print_helper(node->child[0]);
      }
      else{
        std::cout << "- ";
      }
      std::cout << " " << node->value << " ";
      if(node->child[1] != nullptr){
        print_helper(node->child[1]);
      }
      else{
        std::cout << "-";
      }
      std::cout << ")";
    }
    else{
      // std::cout << "(- ";
      std::cout << node->value;
      // std::cout << " -)";
    }
   
  }

public:
  Tree();
  ~Tree();

  // Public Member Functions
  void        clear();
  size_t      count() const;
  bool        contains(const std::string& s) const;
  size_t      find(const std::string& s) const;
  void        insert(const std::string& s);
  std::string lookup(size_t index) const;
  void        print() const;
  void        remove(size_t index);
};

#endif
