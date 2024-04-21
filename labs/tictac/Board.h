#ifndef BOARD_H
#define BOARD_H

#include "Move.h"

// I recommended writing a Board class to manage your game state.
// Here's some space for the class definition; member functions go in Board.cpp.

class Board{
    char play;  // player
    char** board;
    size_t turns;

public:
    Board();
    ~Board();
    void make_move(Move move);
    bool win() const;
    void result() const;
};

#endif
