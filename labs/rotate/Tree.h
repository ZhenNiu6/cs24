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
      return SIZE_MAX;
    }
    if(node->value == s){
      if(node->child[0] == nullptr){
        return 0;
      }
      return (node->child[0]->weight);
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

  // std::string lookup_helper(Node* node, size_t& index) const{
  //   // std::cout << node->index_ << '\n';
  //   if(node == nullptr){
  //     return "";
  //   }
  //   size_t root_index;
  //   if(node->child[0] == nullptr){
  //     root_index = 0;
  //   }
  //   else{
  //     root_index = node->child[0]->weight;
  //   }
  //   if(index == root_index){
  //     return node->value;
  //   }
  //   if(root_index < index){
  //     return lookup_helper(node->child[1], index);
  //   }
  //   else{
  //     return lookup_helper(node->child[0], index);
  //   }
  // }

   std::string lookup_helper(Node* node, size_t index) const{
    // std::cout << node->subweight << '\n';
    if(node == nullptr){
      return "";
    }
    size_t node_index;
    if(node->child[0] == nullptr){
      node_index = 0;
    }
    else{
      node_index = node->child[0]->weight;
    }
   
    
    if(index == node_index){
      return node->value;
    }
    else if(node_index < index){
      // Node* x = leftmost(node);
      index = index - node_index - 1;
      return lookup_helper(node->child[1], index);
    }
    else{
      return lookup_helper(node->child[0], index);
    }
    
  }

  // Node* leftmost(Node* node){
  //   if(node->child[0] == nullptr){
  //     return node;
  //   }
  //   return leftmost(node->child[0]);
  // }

  // size_t imbalance(Node* node){
  //   if(node == nullptr){
  //     return 0;
  //   }
  //   return node->index_ - imbalance(node->child[1]);
  // }




  void insert_helper(Node* node, Node* target){
    if(target->value <= node->value){
      if(node->child[0] == nullptr){
        node->child[0] = target;

      }
      else{
        insert_helper(node->child[0], target);
      }
    }
    else{
      if(node->child[1] == nullptr){
        node->child[1] = target;
      }
      else{
        insert_helper(node->child[1], target);
      }
    }
    node->find_weight();
    
}

  // Node* remove_helper(Node* node, size_t index){
  //   if(node == nullptr){
  //     return nullptr;
  //   }
  //   size_t root_index = node->child[0]->find_weight();
  //   if()

  // }


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
