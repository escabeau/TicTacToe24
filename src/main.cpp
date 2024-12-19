#include <raylib.h>
#include <array>
#include <string>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cctype>

const int SCREEN_WIDTH = 660;
const int SCREEN_HEIGHT = 660;
const int GAME_BOARD_SIZE = static_cast<int>(SCREEN_WIDTH * 0.8);
const int BUTTON_WIDTH = 200;
const int BUTTON_HEIGHT = 50;
const int FONT_SIZE = 20;

enum GameState { MENU, CHOOSE_MODE, PLAYER_SETUP, PLAYING, GAME_OVER };
GameState gameState = MENU;

std::string player1Name = "Joueur 1";
std::string player2Name = "Joueur 2";
char player1Symbol = 'X';
char player2Symbol = 'O';
bool player1Turn = true;
std::array<char, 9> board = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
bool isAI = false;
bool isEasyAI = true;
bool playerSetupComplete = false;
std::string gameOverMessage = "";
double gameOverTime = 0;

int get_random_move(const std::array<char, 9>& board);
int get_ai_move(const std::array<char, 9>& board, char ia_symbol, char player_symbol);

bool DrawButton(int x, int y, const char *text) {
    Rectangle button = { (float)x, (float)y, (float)BUTTON_WIDTH, (float)BUTTON_HEIGHT };
    bool hovered = CheckCollisionPointRec(GetMousePosition(), button);

    DrawRectangleRec(button, hovered ? GRAY : LIGHTGRAY);
    DrawRectangleLinesEx(button, 2, BLACK);
    DrawText(text, x + BUTTON_WIDTH / 2 - MeasureText(text, FONT_SIZE) / 2, y + BUTTON_HEIGHT / 2 - FONT_SIZE / 2, FONT_SIZE, BLACK);

    return hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void DrawGameBoard() {
    int cellSize = GAME_BOARD_SIZE / 3;
    int offsetX = (SCREEN_WIDTH - GAME_BOARD_SIZE) / 2;
    int offsetY = (SCREEN_HEIGHT - GAME_BOARD_SIZE) / 2;
    for (int i = 0; i < 4; i++) {
        DrawLine(offsetX + i * cellSize, offsetY, offsetX + i * cellSize, offsetY + GAME_BOARD_SIZE, BLACK);
        DrawLine(offsetX, offsetY + i * cellSize, offsetX + GAME_BOARD_SIZE, offsetY + i * cellSize, BLACK);
    }
    for (int i = 0; i < 9; i++) {
        int x = offsetX + (i % 3) * cellSize;
        int y = offsetY + (i / 3) * cellSize;
        std::string symbol(1, board[i]);
        DrawText(symbol.c_str(), x + cellSize / 2 - FONT_SIZE / 2, y + cellSize / 2 - FONT_SIZE / 2, FONT_SIZE, BLACK);
    }
}

int GetClickedCell() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        int cellSize = GAME_BOARD_SIZE / 3;
        int offsetX = (SCREEN_WIDTH - GAME_BOARD_SIZE) / 2;
        int offsetY = (SCREEN_HEIGHT - GAME_BOARD_SIZE) / 2;
        if (mousePos.x < offsetX || mousePos.x > offsetX + GAME_BOARD_SIZE || mousePos.y < offsetY || mousePos.y > offsetY + GAME_BOARD_SIZE) {
            return -1;
        }
        int row = static_cast<int>((mousePos.y - offsetY) / cellSize);
        int col = static_cast<int>((mousePos.x - offsetX) / cellSize);
        int cellIndex = row * 3 + col;
        if (cellIndex >= 0 && cellIndex < 9 && board[cellIndex] != 'X' && board[cellIndex] != 'O') {
            return cellIndex;
        }
    }
    return -1;
}

bool CheckWinner(char symbol) {
    for (int i = 0; i < 9; i += 3) {
        if (board[i] == symbol && board[i + 1] == symbol && board[i + 2] == symbol) return true;
    }
    for (int i = 0; i < 3; ++i) {
        if (board[i] == symbol && board[i + 3] == symbol && board[i + 6] == symbol) return true;
    }
    return (board[0] == symbol && board[4] == symbol && board[8] == symbol) ||
           (board[2] == symbol && board[4] == symbol && board[6] == symbol);
}

