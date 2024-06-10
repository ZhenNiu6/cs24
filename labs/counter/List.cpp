#include "List.h"

Node::Node() {
    mValue = 0;
    mKey = "";
    mBefore = nullptr;
    mAfter = nullptr;
    hash_after = nullptr;
}

Node::Node(int value, string key) {
    mValue = value;
    mKey = key;
    mBefore = nullptr;
    mAfter = nullptr;
    hash_after = nullptr;
}


List::List() {
    mStart = nullptr;
    mEnd = nullptr;
}

void List::destruct_helper(Node* current) {
    while(current != nullptr) {
        Node* next = current->mAfter;
        delete current;
        current = next;
    }
} 

List::~List() {
    if(mStart != nullptr) {
        destruct_helper(mStart);
    }
}

void List::insert(Node* node) {
    if(mEnd == nullptr) {
        mStart = node;
        mEnd = node;
    }
    else {
        node->mBefore = mEnd;
        mEnd->mAfter = node;
        mEnd = node;
    }
}

Node* List::find_helper(string input, Node* current) const {
    Node* result = nullptr;
    // if(current->mKey == input) {
    //     return current;
    // }
    // else if(current->mAfter != nullptr) {
    //     result = find_helper(input, current->mAfter);
    // }
    return result;
}

Node* List::find(string input) const {
    Node* result = nullptr;
    // if(mStart != nullptr) {
    //     result = find_helper(input, mStart);
    // }
    return result;
}

void List::remove(Node* current) {
    if(current->mBefore == nullptr && current->mAfter == nullptr) {
        mStart = nullptr;
        delete current;
        current = nullptr;
        mEnd = nullptr;
    }
    else if(current->mBefore == nullptr) {
        current->mAfter->mBefore = nullptr;
        mStart = current->mAfter;
        delete current;
        current = nullptr;
    }
    else if(current->mAfter == nullptr) {
        current->mBefore->mAfter = nullptr;
        mEnd = current->mBefore;
        delete current;
        current = nullptr;
    }
    else {
        current->mBefore->mAfter = current->mAfter;
        current->mAfter->mBefore = current->mBefore;
        delete current;
    }
}

// void List::remove(Node* current) {
//     if(current == nullptr) {
//         return;
//     } 
//     else if(current == mStart) {
//         Node* right = mStart->mAfter;
//         if(right != nullptr) {
//             right->mBefore = nullptr;
//             delete mStart;
//             mStart = right;
//         }
//         else {
//             delete mStart;
//             mStart = nullptr;
//             mEnd = nullptr;
//         }
//     }
//     else if(current == mEnd) {
//         Node* left = mEnd->mBefore;
//         if(left != nullptr) {
//             left->mAfter = nullptr;
//             delete mEnd;
//             mEnd = left;
//         }
//         else {
//             delete mEnd;
//             mStart = nullptr;
//             mEnd = nullptr;
//         }
//     }
//     else {
//         current->mBefore->mAfter = current->mAfter;
//         current->mAfter->mBefore = current->mBefore;
//         delete current;
//     }
// }

// void List::remove(string input) {
//     if(mStart == nullptr || find(input) == nullptr) {
//         return;
//     }
//     else if(mStart->mKey == input) {
//         Node* right = mStart->mAfter;
//         if(right != nullptr) {
//             right->mBefore = nullptr;
//             delete mStart;
//             mStart = right;
//         }
//         else {
//             delete mStart;
//             mStart = nullptr;
//             mEnd = nullptr;
//         }
//     }
//     else if(mEnd->mKey == input) {
//         Node* left = mEnd->mBefore;
//         if(left != nullptr) {
//             left->mAfter = nullptr;
//             delete mEnd;
//             mEnd = left;
//         }
//         else {
//             delete mEnd;
//             mStart = nullptr;
//             mEnd = nullptr;
//         }
//     }
//     else {
//         Node* target = find(input);
//         target->mBefore->mAfter = target->mAfter;
//         target->mAfter->mBefore = target->mBefore;
//         delete target;
//     }
// }

