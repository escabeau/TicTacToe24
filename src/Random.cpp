#include <array>
#include <cstdlib>
#include <ctime>
#include <cctype> 

void initialize_random() {
    static bool initialized = false;
    if (!initialized) {
        srand(static_cast<unsigned>(time(0)));
        initialized = true;
    }
}

int get_random_move(const std::array<char, 9>& board) {
    initialize_random();
    while (true) {
        int move = rand() % 9; 
    
        if (std::isdigit(board[move])) {
            return move + 1; 
        }
    }
}
