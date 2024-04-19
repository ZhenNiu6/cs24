#include "Errors.h"
#include "Move.h"
#include <cctype>
#include <string>

// Space for implementing Move functions.

Move::Move(const std::string& input){
    // Check number
    if((input[0] < 48) || (input[0] > 57)){
        throw ParseError("Invalid move number");
    }
    number = input[0] - '0';


    // Check whitespace
    size_t n = 0;
    size_t index;
    for(size_t i = 1; i < input.length(); i ++){
        if(isspace(input[i])){
            n ++;
            continue;
        }
        else{
            index = i;
            if(n < 1){
                throw ParseError("Invalid whitespace");
            }
            break;
        }
    }
    n = 0;


    // Check player
    if((input[index] != 88) && (input[index] != 120) && (input[index] != 48)){
        throw ParseError("Invalid player code");
    }
    if((input[index] == 88) || (input[index] == 120)){
        char p = input[index];
        player = toupper(p);
    }
    
    // Check whitespace
    for(size_t i = index+1; i < input.length(); i ++){
        if(isspace(input[i])){
            n ++;
            continue;
        }
        else{
            index = i;
            if(n < 1){
                throw ParseError("Invalid whitespace");
            }
            break;
        }
    }
    n = 0;

    // Check row
    if((input[index] != 65) && (input[index] != 66) && (input[index] != 67) && (input[index] != 97) 
        && (input[index] != 98) && (input[index] != 99)){
        throw ParseError("Invalid square code");
    }
    int r = input[index];
    if((input[index] == 97) || (input[index] == 98) || (input[index] == 99)){
        r = input[index] - 32;
    }
    row = r - '@'; // Row A = 1, Row B = 2, Row C = 3;


    // Check column
    index ++;
    if((input[index] != 49) && (input[index] != 50) && (input[index] != 51)){
        throw ParseError("Invalid square code");
    }
    column = input[index] - '0';

    index ++;


    // Check extra whitespace
    if(index < input.length()){
        for(size_t i = index; i < input.length(); i ++){
            if(isspace(input[i])){
                n ++;
                continue;
            }
            else{
                index = i;
                if(n < 1){
                    throw ParseError("Invalid whitespace");
                }
                break;
            }
        }
        n = 0;
    }

    // Check comment
    if(index < input.length()){
        if(input[index] != 35){
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
