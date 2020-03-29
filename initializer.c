//
// Created by 35385 on 24/03/2020.
//

#include <stdlib.h>
#include "initializer.h"

setInvalid(square * s);
setEmpty(square * s);
setGreen(square * s);
setRed(square * s);

void boardInit(square board[BOARD_SIZE][BOARD_SIZE]) {
    int x, y;

    for(y = 0; y < BOARD_SIZE; y++) {
        for(int x=0; x< BOARD_SIZE; x++) {

            if((x==0 && (y==0 || y==1 || y==6 || y==7)) ||
               (x==1 && (y==0 || y==7)) ||
               (x==6 && (y==0 || y==7)) ||
               (x==7 && (y==0 || y==1 || y==6 || y==7)))
                setInvalid(&board[x][y]);

            else {
                if(x==0 || x ==7 || y==0 || y == 7)
                    setEmpty(&board[x][y]);
                else{
                    //squares with red pieces
                    if((y%2 == 1 && (x < 3 || x> 4)) ||
                       (y%2 == 0 && (x == 3 || x==4)))
                        setRed(&board[x][y]);
                        //green squares
                    else setGreen(&board[x][y]);
                }
            }
        }
    }

}

setInvalid(square * s) {
    s->type = INVALID;
    s->stack = NULL;
    s->pieceNum = 0;
}

setEmpty(square * s) {
    s->type = VALID;
    s->stack = NULL;
    s->pieceNum = 0;
}

setGreen(square * s) {
    s->type = VALID;
    s->stack = (piece *) malloc (sizeof(piece));
    s->stack->pieceColour = GREEN;
    s->stack->next = NULL;
    s->pieceNum = 1;
}

setRed(square * s) {
    s->type = VALID;
    s->stack = (piece *) malloc (sizeof(piece));
    s->stack->pieceColour = RED;
    s->stack->next = NULL;
    s->pieceNum = 1;
}
