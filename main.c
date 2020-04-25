#include "gameIO.h"
#include "turns.h"

int main() {
    int winner;
    player player1, player2;

    playerInit(&player1, &player2); //Initializes players

    square board[BOARD_SIZE][BOARD_SIZE];
    boardInit(board); //Initializes the board.

    winner = turns(&player1, &player2, board); //Handles each turn. Returns winner when game is over.

    endGame(player1, player2, winner); //Prints end game screen

    freeAll(&player1, &player2, board); //Frees all dynamically allocated memory

    return 0;
}
