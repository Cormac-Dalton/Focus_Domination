#include "gameIO.h"

int main() {

    playerInit();

    square board[BOARD_SIZE][BOARD_SIZE];

    boardInit(board); //Initializes the board.

    printBoard(board); //Prints the board.

    return 0;
}
