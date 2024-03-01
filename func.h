#ifndef TICTACTOE_FUNC_H
#define TICTACTOE_FUNC_H

//declare stuff
enum Difficulty {
    NONE,
    EASY,
    MEDIUM,
    HARD
};


//prints
void printWelcome();
void printBoard(char board[3][3]);
void printWinner(char winner);
void chooseGameMode();

//Game Mechanics
void playerMove(char board[3][3], char player);
void computerMoveEasy(char board[3][3], char player);
void computerMoveMedium(char board[3][3], char player);
void computerMoveHard(char board[3][3], char player);


//Game Modes
void gamePvP();

//Game Checks
bool checkWinner(char board[3][3], char &winner);
bool checkDraw(char board[3][3]);

//Game Loop
void gameLoop(char board[3][3], bool isSecondPlayerHuman, Difficulty difficulty);


#endif //TICTACTOE_FUNC_H
