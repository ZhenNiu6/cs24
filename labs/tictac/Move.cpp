#include "Errors.h"
#include "Move.h"
#include <cctype>
#include <string>
#include <iostream>

// Space for implementing Move functions.

// Move::Move(const std::string& input){
//     // Check number
//     int a;
//     size_t index = 0;
//     if(isdigit(input[index]) && isdigit(input[index+1])){
//         std::string temp = "";
//         temp += input[index];
//         temp += input[index+1];
//         a = stoi(temp);
//     }
//     else{
//         throw ParseError("Invalid move number");
//     }
//     if((a < 48) || (a > 57)){
//         throw ParseError("Invalid move number");
//     }
//     number = a - '0';


//     // Check whitespace
//     size_t n = 0;
//     for(size_t i = 2; i < input.length(); i ++){
//         if(isspace(input[i])){
//             n ++;
//             continue;
//         }
//         else{
//             index = i;
//             if(n < 1){
//                 throw ParseError("Invalid whitespace 1");
//             }
//             break;
//         }
//     }
//     n = 0;


//     // Check player
//     bool h = false;
//     if(isdigit(input[index]) && isdigit(input[index+1])){
//         std::string temp = "";
//         temp += input[index];
//         temp += input[index+1];
//         if(isdigit(input[index+2])){
//             temp += input[index+2];
//             h = true;
//         }
//         a = stoi(temp);
//     }
//     else{
//         throw ParseError("Invalid player code");
//     }
//     if((a != 88) && (a != 120) && (a != 48)){
//         throw ParseError("Invalid player code");
//     }
//     if((a == 88) || (a == 120)){
//         char p = a;
//         player = toupper(p);
//     }
//     if(a == 48){
//         char p = a;
//         player = p;
//     }
//     if(h){
//         index += 3;
//     }
//     else{
//         index += 2;
//     }
    
//     // Check whitespace
//     for(size_t i = index; i < input.length(); i ++){
//         if(isspace(input[i])){
//             n ++;
//             continue;
//         }
//         else{
//             index = i;
//             if(n < 1){
//                 throw ParseError("Invalid whitespace 2");
//             }
//             break;
//         }
//     }
//     n = 0;

//     // Check row
//     if(isdigit(input[index]) && isdigit(input[index+1])){
//         std::string temp = "";
//         temp += input[index];
//         temp += input[index+1];
//         a = stoi(temp);
//     }
//     else{
//         throw ParseError("Invalid square code");
//     }
//     if((a != 65) && (a != 66) && (a != 67) && (a != 97) && (a != 98) && (a != 99)){
//         throw ParseError("Invalid square code");
//     }
//     int r = a;
//     if((a == 97) || (a == 98) || (a == 99)){
//         r = a - 32;
//     }
//     row = r - '@'; // Row A = 1, Row B = 2, Row C = 3;
//     index += 2;

//     // Check column
//     if(isdigit(input[index]) && isdigit(input[index+1])){
//         std::string temp = "";
//         temp += input[index];
//         temp += input[index+1];
//         a = stoi(temp);
//     }
//     else{
//         throw ParseError("Invalid square code");
//     }
//     if((a != 49) && (a != 50) && (a != 51)){
//         throw ParseError("Invalid square code");
//     }
//     column = a - '0';

//     index += 2;


//     // Check extra whitespace and comment
//     if(index < input.length()){
//         for(size_t i = index; i < input.length(); i ++){
//             if(isspace(input[i])){
//                 n ++;
//             }
//             else{
//                 index = i;
//                 if(n < 1){
//                     if((index+1) < input.length()){
//                         if(isdigit(input[index]) && isdigit(input[index+1])){
//                             std::string temp = "";
//                             temp += input[index];
//                             temp += input[index+1];
//                             a = stoi(temp);
//                         }
//                         if(a == 35){
//                             throw ParseError("Invalid whitespace 3");
//                         }
//                     }
//                 }
//                 break;
//             }
//             if(i == (input.length()-1)){
//                 index += n;
//             }
//         }
//         n = 0;
//     }

//     // Check comment
//     if((index+1) < input.length()){
//         std::cout << "here" << '\n';
//         if(isdigit(input[index]) && isdigit(input[index+1])){
//             std::string temp = "";
//             temp += input[index];
//             temp += input[index+1];
//             a = stoi(temp);
//             std::cout << a << '\n';
//         }
//         else{
//             throw ParseError("Invalid comment");
//         }
//         if(a != 35){
//             throw ParseError("Invalid comment");
//         }
//     }
// }





Move::Move(const std::string& input){
    // Check number
    size_t index = 0;
    if(!isdigit(input[index])){
        throw ParseError("Invalid move number");
    }
    if(input[index] == '0'){
        throw ParseError("Invalid move number");
    }
    number = input[index];
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
    column = input[index];
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
                    if(!isspace(input[i+1])){
                        throw ParseError("Invalid comment");
                    }
                }
                break;
                // index = i;
                // if(n < 1){
                //     throw ParseError("Invalid whitespace");
                // }
                // break;
            }
        }
        // index += n;
        // n = 0;
    }
    // std::cout << index << '\n';

    // Check comment
    // if(index < input.length()){
    //     if(input[index] != '#'){
    //         throw ParseError("Invalid comment");
    //     }
    // }
}


std::string Move::to_string() const{
    std::string output = "";
    output += number;
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
    output += column;
    return output;
}
