#include "gameIO.h"
#include "turns.h"

int main() {
    player player1, player2;

    playerInit(&player1, &player2);

    square board[BOARD_SIZE][BOARD_SIZE];

    boardInit(board); //Initializes the board.

    printBoard(board); //Prints the board.

    turns(&player1, &player2, board);

    return 0;
}
