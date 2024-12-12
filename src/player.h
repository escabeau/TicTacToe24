#ifndef PLAYER_H
#define PLAYER_H

#include <string>

// Structure Player
struct Player {
    std::string name;
    char symbol;
};

// Fonction pour créer un joueur
Player create_player();

#endif // PLAYER_H