bool CheckDraw() {
    for (char cell : board) {
        if (isdigit(cell)) {
            return false;
        }
    }
    return true;
}

int get_random_move(const std::array<char, 9>& board) {
    srand(static_cast<unsigned>(time(0)));
    while (true) {
        int move = rand() % 9;
        if (isdigit(board[move])) {
            return move;
        }
    }
}

bool can_win(const std::array<char, 9>& board, char symbol, int& move) {
    for (int i = 0; i < 3; ++i) {
        if (board[i * 3] == symbol && board[i * 3 + 1] == symbol && isdigit(board[i * 3 + 2])) {
            move = i * 3 + 2;
            return true;
        }
        if (board[i * 3] == symbol && board[i * 3 + 2] == symbol && isdigit(board[i * 3 + 1])) {
            move = i * 3 + 1;
            return true;
        }
        if (board[i * 3 + 1] == symbol && board[i * 3 + 2] == symbol && isdigit(board[i * 3])) {
            move = i * 3;
            return true;
        }
    }

    for (int i = 0; i < 3; ++i) {
        if (board[i] == symbol && board[i + 3] == symbol && isdigit(board[i + 6])) {
            move = i + 6;
            return true;
        }
        if (board[i] == symbol && board[i + 6] == symbol && isdigit(board[i + 3])) {
            move = i + 3;
            return true;
        }
        if (board[i + 3] == symbol && board[i + 6] == symbol && isdigit(board[i])) {
            move = i;
            return true;
        }
    }

    if (board[0] == symbol && board[4] == symbol && isdigit(board[8])) {
        move = 8;
        return true;
    }
    if (board[0] == symbol && board[8] == symbol && isdigit(board[4])) {
        move = 4;
        return true;
    }
    if (board[4] == symbol && board[8] == symbol && isdigit(board[0])) {
        move = 0;
        return true;
    }
    if (board[2] == symbol && board[4] == symbol && isdigit(board[6])) {
        move = 6;
        return true;
    }
    if (board[2] == symbol && board[6] == symbol && isdigit(board[4])) {
        move = 4;
        return true;
    }
    if (board[4] == symbol && board[6] == symbol && isdigit(board[2])) {
        move = 2;
        return true;
    }

    return false;
}

int get_ai_move(const std::array<char, 9>& board, char ia_symbol, char player_symbol) {
    int move = -1;

    if (can_win(board, ia_symbol, move)) {
        return move;
    }

    if (can_win(board, player_symbol, move)) {
        return move;
    }

    if (isdigit(board[4])) {
        return 4;
    }

    const int corners[] = {0, 2, 6, 8};
    for (int corner : corners) {
        if (isdigit(board[corner])) {
            return corner;
        }
    }

    const int sides[] = {1, 3, 5, 7};
    for (int side : sides) {
        if (isdigit(board[side])) {
            return side;
        }
    }

    return move;
}

