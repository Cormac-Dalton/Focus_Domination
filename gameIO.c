//
// Created by 35385 on 25/03/2020.
//

#include <stdio.h>
#include "gameIO.h"

//Prints the game board at any position in the game.
void printBoard(square board[BOARD_SIZE][BOARD_SIZE]) {
    int x, y;

    printf("****** The Board ******\n");
    for(y = 0; y < BOARD_SIZE; y ++){
        for (x = 0; x < BOARD_SIZE; x++){
            if(board[x][y].type == VALID) {
                if(board[x][y].stack == NULL)
                    printf("| + ");
                else{
                    if (board[x][y].stack->pieceColour == GREEN)
                        printf("| G ");
                    else printf("| R ");
                }
            }
            else
                printf("|   ");
        }
        printf("|\n");
    }
}
