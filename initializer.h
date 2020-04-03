//
// Created by 35385 on 24/03/2020.
//

#ifndef FOCUS_DOMINATION_INITIALIZER_H
#define FOCUS_DOMINATION_INITIALIZER_H

#endif //FOCUS_DOMINATION_INITIALIZER_H

#define BOARD_SIZE 8
#define PLAYER_COUNT 2

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
void playerInit();