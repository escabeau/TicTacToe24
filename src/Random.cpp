#include <array>
#include <cstdlib>
#include <ctime>
#include <cctype> // Pour std::isdigit

// Initialise le générateur de nombres aléatoires
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
        int move = rand() % 9; // Génère un index entre 0 et 8
        // Vérifie que la case est valide (contient un chiffre)
        if (std::isdigit(board[move])) {
            return move + 1; // Retourne une case valide
        }
    }
}
