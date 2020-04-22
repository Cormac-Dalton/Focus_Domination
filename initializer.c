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
void freeStack(piece *top);

//Initialize players
void playerInit(player *player1, player *player2) {
    char buffer[20]; //Stores user input
    player1->captured = 0;
    player1->reserve = 0;

    //Takes player 1 name from user input
    player1->name = malloc(20*sizeof(char));
    printf("Player 1, enter your name.\n");
    fgets(player1->name, 20, stdin);

    player1->name[strcspn(player1->name, "\n")] = 0; //Gets rid of newline at end of name

    //Takes user input for player 1 colour, and verifies input
    printf("Choose red or green.\n");
    while(fgets(buffer, 7, stdin)) { //Loop runs until break statement met
        buffer[strcspn(buffer, "\n")] = 0; //Removes newline from colour so it can be evaluated using strcmp
        if(strcmp(buffer, "red") != 0 && strcmp(buffer, "green") != 0) {
            printf("Invalid input. Please enter red or green.\n");
            //Scanf clears values from buffer
            scanf("%*[^\n]");
            scanf("%*c");
        }
        else break; //Breaks if red or green chosen
    }
    //Matches playerColour variable to colour chosen
    player1->playerColour = (strcmp(buffer, "red") == 0) ? RED : GREEN;

    //Player 2 is initialized next
    player2->captured = 0;
    player2->reserve = 0;

    //Takes name as user input
    player2->name = malloc(20*sizeof(char));
    printf("Player 2, enter your name.\n");
    fgets(player2->name, 20, stdin);
    player2->name[strcspn(player2->name, "\n")] = 0;

    //Assigns the opposite colour to player2 and prints out what colour they were assigned to.
    player2->playerColour = (player1->playerColour == 1 ? RED : GREEN);
    printf(player2->playerColour == RED ? "Player 2 is red.\n" : "Player 2 is green.\n");
}

//Initializes board
void boardInit(square board[BOARD_SIZE][BOARD_SIZE]) {
    int x, y;

    //Sets initial state of board squares
    for(y = 0; y < BOARD_SIZE; y++) {
        for(x=0; x< BOARD_SIZE; x++) {

            //All these squares are invalid
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

void freeAll(player *player1, player *player2, square board[BOARD_SIZE][BOARD_SIZE]) {
    int i, j;

    free(player1->name);
    free(player2->name);

    for(i = 0; i < BOARD_SIZE; i++) {
        for(j = 0; j < BOARD_SIZE; j++) {
            if(board[i][j].type == VALID) {
                freeStack(board[i][j].stack);
            }
        }
    }
}

//Frees a stack
void freeStack(piece *top) {
    int i;
    piece *prevPtr, *nextPtr;
    nextPtr = top;

    //Goes down the stack, freeing the previous pointers
    for(i = 0; nextPtr != NULL && i < 5; i++) {
        prevPtr = nextPtr;
        nextPtr = nextPtr->next;
        free(prevPtr);
    }
    free(nextPtr);
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

//
void setRed(square * s) {
    s->type = VALID;
    s->stack = (piece *) malloc (sizeof(piece));
    s->stack->pieceColour = RED;
    s->stack->next = NULL;
    s->pieceNum = 1;
}