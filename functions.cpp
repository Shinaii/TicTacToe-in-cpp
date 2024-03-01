#include "func.h"
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <chrono>
#include <thread>





//Prints
void printBoard(char board[3][3]) {
    std::cout << std::setw(4) << "0" << std::setw(4) << "1" << std::setw(4) << "2" << std::endl;
    std::cout << "  ┌───┬───┬───┐" << std::endl;
    for (int i = 0; i < 3; i++) {
        std::cout << i;
        for (int j = 0; j < 3; j++) {
            std::cout << " │" << std::setw(2) << board[i][j];
        }
        std::cout << " │" << std::endl;
        if (i < 2) {
            std::cout << "  ├───┼───┼───┤" << std::endl;
        }
    }
    std::cout << "  └───┴───┴───┘" << std::endl;
}
void printWelcome() {
    bool flag = true;

    std::cout << "Willkommen zu Tic Tac Toe!" << std::endl;
    std::cout << "Drücken sie die Linke Maustaste um das Spiel zu starten." << std::endl;

    while (flag) {
        if (GetKeyState(VK_LBUTTON) & 0x8000) {
            std::cout << "Das Spiel beginnt!" << std::endl;
            flag = false;
        }
    }
}
void chooseGameMode() {
    int choice;
    std::cout << "Welchen Modus wollen sie Spielen?\n";
    std::cout << "1. Player vs Player\n";
    std::cout << "2. Player vs Computer Easy\n";
    std::cout << "3. Player vs Computer Medium\n";
    std::cout << "4. Player vs Computer Hard\n";
    std::cout << "Ihre Auswahl: ";
    std::cin >> choice;

    char board[3][3] = {{' ', ' ', ' '},
                        {' ', ' ', ' '},
                        {' ', ' ', ' '}};

    switch (choice) {
        case 1:
            gamePvP();
            break;
        case 2:
            gameLoop(board, false, EASY);
            break;
        case 3:
            gameLoop(board, false, MEDIUM);
            break;
        case 4:
            gameLoop(board, false, HARD);
            break;
        default:
            std::cout << "Ungültige Eingabe.\n";
            chooseGameMode();
            break;
    }
}
void printWinner(char winner) {
    if (winner == 'X') {
        std::cout << "Spieler X hat gewonnen!" << std::endl;
    } else if (winner == 'O') {
        std::cout << "Spieler O hat gewonnen!" << std::endl;
    } else {
        std::cout << "Unentschieden!" << std::endl;
    }
}


//Checks
bool checkWinner(char board[3][3], char &winner) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            winner = board[i][0];
            return true;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            winner = board[0][i];
            return true;
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        winner = board[0][0];
        return true;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        winner = board[0][2];
        return true;
    }
    return false;
}
bool checkDraw(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

//algorithms
int score(char board[3][3]) {
    char winner;
    if (checkWinner(board, winner)) {
        return (winner == 'O') ? 1 : -1;
    }
    return 0;
}
int minimax(char board[3][3], bool isMaximizing) {
    char winner;
    if (checkWinner(board, winner) || checkDraw(board)) {
        return score(board);
    }

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int score = minimax(board, false);
                    board[i][j] = ' ';
                    bestScore = std::max(score, bestScore);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int score = minimax(board, true);
                    board[i][j] = ' ';
                    bestScore = std::min(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}

//Mechanics
void playerMove(char board[3][3], char player) {
    int move = 0;

    while (move < 1 || move > 9) {
        for (int i = 1; i <= 9; i++) {
            if (GetAsyncKeyState(VK_NUMPAD0 + i) & 0x8000) {
                move = i;
                break;
            }
        }
    }

    int x = 2 - (move - 1) / 3;
    int y = (move - 1) % 3;


    if (board[x][y] == ' ') {
        board[x][y] = player;

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    } else {
        std::cout << "Ungültiger Schritt.\n";
        playerMove(board, player);
    }
}
void computerMoveEasy(char board[3][3], char player) {
    int x, y;
    bool flag = true;
    while (flag) {
        x = rand() % 3;
        y = rand() % 3;
        if (board[x][y] == ' ') {
            board[x][y] = player;
            flag = false;
        }
    }
}
void computerMoveMedium(char board[3][3], char player) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = player;
                char winner;
                if (checkWinner(board, winner)) {
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }
    char opponent = (player == 'X') ? 'O' : 'X';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = opponent;
                char winner;
                if (checkWinner(board, winner)) {
                    board[i][j] = player;
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }
    computerMoveEasy(board, player);
}
void computerMoveHard(char board[3][3], char player) {
    int bestScore = -1000;
    int moveX = -1;
    int moveY = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = player;
                int score = minimax(board, false);
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    moveX = i;
                    moveY = j;
                }
            }
        }
    }

    if (moveX != -1 && moveY != -1) {
        board[moveX][moveY] = player;
    }
}
void gamePvP(){
    char board[3][3] = {{' ', ' ', ' '},
                        {' ', ' ', ' '},
                        {' ', ' ', ' '}};

    gameLoop(board, true, NONE);
}



//loops
void gameLoop(char board[3][3], bool isSecondPlayerHuman, Difficulty difficulty = EASY) {
    char winner = ' ';
    bool flag = true;
    while (flag) {
        printBoard(board);
        playerMove(board, 'X');
        if (checkWinner(board, winner)) {
            printBoard(board);
            printWinner(winner);
            flag = false;
            break;
        }
        if (checkDraw(board)) {
            printBoard(board);
            printWinner(winner);
            flag = false;
            break;
        }
        printBoard(board);
        if (isSecondPlayerHuman) {
            playerMove(board, 'O');
        } else {
            switch (difficulty) {
                case EASY:
                    computerMoveEasy(board, 'O');
                    break;
                case MEDIUM:
                    computerMoveMedium(board, 'O');
                    break;
                case HARD:
                    computerMoveHard(board, 'O');
                    break;
            }
        }
        if (checkWinner(board, winner)) {
            printBoard(board);
            printWinner(winner);
            flag = false;
            break;
        }
        if (checkDraw(board)) {
            printBoard(board);
            printWinner(winner);
            flag = false;
            break;
        }
    }
}


