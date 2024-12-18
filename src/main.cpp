#include <iostream>
#include <array>
#include <cstdlib>
#include "Player.h"
#include "AIPlayer.h"
#include "Random.h" // Inclusion du fichier Random.cpp

// Constantes pour les messages
const std::string INVALID_MOVE = "Mouvement invalide. Entrez un nombre entre 1 et 9.\n";
const std::string OCCUPIED_CELL = "Cette case est déjà occupée. Choisissez une autre case.\n";
const std::string CHOOSE_GAME_MODE = "1. Deux joueurs\n2. Contre l'IA\n";
const std::string CHOOSE_AI_LEVEL = "Choisissez le niveau de l'IA :\n1. Facile (Random)\n2. Expert\n";

int determine_first_player() {
    return rand() % 2 + 1; // 1 ou 2, pour déterminer qui commence
}

void draw_game_board(const std::array<char, 9>& board) {
    for (int i = 0; i < 9; i += 3) {
        std::cout << "| " << board[i] << " | " << board[i + 1] << " | " << board[i + 2] << " |\n";
    }
    std::cout << std::endl;
}

bool check_winner(const std::array<char, 9>& board, char symbol) {
    for (int i = 0; i < 9; i += 3) {
        if (board[i] == symbol && board[i + 1] == symbol && board[i + 2] == symbol) return true;
    }
    for (int i = 0; i < 3; ++i) {
        if (board[i] == symbol && board[i + 3] == symbol && board[i + 6] == symbol) return true;
    }
    return (board[0] == symbol && board[4] == symbol && board[8] == symbol) ||
           (board[2] == symbol && board[4] == symbol && board[6] == symbol);
}

bool is_board_full(const std::array<char, 9>& board) {
    for (char cell : board) {
        if (cell != 'X' && cell != 'O') return false;
    }
    return true;
}

int main() {
    std::cout << "Bienvenue dans Tic-Tac-Toe !\n";
    std::cout << CHOOSE_GAME_MODE;

    int game_mode;
    std::cin >> game_mode;

    while (game_mode != 1 && game_mode != 2) {
        std::cout << "Entrée invalide, choisissez 1 ou 2 : ";
        std::cin >> game_mode;
    }

    int ai_level = 0;
    if (game_mode == 2) {
        std::cout << CHOOSE_AI_LEVEL;
        std::cin >> ai_level;

        while (ai_level != 1 && ai_level != 2) {
            std::cout << "Entrée invalide, choisissez 1 ou 2 : ";
            std::cin >> ai_level;
        }
    }

    std::array<char, 9> board = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    Player player1 = create_player();
    Player player2 = (game_mode == 1) ? create_player(player1.symbol) : Player{"IA", (player1.symbol == 'X' ? 'O' : 'X')};

    int current_player = determine_first_player();
    Player* active_player = (current_player == 1) ? &player1 : &player2;

    std::cout << "Le joueur " << current_player << " commence !" << std::endl;

    // Si l'IA commence
    if (game_mode == 2 && active_player->name == "IA") {
        std::cout << "L'IA (" << (ai_level == 1 ? "facile" : "expert") << ") commence !\n";
        int move;
        if (ai_level == 1) {
            move = get_random_move(board); // IA facile
        } else {
            move = get_ai_move(board, player2.symbol, player1.symbol); // IA expert
        }
        board[move - 1] = active_player->symbol; // L'IA joue son coup
        std::cout << "IA joue en position " << move << "\n";
        draw_game_board(board);
        current_player = 3 - current_player; // Passe au joueur suivant
        active_player = &player1; // Le joueur humain joue ensuite
        std::cout << "Au tour de " << active_player->name << " !\n";
    }

    // Boucle principale du jeu
    while (true) {
        int move;
        if (game_mode == 2 && active_player->name == "IA") {
            if (ai_level == 1) {
                move = get_random_move(board); // IA facile
            } else {
                move = get_ai_move(board, player2.symbol, player1.symbol); // IA expert
            }
            std::cout << "IA joue en position " << move << "\n";
            board[move - 1] = active_player->symbol; // L'IA joue son coup
            draw_game_board(board);
        } else {
            draw_game_board(board); // Afficher le tableau pour le joueur humain
            while (true) {
                std::cout << active_player->name << " (" << active_player->symbol << "), entrez une case : ";
                std::cin >> move;

                if (move < 1 || move > 9) {
                    std::cout << INVALID_MOVE;
                } else if (board[move - 1] == 'X' || board[move - 1] == 'O') {
                    std::cout << OCCUPIED_CELL;
                } else {
                    break;
                }
            }
            board[move - 1] = active_player->symbol; // Le joueur joue son coup
        }

        if (check_winner(board, active_player->symbol)) {
            draw_game_board(board);
            std::cout << active_player->name << " a gagne !\n";
            break;
        }

        if (is_board_full(board)) {
            draw_game_board(board);
            std::cout << "Match nul !\n";
            break;
        }

        current_player = 3 - current_player; // Alternance entre 1 et 2
        active_player = (current_player == 1) ? &player1 : &player2;

        if (game_mode == 2 && active_player->name != "IA") {
            std::cout << "Au tour de " << active_player->name << " !\n";
        }
    }

    return 0;
}
