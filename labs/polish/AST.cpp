#include "AST.h"
#include "Nodes.h"
#include "Stack.h"

#include <sstream>
#include <iostream>
#include <cmath>
using namespace std;

bool double_check(string input) {
    istringstream iss(input);
    double num;
    char remain;
    if(!(iss >> num)) {
        return false;
    }
    if(iss >> remain) {
        return false;
    }
    return true;
}

AST* AST::parse(const std::string& expression) {
    std::string token;
    std::istringstream stream(expression);
    stack aStack = stack();
    int error_status = 0;

    while(stream >> token) {
        if(double_check(token)) {
            double current_value = stod(token);
            Node* current = new Node(current_value);
            aStack.push(current);
        }
        else if(token.length() == 1) {
            if(token[0] == '+') {
                if(aStack.return_length() >= 2) {
                    Node* right_node = aStack.pop();
                    Node* left_node = aStack.pop();
                    double add_result = left_node->mNum + right_node->mNum;
                    Node* add_result_node = new Node(add_result);
                    add_result_node->left = left_node;
                    add_result_node->right = right_node;
                    add_result_node->mOperator = '+';
                    aStack.push(add_result_node);
                }
                else {
                    error_status = 1;
                    break;
                }
            }
            else if(token[0] == '-') {
                if(aStack.return_length() >= 2) {
                    Node* right_node = aStack.pop();
                    Node* left_node = aStack.pop();
                    double subs_result = left_node->mNum - right_node->mNum;
                    Node* subs_result_node = new Node(subs_result);
                    subs_result_node->left = left_node;
                    subs_result_node->right = right_node;
                    subs_result_node->mOperator = '-';
                    aStack.push(subs_result_node);
                }
                else {
                    error_status = 1;
                    break;
                }
            }
            else if(token[0] == '*') {
                if(aStack.return_length() >= 2) {
                    Node* right_node = aStack.pop();
                    Node* left_node = aStack.pop();
                    double product_result = left_node->mNum * right_node->mNum;
                    Node* product_result_node = new Node(product_result);
                    product_result_node->left = left_node;
                    product_result_node->right = right_node;
                    product_result_node->mOperator = '*';
                    aStack.push(product_result_node);
                }
                else {
                    error_status = 1;
                    break;
                }
            }
            else if(token[0] == '/') {
                if(aStack.return_length() >= 2) {
                    Node* right_node = aStack.pop();
                    Node* left_node = aStack.pop();
                    double quo_result = left_node->mNum / right_node->mNum;
                    Node* quo_result_node = new Node(quo_result);
                    quo_result_node->left = left_node;
                    quo_result_node->right = right_node;
                    quo_result_node->mOperator = '/';
                    aStack.push(quo_result_node);
                }
                else {
                    error_status = 1;
                    break;
                }
            }
            else if(token[0] == '%') {
                if(aStack.return_length() >= 2) {
                    Node* right_node = aStack.pop();
                    Node* left_node = aStack.pop();
                    double mod_result = fmod(left_node->mNum, right_node->mNum);
                    Node* mod_result_node = new Node(mod_result);
                    mod_result_node->left = left_node;
                    mod_result_node->right = right_node;
                    mod_result_node->mOperator = '%';
                    aStack.push(mod_result_node);
                }
                else {
                    error_status = 1;
                    break;
                }
            }
            else if(token[0] == '~') {
                if(aStack.return_length() >= 1) {
                    Node* right_node = aStack.pop();
                    double negate_result = - right_node->mNum;
                    Node* negate_result_node = new Node(negate_result);
                    negate_result_node->left = nullptr;
                    negate_result_node->right = right_node;
                    negate_result_node->mOperator = '~';
                    aStack.push(negate_result_node);
                }
                else {
                    error_status = 1;
                    break;
                }
            }
            else {
                error_status = 2;
                break;
            }
        }
        else {
            error_status = 2;
            break;
        }
    }
    if(error_status == 2) {
        for(size_t i = 0; i < aStack.return_length(); ++i) {
            delete aStack.pop();
        }
        throw runtime_error("Invalid token: " + token);
    }
    else if(error_status == 1) {
        for(size_t i = 0; i < aStack.return_length(); ++i) {
            delete aStack.pop();
        }
        throw runtime_error("Not enough operands.");
    }
    else if(aStack.return_length() > 1) {
        for(size_t i = 0; i < aStack.return_length(); ++i) {
            delete aStack.pop();
        }
        throw runtime_error("Too many operands.");
    }
    else if(aStack.return_length() == 0) {
        for(size_t i = 0; i < aStack.return_length(); ++i) {
            delete aStack.pop();
        }
        throw runtime_error("No input.");
    }
    Node* result = aStack.pop();
    for(size_t i = 0; i < aStack.return_length(); ++i) {
        delete aStack.pop();
    }
    return result;
}
