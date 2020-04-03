//
// Created by 35385 on 24/03/2020.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "initializer.h"

void setInvalid(square * s);
void setEmpty(square * s);
void setGreen(square * s);
void setRed(square * s);

void playerInit() {
    char buffer[20];
    player *player1 = malloc(sizeof(player));
    player1->captured = 0;
    player1->reserve = 0;

    player1->name = malloc(20*sizeof(char));
    printf("Player 1, enter your name.\n");

    fgets(player1->name, 20, stdin);
    player1->name[strcspn(player1->name, "\n")] = 0;
    printf("Choose red or green.\n");
    while(fgets(buffer, 6, stdin)) {
        buffer[strcspn(buffer, "\n")] = 0;
        if(strcmp(buffer, "red") != 0 && strcmp(buffer, "green") != 0) {
            printf("Invalid input. Please enter red or green.\n\n");
            printf("\"%s\"\n", buffer);
        }
        else break;
    }
    player1->playerColour = (strcmp(buffer, "red") == 0) ? RED : GREEN;


    player *player2 = malloc(sizeof(player));
    player2->captured = 0;
    player2->reserve = 0;

    player2->name = malloc(20*sizeof(char));
    printf("Player 2, enter your name.\n");
    fgets(player2->name, 20, stdin);
    player2->name[strcspn(player2->name, "\n")] = 0;

    printf(player1->playerColour == RED ? "Player 2 is green.\n" : "Player 2 is red.\n");
    player2->playerColour = (strcmp(buffer, "red") == 0) ? RED : GREEN;
}

void boardInit(square board[BOARD_SIZE][BOARD_SIZE]) {
    int x, y;

    for(y = 0; y < BOARD_SIZE; y++) {
        for(x=0; x< BOARD_SIZE; x++) {

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

void setInvalid(square * s) {
    s->type = INVALID;
    s->stack = NULL;
    s->pieceNum = 0;
}

void setEmpty(square * s) {
    s->type = VALID;
    s->stack = NULL;
    s->pieceNum = 0;
}

void setGreen(square * s) {
    s->type = VALID;
    s->stack = (piece *) malloc (sizeof(piece));
    s->stack->pieceColour = GREEN;
    s->stack->next = NULL;
    s->pieceNum = 1;
}

void setRed(square * s) {
    s->type = VALID;
    s->stack = (piece *) malloc (sizeof(piece));
    s->stack->pieceColour = RED;
    s->stack->next = NULL;
    s->pieceNum = 1;
}