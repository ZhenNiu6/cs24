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



  size_t find_helper(Node* node, const std::string& s, size_t index) const{
    if(node == nullptr){
      return SIZE_MAX;
    }
    if(node->value > s){
      return find_helper(node->child[0], s, index);
    }
    else if(node->value < s){
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



  void insert_helper(Node* node, Node* target){
    if(target->value <= node->value){
      if(node->child[0] == nullptr){
        node->child[0] = target;
        target->parent = node;
        // rotate?
        rotation(node,target);
      }
      else{
        insert_helper(node->child[0], target);
        rotation(node, node->child[0]);
      }
    }
    else{
      if(node->child[1] == nullptr){
        node->child[1] = target;
        target->parent = node;
        // rotate?
        rotation(node,target);
      }
      else{
        insert_helper(node->child[1], target);
        rotation(node, node->child[1]);
      }
    }
    target->weight = target->find_weight();
    node->weight = node->find_weight();
    // rotation(node, target);
    
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
      else if((node->child[0] != nullptr) && (node->child[1] == nullptr)){ // only has right child
        Node* temp = node->child[0];
        node->value = temp->value;
        node->child[0] = temp->child[0];
        node->child[1] = temp->child[1];
        delete temp;
        if(node->parent != nullptr){
          rotation(node->parent, node);
        }
        return node;
      }
      else if((node->child[0] == nullptr) && (node->child[1] != nullptr)){ // only has left child
        Node* temp = node->child[1];
        // if(node == root){
        node->value = temp->value;
        node->child[0] = temp->child[0];
        node->child[1] = temp->child[1];
        delete temp;
        if(node->parent != nullptr){
          rotation(node->parent, node);
        }
        return node;
      }
      
      // else if((node->child[1] != nullptr) && (node->child[0] == nullptr)){
      //   Node* change = node->child[1];
        
      //   delete node;
      //   return change;
      // }
    //   else{
    //     return node;
    //   }
    }
    return node;

  }

  // Node* remove_helper(Node* root, size_t index){
  //   std::cout << root->value << '\n';
  //   if(root == nullptr){
  //     return root;
  //   }
  //   size_t root_index;
  //   if(root->child[0] != nullptr){
  //     root_index = root->child[0]->weight;
  //   }
  //   else{
  //     root_index = 0;
  //   }
  //   if(index < root->weight){
  //     std::cout << "left" << '\n';
  //     if(root->child[0] != nullptr){
  //       root->child[0] = remove_helper(root->child[0], index);
  //     }
     
  //   }
  //   else if(index > root->weight){
  //     std::cout << "right" << '\n';
  //     if(root->child[1] != nullptr){
  //       root->child[1] = remove_helper(root->child[1], index - root_index - 1);
        
  //     }
      
  //   }
  //   if(root->child[0] == nullptr){
  //     Node* temp;
  //     if(root->child[1] != nullptr){
  //       temp = root->child[1];
  //     }
  //     else{
  //       delete root;
  //       return nullptr;
  //     }
  //     if(root->parent != nullptr){
  //       if(root->parent->child[0] == root){
  //         root->parent->child[0] = temp;
  //       }
  //       else{
  //         root->parent->child[1] = temp;
  //       }
  //     }
  //     else{
  //       root = temp;
  //     }
  //     delete root;
  //     return temp;
  //   }
  //   else if(root->child[1] == nullptr){
  //     Node* temp;
  //     if(root->child[0] != nullptr){
  //       temp = root->child[0];
  //     }
  //     else{
  //       delete root;
  //       return nullptr;
  //     }
  //     if(root->parent != nullptr){
  //       if(root->parent->child[0] == root){
  //         root->parent->child[0] = temp;
  //       }
  //       else{
  //         root->parent->child[1] = temp;
  //       }
  //     }
  //     else{
  //       root = temp;
  //     }
  //     delete root;
  //     return temp;
  //   }
  //   Node* right = root->child[1];
  //   Node* p = root;
  //   while(right->child[0] != nullptr){
  //     p = right;
  //     right = right->child[0];
  //   }
  //   root->weight = right->weight;
  //   if(p->child[0] == right){
  //     p->child[0] = right->child[1];
  //   }
  //   else{
  //     p->child[1] = right->child[1];
  //   }
  //   delete right;
  //   return root;
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




    void rotation(Node* p, Node* c){
      if((p == nullptr) || (c == nullptr)){
        return;
      }
      // std::cout << "parent " << p->value << '\n';
      // std::cout << "child " << c->value << '\n';

      size_t x = 0, y = 0, z = 0;
      if(c == p->child[0]){ // need right rotation
        if(c->child[0] != nullptr){
          x = c->child[0]->find_weight();
        }
        // std::cout << "x " << x << '\n';
        if(c->child[1] != nullptr){
          y = c->child[1]->find_weight();
        }
        // std::cout << "y " << x << '\n';
        if(p->child[1] != nullptr){
          z = p->child[1]->find_weight();
        }
        // std::cout << "z " << x << '\n';
        size_t before = absolute(x + y + 1 - z);
        // std::cout << "before " << before << '\n';
        size_t after = absolute(y + z + 1 - x);
        // std::cout << "after " << after << '\n';
        if(after < before){
          // std::cout << "right" << '\n';
          // print();
          rightRotate(p);
        }
      }
      else{
        if(p->child[0] != nullptr){
          x = p->child[0]->find_weight();
        }
        // std::cout << "x " << x << '\n';
        if(c->child[0] != nullptr){
          y = c->child[0]->find_weight();
        }
        // std::cout << "y " << x << '\n';
        if(c->child[1] != nullptr){
          z = c->child[1]->find_weight();
        }
        // std::cout << "z " << x << '\n';
        size_t before = absolute(y + z + 1 - x);
        // std::cout << "before " << before << '\n';
        size_t after = absolute(x + y + 1 - z);
        // std::cout << "after " << after << '\n';
        if(after < before){
          // print();

          leftRotate(p);
          // std::cout << "left" << '\n';
        }
      }
      if(p != root){
        rotation(p->parent, p);
      }
     
    }
    

size_t absolute(int x){
  if(x < 0){
    x = -x;
  }
  return x;
}


void leftRotate(Node* p) {
    if((p->child[1] == nullptr) || (p == nullptr)){
      return;
    }
    Node* q = p->child[1];
    Node* k = q->child[0];
    if(p == root){
      q->parent = nullptr;
      root = q;
    }
    else{
      q->parent = p->parent;
      if(p == p->parent->child[1]){
        p->parent->child[1] = q;
      }
      else{
        p->parent->child[0] = q;
      }
    }
    p->parent = q;
    
    p->child[1] = q->child[0];
    
    q->child[0] = p;
    if(k != nullptr){
      k->parent = p;
    }
    p->weight = p->find_weight();
    q->weight = q->find_weight();
}


void rightRotate(Node* p) {
    if((p->child[0] == nullptr) || (p == nullptr)){
      return;
    }
    Node* q = p->child[0];
    Node* k = q->child[1];
    if(p == root){
      q->parent = root;
      root = q;
    }
    else{
      q->parent = p->parent;
      if(p == p->parent->child[0]){
        p->parent->child[0] = q;
      }
      else{
        p->parent->child[1] = q;
      }
    }
    p->parent = q;

    p->child[0] = q->child[1];
  
    
    q->child[1] = p;
    if(k != nullptr){
      k->parent = p;
    }
    p->weight = p->find_weight();
    q->weight = q->find_weight();
    // std::cout << q->child[1]->value << '\n';
    
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
