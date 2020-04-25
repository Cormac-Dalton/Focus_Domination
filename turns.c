//
// Created by 35385 on 03/04/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "turns.h"
#include "gameIO.h"

void getCoordinates(int *x, int *y); //Takes coordinates as input and validates them
void getDirection(int *x, int *y, square board[BOARD_SIZE][BOARD_SIZE]); //Takes a direction u, d, r, l, as input
void addToStack(square *targetSquare, square *prevSquare); //Adds one stack to another
void addReserve(square *targetSquare, player *currentPlayer); //Adds a reserve piece to a stack
void popOne(square *popSquare, player *currentPlayer); //Removes one piece from a stack
int checkBoard(square board[BOARD_SIZE][BOARD_SIZE], int colour);

int turns(player *player1, player *player2, square board[BOARD_SIZE][BOARD_SIZE]) {
    int playerTurn = 1; //Number corresponds to the player who's turn it is
    int winner = 0; //Corresponds to number of winning player
    int x, y, previousX, previousY; //Coordinates used in moves
    int validity; //Is 0 while invalid move is selected
    int moves = 0; //Counts number of moves that each player has
    int i;

    while(winner == 0) {
        if(checkBoard(board, (int)(playerTurn == 1 ? player1->playerColour : player2->playerColour)) == 0) { //Checks if player can't move
            if((playerTurn == 1 ? player1->reserve : player2->reserve) > 0) { //Checks if there are reserve pieces

                printBoard(board, *player1, *player2);

                //Prompts user to input coordinates to place reserve piece.
                printf("\n%s\'s turn.\n", playerTurn == 1 ? player1->name : player2->name);
                printf("You have %d pieces in reserve.\n", (playerTurn == 1 ? player1->reserve : player2->reserve));
                printf("Enter the coordinates of a square to put a piece.\n");

                getCoordinates(&x, &y);
                addReserve(&board[x][y], (playerTurn == 1 ? player1 : player2)); //

                //Removes a piece if size goes above 5
                if (board[x][y].pieceNum > 5) {
                    for (i = board[x][y].pieceNum - 5; i > 0; i--) {
                        //Removes one piece from the board. Takes the current player as second argument.
                        popOne(&board[x][y], (playerTurn == 1 ? player1 : player2));
                    }
                }
            }
            else {
                winner = (playerTurn == 1 ? 2 : 1); //Sets the other player as winner
            }
        }
        else {
            printBoard(board, *player1, *player2);

            printf("\n%s\'s turn.\n", playerTurn == 1 ? player1->name : player2->name); //Ternary operator to find name of player
            printf("Enter the coordinates of the piece you would like to move.\n");
            getCoordinates(&x, &y);

            //Loop for checking that the square chosen contains a piece of the right colour
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
                //Checks if the piece colour is the same as the colour that belongs to the current player
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

            //The if statement guards against the case where the previous coordinates are the same as the current ones
            if(x != previousX || y != previousY) {
                addToStack(&board[x][y], &board[previousX][previousY]); //The previous stack is added to the target stack.
            }

            if (board[x][y].pieceNum > 5) {
                for (i = board[x][y].pieceNum - 5; i > 0; i--) {
                    //Removes one piece from the board. Takes the current player as second argument.
                    popOne(&board[x][y], (playerTurn == 1 ? player1 : player2));
                }
            }
        }

        playerTurn = (playerTurn == 1) ? 2 : 1; //Alternates playerTurn variable at the end of each turn.
    }

    return winner; //The number corresponds to the winning player's number
}

