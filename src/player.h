#ifndef PLAYER_H
#define PLAYER_H

#include <string>

struct Player {
    std::string name;
    char symbol;
};

Player create_player(char forbidden_symbol = '\0');

#endif 
