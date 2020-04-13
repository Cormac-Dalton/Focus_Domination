//
// Created by 35385 on 03/04/2020.
//

#include <stdio.h>
#include "turns.h"
#include "gameIO.h"

void getCoordinates(int *x, int *y);
void getDirection(int *x, int *y, square board[BOARD_SIZE][BOARD_SIZE]);
void addToStack(piece *targetStackPtr, piece **prevStackPtr);

void turns(player *player1, player *player2, square board[BOARD_SIZE][BOARD_SIZE]) {
    int playerTurn = 1;
    int winner = 0;
    int x, y, previousX, previousY;
    int validity;
    int moves = 0;

    while(winner == 0) {
        printf("\n%s\'s turn.\n", playerTurn == 1 ? player1->name : player2->name); //Ternary operator to find name of player
        printf("Enter the coordinates of the piece you would like to move.\n");
        getCoordinates(&x, &y);

        validity = 0;
        while(validity == 0) {
            if(board[x][y].type == INVALID) {
                printf("The square %c%d is not valid.\n", x + 'a', y + 1);
                printf("Choose another square.\n");
                getCoordinates(&x, &y);
            }
            else if(board[x][y].stack == NULL) {
                printf("This square has no pieces.\n");
                getCoordinates(&x, &y);
            }
            else if(board[x][y].stack->pieceColour != (playerTurn == 1 ? player1->playerColour : player2->playerColour)) {
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
        while(moves > 0) {
            printf("You have %d move%sleft.\n", moves, moves > 1 ? "s " : " "); //Prints number of moves. If more than one, pluralise word move.
            printf("Your current position is %c%d. Choose a direction to move in.\n", x + 'a', y + 1);
            getDirection(&x, &y, board); //Takes user input and validates it. Changes the coordinates using pointers to x and y.
            moves--;
        }

        addToStack(board[x][y].stack, &board[previousX][previousY].stack); //The previous stack is added to the target stack.

        printBoard(board);

        playerTurn = (playerTurn == 1) ? 2 : 1; //Alternates playerTurn variable at the end of each turn.
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

    while(fgets(buffer, 3, stdin)) {
        if(buffer[1] == '\n') { //Checks for newline. If newline not present, the input is invalid.
            switch(buffer[0]) {
                //Checks if the character input is one of l, r, u, d.
                //Each case also checks if the square that is chosen is valid.
                //If each check is passed, the coordinate value is changed and the function returns void.
                case 'l':
                    if(board[*x - 1][*y].type == VALID) { //Check if square to left is valid
                        *x -= 1;
                        return;
                    }
                    else {
                        printf("You cannot move your piece in that direction. Move to a valid square on the board.\n");
                    }
                    break;
                case 'r':
                    if(board[*x + 1][*y].type == VALID) { //Check if square to right is valid
                        *x += 1;
                        return;
                    }
                    else {
                        printf("You cannot move your piece in that direction. Move to a valid square on the board.\n");
                    }
                    break;
                case 'u':
                    if(board[*x][*y - 1].type == VALID) { //Check is square above is valid
                        *y += -1;
                        return;
                    }
                    else {
                        printf("You cannot move your piece in that direction. Move to a valid square on the board.\n");
                    }
                    break;
                case 'd':
                    if(board[*x][*y + 1].type == VALID) { //Check if square below is valid
                        *y += 1;
                        return;
                    }
                    else {
                        printf("You cannot move your piece in that direction. Move to a valid square on the board.\n");
                    }
                    break;
                default:
                    printf("Invalid input. Enter a direction l, r, u, d (left, right, up, down).\n");
                    break;
            }
        }
        else {
            //If no null terminator is present, the buffer must be cleared.
            scanf("%*[^\n]"); //Clears all chars except newline
            scanf("%*c"); //Clears one char, i.e. newline
        }
    }
}

//Adds pieces to the top of the stack, geometrically speaking. In terms of code, pieces are added to the bottom. The system is FIFO.
//The prevStackPtr points to the stack we are moving. The target stack is the stack we are moving to.
void addToStack(piece *targetStackPtr, piece **prevStackPtr) {
    piece *lastPiece = targetStackPtr;

    //Goes to the piece at the top of the target stack.
    while(lastPiece->next != NULL) {
        lastPiece = lastPiece->next;
    }

    lastPiece->next = *prevStackPtr; //The top piece now points to the bottom of the previous stack.
    *prevStackPtr = NULL; //The previous stack is now empty, and assigned NULL.
}