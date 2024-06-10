#include "Board.h"
#include "Errors.h"
#include "Move.h"

#include <iostream>
#include <string>

using namespace std;

int nextplayer(int currentplayer, char input) {
    if(currentplayer == 0) {
        if(input == 'O') {
            return 1;
            // O
        }
        else {
            return 2;

        }
    }
    else if(currentplayer == 1 && input == 'X') {
        return 2;
        // X
    }
    else if(currentplayer == 2 && input == 'O') {
        return 1;
        // O
    }
    else {
        return 3;
    }
}

string checkposition(string currentboard, char row, char column, int currentplayer) {

    int row_index = 0;
    int column_index = 0;
    int position = 0;
    if(row == 'A') {
        row_index = 0;
    }
    else if(row == 'B') {
        row_index = 1;
    }
    else {
        row_index = 2;
    }
    column_index = int(column) - 48;
    position = 3 * row_index + column_index - 1;
    if(currentboard[position] == '-') {
        currentboard[position] = char(currentplayer + 48);
    }
    else {
        currentboard = "Error";
    }
    return currentboard;

}

int checkwin(string currentboard) {

    int result = 3;
    if(currentboard[0] == '1' && currentboard[1] == '1' && currentboard[2] == '1') {
        result = 1; // horizontal
    }
    else if(currentboard[0] == '2' && currentboard[1] == '2' && currentboard[2] == '2') {
        result = 2;
    }
    else if(currentboard[3] == '1' && currentboard[4] == '1' && currentboard[5] == '1') {
        result = 1;
    }
    else if(currentboard[3] == '2' && currentboard[4] == '2' && currentboard[5] == '2') {
        result = 2;
    }
    else if(currentboard[6] == '1' && currentboard[7] == '1' && currentboard[8] == '1') {
        result = 1;
    }
    else if(currentboard[6] == '2' && currentboard[7] == '2' && currentboard[8] == '2') {
        result = 2;
    }
    else if(currentboard[0] == '1' && currentboard[3] == '1' && currentboard[6] == '1') {
        result = 1; // vertical
    }
    else if(currentboard[0] == '2' && currentboard[3] == '2' && currentboard[6] == '2') {
        result = 2;
    }
    else if(currentboard[1] == '1' && currentboard[4] == '1' && currentboard[7] == '1') {
        result = 1;
    }
    else if(currentboard[1] == '2' && currentboard[4] == '2' && currentboard[7] == '2') {
        result = 2;
    }
    else if(currentboard[2] == '1' && currentboard[5] == '1' && currentboard[8] == '1') {
        result = 1;
    }
    else if(currentboard[2] == '2' && currentboard[5] == '2' && currentboard[8] == '2') {
        result = 2;
    }
    else if(currentboard[0] == '1' && currentboard[4] == '1' && currentboard[8] == '1') {
        result = 1; //diagonal
    }
    else if(currentboard[0] == '2' && currentboard[4] == '2' && currentboard[8] == '2') {
        result = 2;
    }
    else if(currentboard[2] == '1' && currentboard[4] == '1' && currentboard[6] == '1') {
        result = 1;
    }
    else if(currentboard[2] == '2' && currentboard[4] == '2' && currentboard[6] == '2') {
        result = 2;
    }
    else {
        result = 3;
    }

    return result;
    
}

int main() {

    string currentboard = "---------";
    int length = 0;
    int currentplayer = 0;
    int status_number = 0;

    string line;

    while(getline(cin, line)) {
        if(line.length() == 0) {
            status_number = 1;
            break;
        } 
        try {
            Move move(line);
            string input = move.to_string();
            
            currentplayer = nextplayer(currentplayer, input[2]);
            if(currentplayer != 3) {
                int move_number = int(input[0]) - 48;
                if(move_number == length + 1) {
                    length += 1;
                    int win_result = checkwin(currentboard);
                    currentboard = checkposition(currentboard, input[4], input[5], currentplayer);
                    if(currentboard != "Error" && win_result == 3) {
                        if(length == 9) {
                            break;
                        }
                        else {
                            continue;
                        }
                    }
                    else {
                        status_number = 2;
                        break;
                    }
                }
                else {
                    status_number = 2;
                    break;
                }
                // check number
            }
            else {
                status_number = 2;
                break;
            }
            // check player

        }
        catch(const ParseError& error) {
            if(line.length() == 0) {
                status_number = 0;
            }
            else {
                status_number = 1;
            }
        }
    }

    if(status_number == 1) {
        cout << "Parse error.\n";
    }
    else if(status_number == 2) {
        cout << "Invalid move.\n";
    }
    else {
        int winning = checkwin(currentboard);
        if(length == 0) {
            cout << "Game in progress: New game." << '\n';
        }
        else if(winning != 3) {
            if(winning == 2) {
                cout << "Game over: X wins." << '\n';
            }
            else {
                cout << "Game over: O wins." << '\n';
            }
        }
        else {
            if(length == 9) {
                cout << "Game over: Draw." << '\n';
            }
            else if(currentplayer == 1) {
                cout << "Game in progress: X's turn." << '\n';
            }
            else {
                cout << "Game in progress: O's turn." << '\n';
            }
        }
    }

    return status_number;

}
