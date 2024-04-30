#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include <iostream>
#include <cstdlib>

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


  // size_t find_helper(Node* node, const std::string& s) const{
  //   if(node == nullptr){
  //     return SIZE_MAX;
  //   }
  //   if(node->value == s){
  //     if(node->child[0] == nullptr){
  //       return 0;
  //     }
  //     return (node->child[0]->weight);
  //   }
  //   if(node->value >= s){
  //     return find_helper(node->child[0], s);
  //   }
  //   else{
  //     return find_helper(node->child[1], s);
  //   }
  // }

  size_t find_helper(Node* node, const std::string& s, size_t index) const{
    if(node == nullptr){
      // std::cout<<"return ull"<<std::endl;
      return SIZE_MAX;
    }
    if(node->value > s){
      // std::cout<<"left  "<< node->value<<std::endl;
      // if(node->child[0] == nullptr)  std::cout<<"debug left"<<std::endl;
      return find_helper(node->child[0], s, index);
    }
    else if(node->value < s){
      // std::cout<<"right "<<node->value<<std::endl;
      // if(node->child[0] == nullptr)  std::cout<<"debug rigfht"<<std::endl;
      if(node->child[0] == nullptr){
        return find_helper(node->child[1], s, index + 1);
      }
      return find_helper(node->child[1], s, index + 1 + node->child[0]->find_weight());
    }
    else{
      if(node->child[0] != nullptr){
        size_t new_index = find_helper(node->child[0], s, index);
        if(new_index !=  SIZE_MAX){
          return new_index;
        }
        return index + node->child[0]->find_weight();
      }
      
      return index;
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
        target->parent = node;

      }
      else{
        insert_helper(node->child[0], target);
      }
    }
    else{
      if(node->child[1] == nullptr){
        node->child[1] = target;
        target->parent = node;
      }
      else{
        insert_helper(node->child[1], target);
      }
    }
    node->weight = node->find_weight();
    
}

  Node* remove_helper(Node* node, size_t index){
    if(node == nullptr){
      return nullptr;
    }
    size_t root_index;
    if(node->child[0] != nullptr){
      root_index = node->child[0]->weight;
    }
    else{
      root_index = 0;
    }
    if(root_index > index){
      if(node->child[0] != nullptr){
        node->child[0] = remove_helper(node->child[0], index);
      }
    }
    else if(root_index < index){
      if(node->child[1] != nullptr){
        node->child[1] = remove_helper(node->child[1], index - root_index - 1);
      }
    }
    else{
      if((node->child[0] == nullptr) && (node->child[1] == nullptr)){
        delete node;
        return nullptr;
      }
    }
    return node;

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

  // void rotation(Node* p, Node* c){
  //   size_t weight_x;
  //   size_t weight_y;
  //   size_t weight_z;
  //   if(c == p->child[0]){
  //     weight_x = c->child[0]->weight;
  //     weight_y = c->child[1]->weight;
  //     weight_z = p->child[1]->weight;
  //     if(abs(weight_x + weight_y + 1 - weight_z) > abs(weight_y + weight_z + 1 - weight_x)){ //improve the imbalance

  //     }
  //   }
  // }

//   void rotation(Node* p, Node* c) {
//     // Base case: Stop recursion if either parent or child is null
//     if (p == nullptr || c == nullptr) {
//         return;
//     }
    
//     // Calculate weights
//     size_t weight_x = 0, weight_y = 0, weight_z = 0;
//     if (c == p->child[0]) {
//         if (c->child[0] != nullptr) {
//             weight_x = c->child[0]->weight;
//         }
//         if (c->child[1] != nullptr) {
//             weight_y = c->child[1]->weight;
//         }
//         if (p->child[1] != nullptr) {
//             weight_z = p->child[1]->weight;
//         }
        
//         // Check if rotation would improve imbalance
//         if (absolute(weight_x + weight_y + 1 - weight_z) > absolute(weight_y + weight_z + 1 - weight_x)) {
//           rightRotate(p);
//           rightRotate(c);
//           leftRotate(c);
//         }
//     }
//     else{
//       if(p->child[0] != nullptr){
//         weight_x = p->child[0]->weight;
//       }
//       if(c->child[0] != nullptr){
//         weight_y = c->child[0]->weight;
//       }
//       if(c->child[1] != nullptr){
//         weight_z = c->child[1]->weight;
//       }
//       if(absolute(weight_z + weight_y + 1 - weight_x) > absolute(weight_x + weight_y + 1 - weight_z)){
//         leftRotate(c);
//         rightRotate(c);
//         rightRotate(p);
//       }
      
//     }
    
//     // Continue recursion for other cases or subtrees
//     rotation(p->parent, p);
// }

void rotation(Node*& p, Node*& c) {
    // Base case: Stop recursion if either parent or child is null
    if (p == nullptr || c == nullptr) {
        return;
    }
    // Calculate weights before rotation
    size_t weight_x_before = 0, weight_y_before = 0, weight_z_before = 0;
    if (c == p->child[0]) {
        if (c->child[0] != nullptr) {
            weight_x_before = c->child[0]->weight;
        }
        if (c->child[1] != nullptr) {
            weight_y_before = c->child[1]->weight;
        }
        if (p->child[1] != nullptr) {
            weight_z_before = p->child[1]->weight;
        }
        rightRotate(p);
    }
    else {
        if (p->child[0] != nullptr) {
            weight_z_before = p->child[0]->weight;
        }
        if (c->child[0] != nullptr) {
            weight_x_before = c->child[0]->weight;
        }
        if (c->child[1] != nullptr) {
            weight_y_before = c->child[1]->weight;
        }
        leftRotate(p);
    }
    
    
    // Calculate weights after rotation
    size_t weight_x_after = 0, weight_y_after = 0, weight_z_after = 0;
    if (c == p->child[0]) {
        if (c->child[0] != nullptr) {
          c->child[0]->find_weight();
          weight_x_after = c->child[0]->weight;
        }
        if (c->child[1] != nullptr) {
          c->child[1]->find_weight();
          weight_y_after = c->child[1]->weight;
        }
        if (p->child[1] != nullptr) {
          p->child[1]->find_weight();
          weight_z_after = p->child[1]->weight;
        }
    }
    else {
        if (p->child[0] != nullptr) {
          p->child[0]->find_weight();
          weight_z_after = p->child[0]->weight;
        }
        if (c->child[0] != nullptr) {
          c->child[0]->find_weight();
          weight_x_after = c->child[0]->weight;
        }
        if (c->child[1] != nullptr) {
          c->child[1]->find_weight();
          weight_y_after = c->child[1]->weight;
        }
    }
    
    // Compare imbalances before and after rotation
    size_t imbalance_before = absolute(weight_x_before + weight_y_before + 1 - weight_z_before);
    size_t imbalance_after = absolute(weight_x_after + weight_y_after + 1 - weight_z_after);
    
    // If imbalance is improved, keep the rotation; otherwise, rotate back
    if (imbalance_after >= imbalance_before) {
        // Rotation did not improve imbalance, rotate back
        if(c == p->child[0]){
          leftRotate(c);
        }
        else{
          rightRotate(c);
        }
        
    }
    
    // Continue recursion for other cases or subtrees
    rotation(p->parent, p);
}

size_t absolute(size_t x){
  if(x < 0){
    x = -x;
  }
  return x;
}


void leftRotate(Node* p) {
    Node* q = p->child[1];
    Node* z = q->child[0];
    q->child[0] = p;
    p->child[1] = z;
}

void rightRotate(Node*& p) {
    Node* q = p->child[0];
    Node* z = q->child[1];
    q->child[1] = p;
    p->child[0] = z;
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
