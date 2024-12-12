#include "Player.h"
#include <iostream>
#include <cctype>


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
