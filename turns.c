//
// Created by 35385 on 03/04/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "turns.h"
#include "gameIO.h"

void getCoordinates(int *x, int *y);
void getDirection(int *x, int *y, square board[BOARD_SIZE][BOARD_SIZE]);
void addToStack(square *targetSquare, square *prevSquare);
void popOne(square *popSquare, player *currentPlayer);
int checkBoard(square board[BOARD_SIZE][BOARD_SIZE], int colour);

void turns(player *player1, player *player2, square board[BOARD_SIZE][BOARD_SIZE]) {
    int playerTurn = 1;
    int winner = 0;
    int x, y, previousX, previousY;
    int validity;
    int moves = 0;
    int i;

    while(winner == 0) {
        if(checkBoard(board, (playerTurn == 1 ? player1->playerColour : player2->playerColour)) == 0) { //If player can move a piece
            if((playerTurn == 1 ? player1->reserve : player2->reserve) > 0) { //If there are reserve pieces
                printf("\n%s\'s turn.\n", playerTurn == 1 ? player1->name : player2->name);
                printf("You have %d pieces in reserve.\n", (playerTurn == 1 ? player1->reserve : player2->reserve));
                printf("Mo");
            }
            else {
                winner = (playerTurn == 1 ? 2 : 1); //Sets the other player as winner
            }
        }
        else {
            printf("\n%s\'s turn.\n", playerTurn == 1 ? player1->name : player2->name); //Ternary operator to find name of player
            printf("Enter the coordinates of the piece you would like to move.\n");
            getCoordinates(&x, &y);

            validity = 0;
            while (validity == 0) {
                if (board[x][y].type == INVALID) {
                    printf("The square %c%d is not valid.\n", x + 'a', y + 1);
                    printf("Choose another square.\n");
                    getCoordinates(&x, &y);
                }
                else if (board[x][y].stack == NULL) {
                    printf("This square has no pieces.\n");
                    getCoordinates(&x, &y);
                }
                else if (board[x][y].stack->pieceColour != (playerTurn == 1 ? player1->playerColour : player2->playerColour)) {
                    printf("That piece does not belong to you.\n");
                    printf("Choose another piece.\n");
                    getCoordinates(&x, &y);
                }
                else {
                    validity = 1;
                }
            }

            //These coordinates are stored. The values x and y are updated to hold the coordinates after the move is made.
            previousX = x;
            previousY = y;

            moves = board[x][y].pieceNum;
            //Takes user directions as input.
            while (moves > 0) {
                printf("You have %d move%sleft.\n", moves, moves > 1 ? "s " : " "); //Prints number of moves. If more than one, pluralise word move.
                printf("Your current position is %c%d. Choose a direction to move in.\n", x + 'a', y + 1);
                getDirection(&x, &y, board); //Takes user input and validates it. Changes the coordinates using pointers to x and y.
                moves--;
            }

            //If coordinates haven't changed, nothing happens
            if(x != previousX || y != previousY) {
                addToStack(&board[x][y], &board[previousX][previousY]); //The previous stack is added to the target stack.
            }

            if (board[x][y].pieceNum > 5) {
                for (i = board[x][y].pieceNum - 5; i > 0; i--) {
                    //Removes one piece from the board. Takes the current player as second argument.
                    popOne(&board[x][y], (playerTurn == 1 ? player1 : player2));
                }
            }

            printBoard(board, *player1, *player2);

            playerTurn = (playerTurn == 1) ? 2 : 1; //Alternates playerTurn variable at the end of each turn.
        }
    }
}

void getCoordinates(int *x, int *y) {
    char buffer[6];
    int i;

    *x = *y = -1;

    while(*x == -1 || *y == -1) {
        fgets(buffer, 6, stdin);
        for(i = 0; buffer[i] != '\0'; i++) {

            if(buffer[i] >= 'a' && buffer[i] <= 'z') {
                if(*x == -1) {
                    *x = buffer[i] - 'a';
                }
                else {
                    printf("Invalid input. Coordinates must contain one letter a-g and one number 1-8.\n");
                    *x = *y = -1;
                    break;
                }
            }
            else if(buffer[i] >= 'A' && buffer[i] <= 'Z') {
                if(*x == -1) {
                    *x = buffer[i] - 'A';
                }
                else {
                    printf("Invalid input. Coordinates must contain one letter a-g and one number 1-8.\n");
                    *x = *y = -1;
                    break;
                }
            }
            else if(buffer[i] >= '1' && buffer[i] <= '8') {
                if(*y == -1) {
                    *y = buffer[i] - '1';
                }
                else {
                    printf("Invalid input. Coordinates must contain one letter a-g and one number 1-8.\n");
                    *x = *y = -1;
                    break;
                }
            }
        }
    }
}

