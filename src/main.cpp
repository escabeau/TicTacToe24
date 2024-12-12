#include <iostream>
#include <array>
#include <string>
#include <cstdlib>
#include <ctime>


void draw_game_board(const std::array<char, 9>& board) {
    for (int i = 0; i < 9; i += 3) {
        std::cout << "| " << board[i] << " | " << board[i + 1] << " | " << board[i + 2] << " |\n";
    }
}

int main() {
    std::cout << "Bienvenue dans le jeu Tic-Tac-Toe !\n";
    std::cout << "Choisissez le mode de jeu:\n1. Deux joueurs\n2. Contre l'IA\n"; // verif avec suite @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    int game_mode;
    std::cin >> game_mode;

    
    std::array<char, 9> board = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

    
    draw_game_board(board);

    return 0;
}
struct Player {
    std::string name;
    char symbol; // X ou O
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
