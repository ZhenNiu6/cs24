#include "Errors.h"
#include "Board.h"
#include <iostream>

// Space for implementing Board functions.

Board::Board(){
    play = 'X';
    turns = 0;
    num = 0;
    board = new char*[3];
    for (size_t i = 0; i < 3; ++i) {
        board[i] = new char[3];
        for (size_t j = 0; j < 3; ++j) {
            board[i][j] = ' '; 
        }
    }
}

Board::~Board() {
    for(size_t i = 0; i < 3; ++i) {
        delete [] board[i];
    }
    delete [] board;
}


void Board::make_move(Move move){
    if(move.number != num + 1){
        throw InvalidMove("invalid move number");
    }
    if((play == move.player) && (turns != 0)){
        throw InvalidMove("need switch players");
    }
    if(board[move.row-1][move.column-1] != ' '){
        throw InvalidMove("space being occupied");
    }
    if(win() == true){
        throw InvalidMove("already have result");
    }
    board[move.row-1][move.column-1] = move.player;
    play = move.player;
    turns ++;
    num ++;
}

bool Board::win() const{
    for(size_t i = 0; i < 3; i ++){ // check rows
        for(size_t j = 0; j < 3; j ++){
            if(board[i][j] != play){
                break;
            }
            if(j == 2){
                return true;
            }
        }
    }

    for(size_t i = 0; i < 3; i ++){  // check columns
        for(size_t j = 0; j < 3; j ++){
            if(board[j][i] != play){
                break;
            }
            if(j == 2){
                return true;
            }
        }
    }

    for(size_t i = 0; i < 3; i ++){ // check one diagonal
        if(board[i][i] != play){
            break;
        }
        if(i == 2){
            return true;
        }
    }

    for(size_t i = 0; i < 3; i ++){
        if(board[i][3-i] != play){
            break;
        }
        if(i == 2){
            return true;
        }
    }

    return false;
}

void Board::result() const{
    if((win() == true) && (play == 'X')){
        std::cout << "Game over: X wins." << '\n';
    }
    else if((win() == true) && (play == 'O')){
        std::cout << "Game over: O wins." << '\n';
    }
    else{
        if(turns == 9){
            std::cout << "Game over: Draw." << '\n';
        }
        else if(turns == 0){
            std::cout << "Game in progress: New game." << '\n';
        }
        else{
            if(play == 'X'){
                std::cout << "Game in progress: O's turn." << '\n';
            }
            if(play == 'O'){
                std::cout << "Game in progress: X's turn." << '\n';
            }
        }
    }
}