//Function changes the coordinates x and y to match user input.
//User input is validated to ensure that it follows the correct format, and that the coordinates are valid.
void getCoordinates(int *x, int *y) {
    char buffer[6]; //Array to store user input for validation
    int i;

    //x and y are set to -1 to signal that they have not yet recieved a value
    *x = *y = -1;

    //Loop ends when both x and y get valid values
    while(*x == -1 || *y == -1) {
        //If statement covers case where user inputs only one coordinate, which is treated as valid, but doesn't put in the other.
        if(*x != -1 || *y != -1) {
            printf("Invalid input. Coordinates must contain one letter a-g and one number 1-8.\n");
            *x = *y = -1;
        }
        fgets(buffer, 6, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        //Loop goes through string until end is reached.
        for(i = 0; buffer[i] != '\0'; i++) {

            //If statements check if input is valid. They ignore non alphanumeric characters.
            if(buffer[i] >= 'a' && buffer[i] <= 'g') {
                if(*x == -1) { //Checks if x has been given another value yet
                    *x = buffer[i] - 'a'; //Converts user input char to int
                }
                else { //Triggers if x has already been given a value, which means the input is invalid.
                    printf("Invalid input. Coordinates must contain one letter a-g and one number 1-8.\n");
                    *x = *y = -1; //Coordinates are reset to -1 on a failed test
                    break;
                }
            }
            else if(buffer[i] >= 'A' && buffer[i] <= 'G') { //Input also accepts capital letters
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
                    *y = buffer[i] - '1'; //Values '1'-'8' are converted to 0-7 to match array format
                }
                else {
                    printf("Invalid input. Coordinates must contain one letter a-g and one number 1-8.\n");
                    *x = *y = -1;
                    break;
                }
            }
            //This branch checks if an invalid alphanumeric character was added (i.e. letters g-z, or numbers 9 and 0)
            else if((buffer[i] >= 'h' && buffer[i] <= 'z') || (buffer[i] >= 'H' && buffer[i] <= 'Z') || (buffer[i] == '9') || (buffer[i] == '0')) {
                printf("Invalid input. Coordinates must contain one letter a-g and one number 1-8.\n");
                *x = *y = -1;
                break;
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
                //If each check is passed, the coordinate value is changed and the function ends.
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
                    testX = -1; //Indicates that input was invalid
                    break;
            }
            //Checks if square is on the board.
            if(testX >= 0 && testX <= 7 && testY >= 0 && testY <= 7) {
                if(board[testX][testY].type == VALID) {
                    //x and y are set if they are both on the board and valid
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
            else if(testX == -1) { //If the input was not one of u, d, l, r
                testX = *x; //Resets testX
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

//Adds a reserve piece by dynamically allocating memory for it.
void addReserve(square *targetSquare, player *currentPlayer) {
    piece *temp = targetSquare->stack; //temp stores the pointer to the top of stack before the reserve piece is added

    //This block initializes the new piece
    targetSquare->stack = calloc(1, sizeof(piece));
    targetSquare->stack->next = temp;
    targetSquare->stack->pieceColour = currentPlayer->playerColour;

    currentPlayer->reserve--;
    targetSquare->pieceNum++;
}

//Removes one piece from a stack
void popOne(square *popSquare, player *currentPlayer) {
    //These variables are used to find the bottom piece in the stack
    piece *nextPiece = popSquare->stack;
    piece *prevPiece = NULL;

    //Loop continues until bottom piece reached
    while(nextPiece->next != NULL) {
        prevPiece = nextPiece;
        nextPiece = nextPiece->next; //nextPiece follows the pointers to find the last piece
    }

    //If statement determines whether the piece should be added to 'reserve' or 'captured'
    if(currentPlayer->playerColour == nextPiece->pieceColour) {
        currentPlayer->reserve++;
    }
    else {
        currentPlayer->captured++;
    }

    prevPiece->next = NULL; //prevPiece is the new bottom piece so the pointer is made NULL
    free(nextPiece); //Removed piece is freed
    popSquare->pieceNum--;
}

//Checks the board to see if a player can make a move, based on their colour.
int checkBoard(square board[BOARD_SIZE][BOARD_SIZE], int colour) {
    int i, j;

    for(i = 0; i < 8; i++) {
        for(j = 0; j < 8; j++) {
            if(board[i][j].type == VALID) {
                if(board[i][j].stack != NULL) { //Checks if there are any pieces on that square
                    if(board[i][j].stack->pieceColour == colour) {
                        return 1; //Returns 1 if there is at least one valid move to be made
                    }
                }
            }
        }
    }

    return 0; //Returns 0 if there are no valid moves
}