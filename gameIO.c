//
// Created by 35385 on 25/03/2020.
//

#include <stdio.h>
#include "gameIO.h"

//Prints the game board at any position in the game.
void printBoard(square board[BOARD_SIZE][BOARD_SIZE], player player1, player player2) {
    int x, y;

    printf("      ****** The Board ******\n");
    printf("    a   b   c   d   e   f   g   h \n");

    for(y = 0; y < BOARD_SIZE; y ++){
        printf("%d ", y + 1);
        for (x = 0; x < BOARD_SIZE; x++){
            if(board[x][y].type == VALID) {
                if(board[x][y].stack == NULL)
                    printf("| + ");
                else{
                    if(board[x][y].stack->pieceColour == GREEN)
                        printf("| G%d", board[x][y].pieceNum);
                    else printf("| R%d", board[x][y].pieceNum);
                }
            }
            else
                printf("|   ");
        }
        printf("|\n");
    }
    printf("PLAYER:\t\t%s\t%s\n", player1.name, player2.name);
    if(player1.playerColour == RED) {
        printf("COLOUR:\t\tRED\tGREEN\n");
    }
    else {
        printf("COLOUR:\tGREEN\tRED\n");
    }
    printf("CAPTURED:\t%d\t%d\n", player1.captured, player2.captured);
    printf("RESERVE:\t%d\t%d\n", player1.reserve, player2.reserve);
}