void ResetBoard() {
    board = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    player1Turn = true;
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tic-Tac-Toe");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (gameState) {
            case MENU:
                DrawText("Tic-Tac-Toe", SCREEN_WIDTH / 2 - MeasureText("Tic-Tac-Toe", 40) / 2, 50, 40, BLACK);
                if (DrawButton(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, 200, "Jouer")) {
                    gameState = CHOOSE_MODE;
                }
                if (DrawButton(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, 300, "Quitter")) {
                    CloseWindow();
                    return 0;
                }
                break;

            case CHOOSE_MODE:
                DrawText("Choisissez le mode de jeu :", 50, 50, 20, BLACK);
                if (DrawButton(50, 150, "Deux Joueurs")) {
                    isAI = false;
                    gameState = PLAYER_SETUP;
                }
                if (DrawButton(50, 250, "IA Facile")) {
                    isAI = true;
                    isEasyAI = true;
                    player2Name = "Ordi (Facile)";
                    gameState = PLAYER_SETUP;
                }
                if (DrawButton(50, 350, "IA Difficile")) {
                    isAI = true;
                    isEasyAI = false;
                    player2Name = "Ordi (Difficile)";
                    gameState = PLAYER_SETUP;
                }
                break;

            case PLAYER_SETUP:
                DrawText("Configuration des joueurs :", 50, 50, 20, BLACK);
                if (!playerSetupComplete) {
                    static char input[64] = {0};
                    static bool player1NameEntered = false;

                    if (!player1NameEntered) {
                        DrawText("Entrez le nom du Joueur 1 :", 50, 150, 20, BLACK);
                        DrawText("Appuyez sur ENTRER pour valider", 50, 180, 15, GRAY);

                        int key = GetKeyPressed();
                        if (key >= 32 && key <= 125 && strlen(input) < sizeof(input) - 1) {
                            int len = static_cast<int>(strlen(input));
                            input[len] = (char)key;
                            input[len + 1] = '\0';
                        }
                        if (IsKeyPressed(KEY_BACKSPACE) && strlen(input) > 0) {
                            input[strlen(input) - 1] = '\0';
                        }
                        if (IsKeyPressed(KEY_ENTER)) {
                            player1Name = std::string(input);
                            memset(input, 0, sizeof(input));
                            player1NameEntered = true;
                        }
                    } else {
                        DrawText("Entrez le nom du Joueur 2 :", 50, 150, 20, BLACK);
                        DrawText("Appuyez sur ENTRER pour valider", 50, 180, 15, GRAY);

                        int key = GetKeyPressed();
                        if (key >= 32 && key <= 125 && strlen(input) < sizeof(input) - 1) {
                            int len = static_cast<int>(strlen(input));
                            input[len] = (char)key;
                            input[len + 1] = '\0';
                        }
                        if (IsKeyPressed(KEY_BACKSPACE) && strlen(input) > 0) {
                            input[strlen(input) - 1] = '\0';
                        }
                        if (IsKeyPressed(KEY_ENTER)) {
                            player2Name = std::string(input);
                            player2Symbol = 'O';
                            playerSetupComplete = true;
                        }
                    }
                } else {
                    playerSetupComplete = true;
                }

                if (playerSetupComplete) {
                    gameState = PLAYING;
                }
                break;

            case PLAYING:
                DrawGameBoard();

                DrawText((player1Turn ? player1Name : player2Name).c_str(), 10, 10, 20, BLACK);

                {
                    int clickedCell = GetClickedCell();
                    if (clickedCell != -1) {
                        char currentSymbol = player1Turn ? player1Symbol : player2Symbol;
                        board[clickedCell] = currentSymbol;

                        if (CheckWinner(currentSymbol)) {
                            std::string winnerName = player1Turn ? player1Name : player2Name;
                            gameOverMessage = winnerName + " a gagné!";
                            gameOverTime = GetTime();
                            gameState = GAME_OVER;
                        } else if (CheckDraw()) {
                            gameOverMessage = "Egalité !";
                            gameOverTime = GetTime();
                            gameState = GAME_OVER;
                        } else {
                            player1Turn = !player1Turn;

                            if (isAI && !player1Turn) {
                                int aiMove = isEasyAI ? get_random_move(board) : get_ai_move(board, player2Symbol, player1Symbol);
                                board[aiMove] = player2Symbol;

                                if (CheckWinner(player2Symbol)) {
                                    gameOverMessage = player2Name + " a gagné!";
                                    gameOverTime = GetTime();
                                    gameState = GAME_OVER;
                                } else if (CheckDraw()) {
                                    gameOverMessage = "Egalité !";
                                    gameOverTime = GetTime();
                                    gameState = GAME_OVER;
                                }

                                player1Turn = true;
                            }
                        }
                    }
                }

                if (DrawButton(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT - 100, "Retour au menu")) {
                    ResetBoard();
                    gameState = MENU;
                }
                break;

            case GAME_OVER:
                DrawGameBoard();
                DrawText(gameOverMessage.c_str(), SCREEN_WIDTH / 2 - MeasureText(gameOverMessage.c_str(), 30) / 2, SCREEN_HEIGHT / 2 - 15, 30, RED);
                if (GetTime() - gameOverTime > 3) {
                    if (DrawButton(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT - 100, "Rejouer")) {
                        ResetBoard();
                        gameState = PLAYING;
                    }
                    if (DrawButton(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT - 50, "Retour au menu")) {
                        ResetBoard();
                        gameState = MENU;
                    }
                }
                break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}