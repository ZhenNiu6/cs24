#include "Node.h"

// Node Function Implementations

Node::Node() {

    content = "";
    left = nullptr;
    right = nullptr;
    mIndex = 0;
    weight = 0;

}

Node::Node(string input) {
    content = input;
    left = nullptr;
    right = nullptr;
    mIndex = 0;
    weight = 0;
}



