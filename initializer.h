//
// Created by 35385 on 24/03/2020.
//

#ifndef FOCUS_DOMINATION_INITIALIZER_H
#define FOCUS_DOMINATION_INITIALIZER_H

#endif //FOCUS_DOMINATION_INITIALIZER_H

enum Colour {red, green, none};

struct piece {
    enum Colour colour;
    struct piece *next;
};

void boardInit(struct piece *board[8][8]);
void freeBoard(struct piece *board[8][8]);