//Takes user direction input, and validates it. If valid, sets the coordinate values to the new coordinates
void getDirection(int *x, int *y, square board[BOARD_SIZE][BOARD_SIZE]) {
    char buffer[3];
    int testX = *x, testY = *y; //Temporarily hold new x and y values for testing purposes.

    while(fgets(buffer, 3, stdin)) {
        if(buffer[1] == '\n') { //Checks for newline. If newline not present, the input is invalid.
            switch(buffer[0]) {
                //Checks if the character input is one of l, r, u, d.
                //Each case also checks if the square that is chosen is valid.
                //If each check is passed, the coordinate value is changed and the function returns void.
                case 'l':
                    testX -= 1;
                    break;
                case 'r':
                    testX += 1;
                    break;
                case 'u':
                    testY -= 1;
                    break;
                case 'd':
                    testY += 1;
                    break;
                default:
                    printf("Invalid input. Enter a direction l, r, u, d (left, right, up, down).\n");
                    break;
            }
            //Checks if square is on the board.
            if(testX >= 0 && testX <= 7 && testY >= 0 && testY <= 7) {
                if(board[testX][testY].type == VALID) {
                    *x = testX;
                    *y = testY;
                    return;
                }
                else {
                    printf("You cannot move your piece in that direction. Move to a valid square on the board.\n");
                    //Test values are restored to their original states.
                    testX = *x;
                    testY = *y;
                }
            }
            else {
                printf("You cannot move your piece in that direction. Move to a valid square on the board.\n");
                //Test values are restored to their original states.
                testX = *x;
                testY = *y;
            }
        }
        else {
            //If no null terminator is present, the buffer must be cleared.
            scanf("%*[^\n]"); //Clears all chars except newline
            scanf("%*c"); //Clears one char, i.e. newline
            printf("Invalid input. Enter a direction l, r, u, d (left, right, up, down).\n");
        }
    }
}

//Adds to the bottom of the stack. The system is FIFO.
//prevSquare is the square that holds the piece being moved. targetSquare is the square being moved to.
void addToStack(square *targetSquare, square *prevSquare) {
    piece *lastPiece = prevSquare->stack;

    //Finds the bottom of the stack being moved.
    while(lastPiece->next != NULL) {
        lastPiece = lastPiece->next;
    }

    //Changing pointers to complete the movement of the stack. Each square contains a pointer to the top of each stack.
    lastPiece->next = targetSquare->stack;
    targetSquare->stack = prevSquare->stack;
    prevSquare->stack = NULL;

    //Updates number of pieces on each square
    targetSquare->pieceNum += prevSquare->pieceNum;
    prevSquare->pieceNum = 0;
}

void popOne(square *popSquare, player *currentPlayer) {
    piece *nextPiece = popSquare->stack;

    while(nextPiece->next != NULL) {
        nextPiece = nextPiece->next;
    }

    if(currentPlayer->playerColour == nextPiece->pieceColour) {
        currentPlayer->reserve++;
    }
    else {
        currentPlayer->captured++;
    }

    free(nextPiece);
    popSquare->pieceNum--;
}

//Checks the board to see if any player can make a move.
int checkBoard(square board[BOARD_SIZE][BOARD_SIZE], int colour) {
    int i, j;

    for(i = 0; i < 8; i++) {
        for(j = 0; j < 8; j++) {
            if(board[i][j].type == VALID) {
                if(board[i][j].stack != NULL) {
                    if(board[i][j].stack->pieceColour == colour) {
                        return 1; //Returns 1 if there is at least one valid move to be made
                    }
                }
            }
        }
    }

    return 0; //Returns 0 if there are no valid moves
}