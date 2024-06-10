#include "AST.h"
#include <iostream>
#include <sstream>
#include <string>

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

// If you want a different main function, write it here!
// This file won't be graded - do whatever you want.

int main() {
    string input = "5.4a";
    cout << double_check(input) << '\n';
    return 0;
}