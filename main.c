#include "gameIO.h"

int main() {
    //Struct piece is declared in initializer. It represents a node in a linked list.
    struct piece *board[8][8]; //The game board. Contains pointers to linked lists. Invalid tiles are null pointers.

    boardInit(board); //Initializes the board.

    printBoard(board); //Prints the board.

    freeBoard(board); //Frees all dynamically allocated values on the board.

    return 0;
}
