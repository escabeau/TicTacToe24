#include "AIPlayer.h"
#include <array>

bool can_win(const std::array<char, 9>& board, char symbol, int& move) {
    for (int i = 0; i < 3; ++i) {
        // lignes
        if (board[i * 3] == symbol && board[i * 3 + 1] == symbol && board[i * 3 + 2] != 'X' && board[i * 3 + 2] != 'O') {
            move = i * 3 + 2;
            return true;
        }
        if (board[i * 3] == symbol && board[i * 3 + 2] == symbol && board[i * 3 + 1] != 'X' && board[i * 3 + 1] != 'O') {
            move = i * 3 + 1;
            return true;
        }
        if (board[i * 3 + 1] == symbol && board[i * 3 + 2] == symbol && board[i * 3] != 'X' && board[i * 3] != 'O') {
            move = i * 3;
            return true;
        }

        //  colonnes
        if (board[i] == symbol && board[i + 3] == symbol && board[i + 6] != 'X' && board[i + 6] != 'O') {
            move = i + 6;
            return true;
        }
        if (board[i] == symbol && board[i + 6] == symbol && board[i + 3] != 'X' && board[i + 3] != 'O') {
            move = i + 3;
            return true;
        }
        if (board[i + 3] == symbol && board[i + 6] == symbol && board[i] != 'X' && board[i] != 'O') {
            move = i;
            return true;
        }
    }
    //  diagonales
    if (board[0] == symbol && board[4] == symbol && board[8] != 'X' && board[8] != 'O') {
        move = 8;
        return true;
    }
    if (board[0] == symbol && board[8] == symbol && board[4] != 'X' && board[4] != 'O') {
        move = 4;
        return true;
    }
    if (board[4] == symbol && board[8] == symbol && board[0] != 'X' && board[0] != 'O') {
        move = 0;
        return true;
    }
    if (board[2] == symbol && board[4] == symbol && board[6] != 'X' && board[6] != 'O') {
        move = 6;
        return true;
    }
    if (board[2] == symbol && board[6] == symbol && board[4] != 'X' && board[4] != 'O') {
        move = 4;
        return true;
    }
    if (board[4] == symbol && board[6] == symbol && board[2] != 'X' && board[2] != 'O') {
        move = 2;
        return true;
    }
    return false;
}

int get_ai_move(const std::array<char, 9>& board, char ia_symbol, char player_symbol) {
    int move = -1;

    
    if (can_win(board, ia_symbol, move)) {
        return move + 1;
    }

    if (can_win(board, player_symbol, move)) {
        return move + 1;
    }

    if (board[4] != 'X' && board[4] != 'O') {
        return 5;
    }

    if (board[0] != 'X' && board[0] != 'O' && board[0] != player_symbol) return 1;
    if (board[2] != 'X' && board[2] != 'O' && board[2] != player_symbol) return 3;
    if (board[6] != 'X' && board[6] != 'O' && board[6] != player_symbol) return 7;
    if (board[8] != 'X' && board[8] != 'O' && board[8] != player_symbol) return 9;

    if (board[1] != 'X' && board[1] != 'O' && board[1] != player_symbol) return 2;
    if (board[3] != 'X' && board[3] != 'O' && board[3] != player_symbol) return 4;
    if (board[5] != 'X' && board[5] != 'O' && board[5] != player_symbol) return 6;
    if (board[7] != 'X' && board[7] != 'O' && board[7] != player_symbol) return 8;

   
    for (int i = 0; i < 9; ++i) {
        if (board[i] != 'X' && board[i] != 'O') {
            return i + 1;
        }
    }

    return 0;
}
