#include "Errors.h"
#include "Move.h"
#include <iostream>
#include <cctype>

using namespace std;

// Space for implementing Move functions.

Move::Move(const std::string& input) {

    int length = input.length();
    if(length < 6) {
        throw ParseError("Invalid Move 1");
    }
    else if(length == 6) {
        char num = input[0];
        char play = input[2];
        char ro = input[4];
        char col = input[5];
        if((num >= '1' && num <= '9') && (input[1] == ' ' || input[1] == '\t') && (play == 'O' || play == 'o' || play == 'X' || play == 'x') && (input[3] == ' ' || input[3] == '\t') && (ro == 'A' || ro == 'B' || ro == 'C' || ro == 'a' || ro == 'b' || ro == 'c') && (col >= '1' && col <= '3')) {
            number = int(num) - 48;
            player = play;
            column = int(col) - 48;
            if(ro < 'a') {
                row = int(ro) - 64;
            }
            else {
                row = int(ro) - 96;
            }
        }
        else {
            throw ParseError("Invalid Move 2");
        }
    }
    else {
        string temp = "";
        for(int i = 0; i < length; ++i) {
            if(input[i] == ' ' || input[i] == '\t') {
                continue;
            }
            else {
                temp += input[i];
            }
        }
        size_t comment_index = temp.find('#');
        if(comment_index >= size_t(length)) {
            int temp_length = temp.length();
            if(temp_length < 4) {
                throw ParseError("Invalid Move 3");
            }
            else if(temp_length == 4) {
                char num = temp[0];
                char play = temp[1];
                char ro = temp[2];
                char col = temp[3];
                size_t play_index = input.find(play);
                size_t ro_index = input.find(ro);
                size_t col_index = input.find(col, 1);
                if((num >= '1' && num <= '9') && (play == 'O' || play == 'o' || play == 'X' || play == 'x') && (ro == 'A' || ro == 'B' || ro == 'C' || ro == 'a' || ro == 'b' || ro == 'c') && (col >= '1' && col <= '3')) {
                    if(isspace(input[play_index - 1]) && (isspace(input[ro_index - 1])) && (ro_index == col_index - 1)) {
                        number = int(num) - 48;
                        player = play;
                        column = int(col) - 48;
                        if(ro < 'a') {
                            row = int(ro) - 64;
                        }
                        else {
                            row = int(ro) - 96;
                        }
                    }
                    else {
                        throw ParseError("Invalid Move 4");
                    }
                }
                else {
                    throw ParseError("Invalid Move 5");
                }
            }
            else {
                throw ParseError("Invalid Move 6");
            }
        }
        else {
            int temp_length = temp.length();
            if(temp_length < 5) {
                throw ParseError("Invalid Move 7");
            }
            else {
                char num = temp[0];
                char play = temp[1];
                char ro = temp[2];
                char col = temp[3];
                char comment = temp[4];
                size_t play_index = input.find(play);
                size_t ro_index = input.find(ro);
                size_t col_index = input.find(col, 1);
                size_t comment_index = input.find(comment);
                if((num >= '1' && num <= '9') && (play == 'O' || play == 'o' || play == 'X' || play == 'x') && (ro == 'A' || ro == 'B' || ro == 'C' || ro == 'a' || ro == 'b' || ro == 'c') && (col >= '1' && col <= '3') && (comment == '#')) {
                    if(isspace(input[play_index - 1]) && isspace(input[ro_index - 1]) && (ro_index == col_index - 1) && isspace(input[comment_index - 1])) {
                        number = int(num) - 48;
                        player = play;
                        column = int(col) - 48;
                        if(ro < 'a') {
                            row = int(ro) - 64;
                        }
                        else {
                            row = int(ro) - 96;
                        }
                    }
                    else {
                        throw ParseError("Invalid Move 8");
                    }
                }
                else {
                    throw ParseError("Invalid Move 9");
                }
            }
        }
    }
}

std::string Move::to_string() const {

    string result = "";
    char num = number + 48;
    char ro = row + 64;
    char col = column + 48;
    char play = ' ';
    if(player < 'a') {
        play = player;
    }
    else {
        play = player - 32;
    }
    result = result + num + ' ' + play + ' ' + ro + col;
    return result;

}
