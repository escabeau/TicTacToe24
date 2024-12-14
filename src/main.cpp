#include <iostream>
#include <array>
#include "Player.h"
#include "AIPlayer.h"

int determine_first_player() {
    return rand() % 2 + 1;  // 1 ou 2, pour determiner qui commence
}

void draw_game_board(const std::array<char, 9>& board) {
    for (int i = 0; i < 9; i += 3) {
        std::cout << "| " << board[i] << " | " << board[i + 1] << " | " << board[i + 2] << " |\n";
    }
    std::cout << std::endl;
}

bool check_winner(const std::array<char, 9>& board, char symbol) {
    for (int i = 0; i < 9; i += 3) {
        if (board[i] == symbol && board[i + 1] == symbol && board[i + 2] == symbol)
            return true;
    }
    for (int i = 0; i < 3; ++i) {
        if (board[i] == symbol && board[i + 3] == symbol && board[i + 6] == symbol)
            return true;
    }
    if ((board[0] == symbol && board[4] == symbol && board[8] == symbol) ||
        (board[2] == symbol && board[4] == symbol && board[6] == symbol))
        return true;

    return false;
}

bool is_board_full(const std::array<char, 9>& board) {
    for (char cell : board) {
        if (cell != 'X' && cell != 'O') 
            return false;
    }
    return true;
}

int main() {
    std::cout << "Bienvenue dans Tic-Tac-Toe !\n";
    std::cout << "1. Deux joueurs\n2. Contre l'IA\n";
    int game_mode;
    std::cin >> game_mode;

    // Verification de la validite du mode de jeu
    while (game_mode != 1 && game_mode != 2) {
        std::cout << "Entree invalide, choisissez 1 ou 2 : ";
        std::cin >> game_mode;
    }

    // Initialisation du tableau de jeu
    std::array<char, 9> board = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

    // Creation des joueurs
    Player player1 = create_player();
    Player player2;

    if (game_mode == 1) {
        player2 = create_player(player1.symbol); 
    } else {
        char ai_symbol = (player1.symbol == 'X' || player1.symbol == 'O') ? 'O' : 'X';
        player2 = {"IA", ai_symbol};
    }

    // Determination du premier joueur
    int first_player = determine_first_player();
    int current_player = first_player; 
    Player* active_player = (first_player == 1) ? &player1 : &player2;

    std::cout << "Le joueur " << current_player << " commence !" << std::endl;

    while (true) {
        draw_game_board(board);

        int move;
        if (game_mode == 2 && active_player->name == "IA") {
            move = get_ai_move(board, player2.symbol, player1.symbol);
            std::cout << "IA joue en position " << move << "\n";
        } else {
            bool valid_move = false;
            while (!valid_move) {
                std::cout << active_player->name << " (" << active_player->symbol << "), entrez une case : ";
                std::cin >> move;

                if (move < 1 || move > 9) {
                    std::cout << "Mouvement invalide. Entrez un nombre entre 1 et 9.\n";
                } else if (board[move - 1] != '1' && board[move - 1] != '2' && board[move - 1] != '3' &&
                           board[move - 1] != '4' && board[move - 1] != '5' && board[move - 1] != '6' &&
                           board[move - 1] != '7' && board[move - 1] != '8' && board[move - 1] != '9') {
                    std::cout << "Cette case est deja occupee. Choisissez une autre case.\n";
                } else {
                    valid_move = true;
                }
            }
        }

        // Placement du symbole dans la case choisie
        board[move - 1] = active_player->symbol;

        // Verification de la victoire
        if (check_winner(board, active_player->symbol)) {
            draw_game_board(board);
            std::cout << active_player->name << " a gagne !\n";
            break;
        }

        // Verification d'un match nul
        if (is_board_full(board)) {
            draw_game_board(board);
            std::cout << "Match nul !\n";
            break;
        }

        // Changement de joueur
        current_player = (current_player == 1) ? 2 : 1;
        active_player = (current_player == 1) ? &player1 : &player2;
    }

    return 0;
}
