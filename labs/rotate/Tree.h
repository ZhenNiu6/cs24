#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include <iostream>

class Tree {
  // Member Variables
  Node* root;
  size_t num;


  // Private Helper Functions


  bool contains_helper(Node* node, const std::string& s) const{
    if(node == nullptr){
      return false;
    }
    if(node->value == s){
      return true;
    }
    else{
      if(node->value >= s){
        return contains_helper(node->child[0], s);
      }
      else{
        return contains_helper(node->child[1], s);
      }
    }
  }


  size_t find_helper(Node* node, const std::string& s) const{
    if(node == nullptr){
      return 0;
    }
    if(node->value == s){
      return node->subweight;
    }
    if(node->value >= s){
      return find_helper(node->child[0], s);
    }
    else{
      return find_helper(node->child[1], s);
    }
  }


  void clear_helper(Node* node){
    if(node != nullptr){
      clear_helper(node->child[0]);
      clear_helper(node->child[1]);
      node->child[0] = nullptr;
      node->child[1] = nullptr;
      delete node;
    }
  }

  std::string lookup_helper(Node* node, size_t& index) const{
    if(node == nullptr){
      return "";
    }
    if(index == node->subweight){
      return node->value;
    }
    if(node->subweight < index){
      return lookup_helper(node->child[1], index);
    }
    else{
      return lookup_helper(node->child[0], index);
    }
  }

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
    if((node == nullptr) && (node == root)){
      std::cout << "-";
    }
    else{
      if((node->child[0] != nullptr) || (node->child[1] != nullptr)){
        std::cout << "(";
        if(node->child[0] != nullptr){
          print_helper(node->child[0]);
        }
        else{
          std::cout << "-";
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
        std::cout << node->value;
      }
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
