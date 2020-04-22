//
// Created by 35385 on 25/03/2020.
//

#include "initializer.h"

#ifndef FOCUS_DOMINATION_GAMEIO_H
#define FOCUS_DOMINATION_GAMEIO_H

void printBoard(square board[BOARD_SIZE][BOARD_SIZE], player player1, player player2);

void endGame(player player1, player player2, int winner);

#endif //FOCUS_DOMINATION_GAMEIO_H