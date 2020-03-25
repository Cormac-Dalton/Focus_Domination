//
// Created by 35385 on 24/03/2020.
//

#include <stdlib.h>
#include "initializer.h"

void allocateMemory(struct piece *board[8][8]);

void boardInit(struct piece *board[8][8]) {
    int x, y;
    enum Colour alternator = red; //Called alternator as it alternates between red and green. Used to set initial board state.

    //Allocates memory to valid positions.
    allocateMemory(board);

    //Invalid positions in the array are set to NULL so they don't point to junk values.
    board[0][0] = board[0][1] = board[1][0] = NULL;
    board[6][0] = board[7][0] = board[7][1] = NULL;
    board[0][6] = board[0][7] = board[1][7] = NULL;
    board[7][6] = board[6][7] = board[7][7] = NULL;

    //Starts by setting the colour in every position to NONE.
    for(y = 0; y < 8; y++) {
        for(x = 0; x < 8; x++) {
            if(board[x][y] != NULL) { //Null pointers don't have colour values.
                board[x][y]->colour = none;
            }
        }
    }

    //The next few loops set the inital colours on the board with compact code.
    //The first loops sets every other position by alternating colours. E.g. [1][1] = R, [3][1] = G, [5][1] = R, [1][2] = G, etc.
    //Only the 6x6 square in the center of the board is considered.
    for(y = 1; y < 7; y++) {
        for(x = 1; x < 6; x += 2) { //Loop skips every second value of x.
            board[x][y]->colour = alternator;
            alternator = (alternator == red) ? green : red; //Ternary operator alternates the colour of alternator.
        }
    }

    //This loop covers the squares that the first one missed.
    for(y = 1; y < 7; y ++) {
        for(x = 2; x < 7; x += 2) {
            board[x][y]->colour = alternator;
            alternator = (alternator == red) ? green : red; //Ternary operator alternates the colour of alternator.
        }
    }
}

//Frees allocated memory on the board.
void freeBoard(struct piece *board[8][8]) {
    int i, j;

    for(i = 0; i < 8; i++) {
        for(j = 0; j < 8; j++) {
            free(board[i][j]);
        }
    }
}

//Allocates memory to every valid position on the board.
void allocateMemory(struct piece *board[8][8]) {
    int x, y;

    //To avoid allocating memory to unused positions, some rows are allocated in separate loops.
    for(x = 2; x < 6; x++) {
        board[x][0] = malloc(sizeof(struct piece));
    }

    for(x = 1; x < 7; x++) {
        board[x][1] = malloc(sizeof(struct piece));
    }

    //The middle four rows are all full length, and can be allocated using nested loops.
    for(y = 2; y < 6; y++) {
        for(x = 0; x < 8; x++) {
            board[x][y] = malloc(sizeof(struct piece));
        }
    }

    for(x = 1; x < 7; x++) {
        board[x][6] = malloc(sizeof(struct piece));
    }

    for(x = 2; x < 6; x++) {
        board[x][7] = malloc(sizeof(struct piece));
    }
}

