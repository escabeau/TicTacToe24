#include <iostream>
#include <array>
#include <string>
#include <cctype>

struct Player {
    std::string name;
    char symbol;
};

Player create_player() {
    Player player;
    std::cout << "Entrez le nom du joueur : ";
    std::cin >> player.name;

    do {
        std::cout << player.name << ", choisissez votre symbole (X ou O) : ";
        std::cin >> player.symbol;
        player.symbol = toupper(player.symbol);
    } while (player.symbol != 'X' && player.symbol != 'O');

    return player;
}

void draw_game_board(const std::array<char, 9>& board) {
    for (int i = 0; i < 9; i += 3) {
        std::cout << "| " << board[i] << " | " << board[i + 1] << " | " << board[i + 2] << " |\n";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "Bienvenue dans le jeu Tic-Tac-Toe !\n";
    std::cout << "Choisissez le mode de jeu:\n1. Deux joueurs\n2. Contre l'IA\n";
    int game_mode;
    std::cin >> game_mode;

    while (game_mode != 1 && game_mode != 2) {
        std::cout << "Entrée invalide. Veuillez choisir 1 ou 2 : ";
        std::cin >> game_mode;
    }

    std::array<char, 9> board = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

    draw_game_board(board);

    Player player1 = create_player();
    Player player2;

    if (game_mode == 1) {
        player2 = create_player();
        while (player1.symbol == player2.symbol) {
            std::cout << "Le symbole est deja pris par " << player1.name << ". Veuillez choisir un autre symbole.\n";
            player2 = create_player();
        }
    } else {
        player2.name = "IA";
        player2.symbol = (player1.symbol == 'X') ? 'O' : 'X';
    }

    std::cout << player1.name << " jouera avec le symbole " << player1.symbol << ".\n";
    std::cout << player2.name << " jouera avec le symbole " << player2.symbol << ".\n";

    return 0;
}
