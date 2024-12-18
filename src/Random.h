#ifndef RANDOM_H
#define RANDOM_H

#include <array>

void initialize_random();


int get_random_move(const std::array<char, 9>& board);

#endif 
