#include "Nodes.h"

#include <sstream>
#include <string>
#include <cmath>

using namespace std;

// This creates the number format the autograder expects:
std::string format(double number) {
  std::ostringstream stream;
  stream << number;
  return stream.str();
}


// Implement your AST subclasses' member functions here.

Node::Node() {
    left = nullptr;
    right = nullptr;
    mNum = 0;
    mOperator = '\0';
}

Node::~Node() {
    delete left;
    delete right;
}

Node::Node(double mNum) {
    left = nullptr;
    right = nullptr;
    this->mNum = mNum;
    mOperator = '\0';
}

Node::Node(char mOperator) {
    left = nullptr;
    right = nullptr;
    mNum = 0;
    this->mOperator = mOperator;
}

string Node::prefix() const {
    string result = "";
    if(left == nullptr && right == nullptr) {
        result = format(mNum);
        return result;
    }
    else {
        result += mOperator;
        if(left != nullptr) {
            result += " ";
            result += left->prefix();
        }
        if(right != nullptr) {
            result += " ";
            result += right->prefix();
        }
    }
    return result;
}

string Node::postfix() const {
    string result = "";
    if(left == nullptr && right == nullptr) {
        result = format(mNum);
        return result;
    }
    else {
        if(left != nullptr) {
            result += left->postfix();
            result += " ";
        }
        if(right != nullptr) {
            result += right->postfix();
            result += " ";
        }
        result += mOperator;
    }
    return result;
}

double Node::value() const {
    if(left == nullptr && right == nullptr) {
        return mNum;
    }
    else {
        double left_value = 0;
        double right_value = 0;
        double result = 0;
        if(left != nullptr) {
            left_value = left->value();
        }
        if(right != nullptr) {
            right_value = right->value();
        }
        if(mOperator == '+') {
            result = left_value + right_value;
        }
        else if(mOperator == '-') {
            result = left_value - right_value;
        }
        else if(mOperator == '*') {
            result = left_value * right_value;
        }
        else if(mOperator == '/') {
            if(right_value == 0) {
                throw std::runtime_error("Division by zero.");
            }
            else {
                result = left_value / right_value;
            }
        }
        else if(mOperator == '%') {
            if(right_value == 0) {
                throw std::runtime_error("Division by zero.");
            }
            else {
                result = fmod(left_value, right_value);
            }
        }
        else if(mOperator == '~') {
            result = - right_value;
        }
        return result;
    }
}