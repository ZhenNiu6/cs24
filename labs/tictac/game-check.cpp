#include "Board.h"
#include "Errors.h"
#include "Move.h"
#include <iostream>
#include <string>
#include <fstream>


int main() {
    Board board;
    // std::fstream newfile;
    // newfile.open("o-wins.ttt", std::ios::in);
    std::string line;
    while(std::getline(std::cin, line)){
        try{
            Move move(line);
            board.make_move(move);
            if(board.win()){
                break;
            }
        }
        catch(const ParseError& e){
            std::cout << "Parse error: " << e.what() << '\n';
            return 1;
        }
        catch(const InvalidMove& e){
            std::cout << "Invalid move: " << e.what() << '\n';
            return 2;
        }
    }
    board.result();
    return 0;

}
