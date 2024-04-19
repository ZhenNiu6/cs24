#include "Errors.h"
#include "Move.h"
#include <cctype>
#include <string>
#include <iostream>

// Space for implementing Move functions.

Move::Move(const std::string& input){
    // Check number
    int a;
    size_t index = 0;
    if(isdigit(input[index]) && isdigit(input[index+1])){
        std::string temp = "";
        temp += input[index];
        temp += input[index+1];
        a = stoi(temp);
    }
    else{
        throw ParseError("Invalid move number");
    }
    if((a < 48) || (a > 57)){
        throw ParseError("Invalid move number");
    }
    number = a - '0';


    // Check whitespace
    size_t n = 0;
    for(size_t i = 2; i < input.length(); i ++){
        if(isspace(input[i])){
            n ++;
            continue;
        }
        else{
            index = i;
            if(n < 1){
                throw ParseError("Invalid whitespace 1");
            }
            break;
        }
    }
    n = 0;


    // Check player
    bool h = false;
    if(isdigit(input[index]) && isdigit(input[index+1])){
        std::string temp = "";
        temp += input[index];
        temp += input[index+1];
        if(isdigit(input[index+2])){
            temp += input[index+2];
            h = true;
        }
        a = stoi(temp);
    }
    else{
        throw ParseError("Invalid player code");
    }
    if((a != 88) && (a != 120) && (a != 48)){
        throw ParseError("Invalid player code");
    }
    if((a == 88) || (a == 120)){
        char p = a;
        player = toupper(p);
    }
    if(h){
        index += 3;
    }
    else{
        index += 2;
    }
    
    // Check whitespace
    for(size_t i = index; i < input.length(); i ++){
        if(isspace(input[i])){
            n ++;
            continue;
        }
        else{
            index = i;
            if(n < 1){
                throw ParseError("Invalid whitespace 2");
            }
            break;
        }
    }
    n = 0;

    // Check row
    if(isdigit(input[index]) && isdigit(input[index+1])){
        std::string temp = "";
        temp += input[index];
        temp += input[index+1];
        a = stoi(temp);
    }
    else{
        throw ParseError("Invalid square code");
    }
    if((a != 65) && (a != 66) && (a != 67) && (a != 97) && (a != 98) && (a != 99)){
        throw ParseError("Invalid square code");
    }
    int r = a;
    if((a == 97) || (a == 98) || (a == 99)){
        r = a - 32;
    }
    row = r - '@'; // Row A = 1, Row B = 2, Row C = 3;
    index += 2;

    // Check extra whitespace
    for(size_t i = index; i < input.length(); i ++){
        if(isspace(input[i])){
            continue;
        }
        else{
            index = i;
            break;
        }
    }

    // Check column
    if(isdigit(input[index]) && isdigit(input[index+1])){
        std::string temp = "";
        temp += input[index];
        temp += input[index+1];
        a = stoi(temp);
    }
    else{
        throw ParseError("Invalid square code");
    }
    if((a != 49) && (a != 50) && (a != 51)){
        throw ParseError("Invalid square code");
    }
    column = a - '0';

    index += 2;


    // Check extra whitespace and comment
    if(index < input.length()){
        for(size_t i = index; i < input.length(); i ++){
            if(isspace(input[i])){
                n ++;
            }
            else{
                index = i;
                if(n < 1){
                    if((index+1) < input.length()){
                        if(isdigit(input[index]) && isdigit(input[index+1])){
                            std::string temp = "";
                            temp += input[index];
                            temp += input[index+1];
                            a = stoi(temp);
                        }
                        if(a == 35){
                            throw ParseError("Invalid whitespace 3");
                        }
                    }
                }
                break;
            }
            if(i == (input.length()-1)){
                index += n;
            }
        }
        n = 0;
    }

    // Check comment
    if((index+1) < input.length()){
        std::cout << "here" << '\n';
        if(isdigit(input[index]) && isdigit(input[index+1])){
            std::string temp = "";
            temp += input[index];
            temp += input[index+1];
            a = stoi(temp);
            std::cout << a << '\n';
        }
        else{
            throw ParseError("Invalid comment");
        }
        if(a != 35){
            throw ParseError("Invalid comment");
        }
    }
}


std::string Move::to_string() const{
    std::string output = "";
    output += std::to_string(number);
    output += " ";
    output += player;
    output += " ";
    if(row == 1){
        output += 'A';
    }
    if(row == 2){
        output += 'B';
    }
    if(row == 3){
        output += 'C';
    }
    output += std::to_string(column);
    return output;
}


