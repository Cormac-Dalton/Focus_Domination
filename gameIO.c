//
// Created by 35385 on 25/03/2020.
//

#include <stdio.h>
#include "gameIO.h"

//Prints the game board at any position in the game.
void printBoard(struct piece *board[8][8]) {
    int x, y; //Represent the x and y axises on the board. 0 is above 7 on the y axis. 0 is on the left of 7 on the x axis.

    //Cycles through every position on the board
    for(y = 0; y < 8; y++) {
        for(x = 0; x < 8; x++) {
            if(board[x][y] != NULL) { //If the pointer at [x][y] is null, whitespace is printed.
                //Checks the colour value (or lack of thereof) in board and prints the corresponding symbol
                switch(board[x][y]->colour) {
                    case red:
                        printf("R  "); //Red piece on top
                        break;
                    case green:
                        printf("G  "); //Green piece on top.
                        break;
                    case none:
                        printf("+  "); //Empty tile. Contains no pieces.
                        break;
                    default:
                        printf("?  "); //Error symbol. Should not occur unless something is broken.
                        break;
                }
            }
            else { //Prints whitespace if pointer at [x][y] is null
                printf("   ");
            }
        }
        printf("\n"); //Newline printed after every line
    }
}
