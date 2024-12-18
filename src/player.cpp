#include "Player.h"
#include <iostream>
#include <cctype>

Player create_player(char forbidden_symbol) {
    Player player;

    std::cout << "Entrez le nom du joueur : ";
    std::cin >> player.name;

    std::cout << "Choisissez un symbole avec lequel jouer : ";
    std::cin >> player.symbol;


    while (player.symbol == ' ' || player.symbol == forbidden_symbol || 
           (player.symbol >= '1' && player.symbol <= '9')) {
        if (player.symbol == ' ') {
            std::cout << "Symbole invalide. Le symbole ne peut pas etre un espace vide. Choisissez un autre symbole : ";
        } else if (player.symbol >= '1' && player.symbol <= '9') {
            std::cout << "Symbole interdit. Vous ne pouvez pas utiliser un chiffre de 1 a 9. Choisissez un autre symbole : ";
        } else {
            std::cout << "Ce symbole est deja pris. Choisissez un autre symbole : ";
        }
        std::cin >> player.symbol;
    }

    return player;
}