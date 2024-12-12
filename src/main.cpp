#include <iostream>
#include <array>
#include "Player.h"


void draw_game_board(const std::array<char, 9>& board) {
    for (int i = 0; i < 9; i += 3) {
        std::cout << "| " << board[i] << " | " << board[i + 1] << " | " << board[i + 2] << " |\n";
    }
    std::cout << std::endl;
}


bool check_winner(const std::array<char, 9>& board, char symbol) {
    // lignes
    for (int i = 0; i < 9; i += 3) {
        if (board[i] == symbol && board[i + 1] == symbol && board[i + 2] == symbol)
            return true;
    }
    // colonnes
    for (int i = 0; i < 3; ++i) {
        if (board[i] == symbol && board[i + 3] == symbol && board[i + 6] == symbol)
            return true;
    }
    // diagonales
    if ((board[0] == symbol && board[4] == symbol && board[8] == symbol) ||
        (board[2] == symbol && board[4] == symbol && board[6] == symbol))
        return true;

    return false;
}

// le plateau est plein
bool is_board_full(const std::array<char, 9>& board) {
    for (char cell : board) {
        if (cell != 'X' && cell != 'O') {
            return false;
        }
    }
    return true;
}

int main() {
    std::cout << "Bienvenue dans le jeu Tic-Tac-Toe !\n";
    std::cout << "Choisissez le mode de jeu:\n1. Deux joueurs\n2. Contre l'IA\n";
    int game_mode;
    std::cin >> game_mode;

    while (game_mode != 1 && game_mode != 2) {
        std::cout << "Entree invalide. Veuillez choisir 1 ou 2 : ";
        std::cin >> game_mode;
    }

    std::array<char, 9> board = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

    Player player1 = create_player();
    Player player2;
    if (game_mode == 1) {
        player2 = create_player();
        while (player1.symbol == player2.symbol) {
            std::cout << "Le symbole est déjà pris par " << player1.name << ". Veuillez choisir un autre symbole.\n";
            player2 = create_player();
        }
    } else {
        player2.name = "IA";
        player2.symbol = (player1.symbol == 'X') ? 'O' : 'X';
    }

    std::cout << player1.name << " jouera avec le symbole " << player1.symbol << ".\n";
    std::cout << player2.name << " jouera avec le symbole " << player2.symbol << ".\n";

    int current_player = 1;
    Player* active_player = &player1;

    while (true) {
        draw_game_board(board);

        int move;
        std::cout << active_player->name << " (" << active_player->symbol << "), entrez un numero de case (1-9) : ";
        std::cin >> move;

       
        while (move < 1 || move > 9 || (board[move - 1] == 'X' || board[move - 1] == 'O')) {
            std::cout << "Mouvement invalide. Essayez a nouveau : ";
            std::cin >> move;
        }

        board[move - 1] = active_player->symbol;

        //victoire
        if (check_winner(board, active_player->symbol)) {
            draw_game_board(board);
            std::cout << active_player->name << " a gagne la partie ! Felicitations !\n";
            break;
        }

       //match nul
        if (is_board_full(board)) {
            draw_game_board(board);
            std::cout << "Match nul !\n";
            break;
        }

   
        current_player = (current_player == 1) ? 2 : 1;
        active_player = (current_player == 1) ? &player1 : &player2;
    }

    return 0;
}
