//
// Created by 35385 on 25/03/2020.
//

#include <stdio.h>
#include <string.h>
#include "gameIO.h"

//Prints the game board at any position in the game.
void printBoard(square board[BOARD_SIZE][BOARD_SIZE], player player1, player player2) {
    int x, y;

    printf("\n       ****** The Board ******\n");
    printf("     a    b    c    d    e    f    g    h \n"); //Coordinate values

    //Checks each square on the board and prints the appropriate symbol
    for(y = 0; y < BOARD_SIZE; y ++){
        printf("%d ", y + 1); //Prints the coordinates at the side of the board
        for (x = 0; x < BOARD_SIZE; x++){
            if(board[x][y].type == VALID) {
                if(board[x][y].stack == NULL)
                    printf("| ++ "); //Empty square
                else{
                    if(board[x][y].stack->pieceColour == GREEN)
                        printf("| G%d ", board[x][y].pieceNum); //Colour of top piece followed by number of pieces in stack
                    else printf("| R%d ", board[x][y].pieceNum);
                }
            }
            else
                printf("|    "); //Invalid square
        }
        printf("|\n");
    }

    //Prints player information each turn. Tabs are used for formatting.
    //If statement formats scoreboard differently if player1's name is too long
    if(strlen(player1.name) > 7) {
        printf("PLAYER:\t\t%s\t%s\n", player1.name, player2.name);
    }
    else {
        printf("PLAYER:\t\t%s\t\t%s\n", player1.name, player2.name);
    }

    //If statement assigns the correct colour to each player
    if(player1.playerColour == RED) {
        printf("COLOUR:\t\tRED\t\tGREEN\n");
    }
    else {
        printf("COLOUR:\t\tGREEN\t\tRED\n");
    }

    //Prints captured and reserve pieces
    printf("CAPTURED:\t%d\t\t%d\n", player1.captured, player2.captured);
    printf("RESERVE:\t%d\t\t%d\n", player1.reserve, player2.reserve);
}

//Prints end of game screen. Shows winning player name, followed by the final scoreboard
void endGame(player player1, player player2, int winner) {
    printf("\n\n##############################\n");
    printf("CONGRATULATIONS.\n");
    printf("%s HAS WON THE GAME.\n", (winner == 1) ? player1.name : player2.name); //Prints name of winner
    printf("##############################\n");

    //The final score is printed in the same way as the score in the print function.
    printf("\tFINAL SCORE:\n");
    if(strlen(player1.name) > 7) {
        printf("PLAYER:\t\t%s\t%s\n", player1.name, player2.name);
    }
    else {
        printf("PLAYER:\t\t%s\t\t%s\n", player1.name, player2.name);
    }

    if(player1.playerColour == RED) {
        printf("COLOUR:\t\tRED\t\tGREEN\n");
    }
    else {
        printf("COLOUR:\t\tGREEN\t\tRED\n");
    }

    printf("CAPTURED:\t%d\t\t%d\n", player1.captured, player2.captured);
    printf("RESERVE:\t%d\t\t%d\n", player1.reserve, player2.reserve);

    printf("##############################\n");
}