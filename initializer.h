//
// Created by 35385 on 24/03/2020.
//

#ifndef FOCUS_DOMINATION_INITIALIZER_H
#define FOCUS_DOMINATION_INITIALIZER_H

#define BOARD_SIZE 8

typedef enum colour {RED, GREEN} colour;

typedef enum squareType {VALID, INVALID} squareType;

typedef struct player {
    colour playerColour;
    char *name;
    int captured;
    int reserve;
}player;

typedef struct piece {
    colour pieceColour;
    struct piece *next;
}piece;

typedef struct square {
    squareType type;
    piece *stack;
    int pieceNum;
}square;

void boardInit(square board[BOARD_SIZE][BOARD_SIZE]);
void playerInit(player *player1, player *player2);
void freeAll(player *player1, player *player2, square board[BOARD_SIZE][BOARD_SIZE]);

#endif //FOCUS_DOMINATION_INITIALIZER_H


