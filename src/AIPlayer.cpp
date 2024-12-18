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

        // colonnes
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
    // diagonales
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

    // 1. Vérifie si l'IA peut gagner
    if (can_win(board, ia_symbol, move)) {
        return move + 1;
    }

    // 2. Bloque l'adversaire s'il peut gagner au prochain coup
    if (can_win(board, player_symbol, move)) {
        return move + 1;
    }

    // 3. Priorise le centre
    if (board[4] != 'X' && board[4] != 'O') {
        return 5;
    }

    // 4. Priorise les coins
    const int corners[] = {0, 2, 6, 8};
    for (int corner : corners) {
        if (board[corner] != 'X' && board[corner] != 'O') {
            return corner + 1;
        }
    }

    // 5. Choisis les côtés restants
    const int sides[] = {1, 3, 5, 7};
    for (int side : sides) {
        if (board[side] != 'X' && board[side] != 'O') {
            return side + 1;
        }
    }

    // 6. Dernier recours : Choisis la première case disponible
    for (int i = 0; i < 9; ++i) {
        if (board[i] != 'X' && board[i] != 'O') {
            return i + 1;
        }
    }

    // Si aucune case valide n'est trouvée (impossible dans une partie normale)
    return 0;
}
