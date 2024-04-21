#include "Errors.h"
#include "Move.h"
#include <cctype>
#include <string>
#include <iostream>

// Space for implementing Move functions.

Move::Move(const std::string& input){
    // Check number
    size_t index = 0;
    if(!isdigit(input[index])){
        throw ParseError("Invalid move number");
    }
    if(input[index] == '0'){
        throw ParseError("Invalid move number");
    }
    number = input[index] - '0';
    index ++;


    // Check whitespace
    size_t n = 0;
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
    if((input[index] != 'X') && (input[index] != 'x') && (input[index] != 'O') && (input[index] != 'o')){
        throw ParseError("Invalid player code");
    }
    player = input[index];
    if(input[index] == 'x'){
        player = 'X';
    }
    if(input[index] == 'o'){
        player = 'O';
    }
    index ++;
    
    // Check whitespace
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

    // Check row
    if((input[index] != 'A') && (input[index] != 'B') && (input[index] != 'C') && (input[index] != 'a') 
        && (input[index] != 'b') && (input[index] != 'c')){
        throw ParseError("Invalid square code");
    }
    int r = input[index];
    if((input[index] == 'a') || (input[index] == 'b') || (input[index] == 'c')){
        r = input[index] - 32;
    }
    row = r - '@'; // Row A = 1, Row B = 2, Row C = 3;
    index ++;


    // Check column
    if((input[index] != '1') && (input[index] != '2') && (input[index] != '3')){
        throw ParseError("Invalid square code");
    }
    column = input[index] - '0';
    index ++;


    // Check extra whitespace
    if(index < input.length()){
        for(size_t i = index; i < input.length(); i ++){
            if(isspace(input[i])){
                n ++;
            }
            else{
                if(input[i] == '#'){
                    if(n < 1){
                        throw ParseError("Invalid comment");
                    }
                }
                if(input[i] != '#'){
                    throw ParseError("Invalid comment");
                }
                break;
            }
        }
    }
}


std::string Move::to_string() const{
    std::string output = "";
    if(number == 1){
        output += '1';
    }
    if(number == 2){
        output += '2';
    }
    if(number == 3){
        output += '3';
    }
    if(number == 4){
        output += '4';
    }
    if(number == 5){
        output += '5';
    }
    if(number == 6){
        output += '6';
    }
    if(number == 7){
        output += '7';
    }
    if(number == 8){
        output += '8';
    }
    if(number == 9){
        output += '9';
    }
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
    if(column == 1){
        output += '1';
    }
    if(column == 2){
        output += '2';
    }
    if(column == 3){
        output += '3';
    }
    return output;
}
