//  A simple two player tic tac toe game with GUI display
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void printboard(int rows, int columns, char board[rows][columns]){
    printf("\n\n");
    for (int i = 0 ; i < rows ; i ++ ) {
        printf("%s\n", board[i]);
    }
}

int calcrow(char *move){
    int row = 0;
    if (move[1] == '3') {
        row = 0;
    } else if (move[1] == '2') {
        row = 1;
    } else if (move[1] == '1') {
        row = 2;
    }
    return row;
}

int calccolumn(char *move){
    // column 3,7,11
    int column = 0;  
    if (move[0] == 'A'){
        column = 3;
    } else if (move[0] == 'B') {
        column = 7;
    } else if (move[0] == 'C') {
        column = 11;
    }    
    return column;
}

void updateboard (int turn, char *move, int rows, int columns, char board[rows][columns]){
    char marker;        // initialize marker
    if (turn == 0) {
        marker = 'X';   // player 1
    } else {
        marker = 'O';   // player 2
    }
    // convert move to a board location 
    int row = calcrow(move);
    int column = calccolumn(move);
    // put the marker on the board 
    board[row][column] = marker;    
}

bool checkmove(char *move, int rows, int columns, char board[rows][columns]) {
    // convert move to a board location 
    int row = calcrow(move);
    int column = calccolumn(move);
    if ( board[row][column] != '_') {      // if the board position is occupied, return false
        return false;
    } else {
        return true;                                // the position is not occupied so return true;
    }
}

// This function checks if a win was achieved after each move
bool checkwin(int player, int rows, int columns, char board[4][20]){
    bool win = false;
    int dimension = rows;
    char moves[3][3];
    char symbol;
    if (player == 0 ) { //P1
        symbol = 'X';
    } else {            //P2
        symbol = 'O';
    }
    int offset = 1;
    // Put all of the gameboard of the moves or default board into a new 2D array moves
    for (int i = 0 ; i < 3 ; i ++ ){
        for (int j = 0 ; j <= 11 ; j ++){   // columns 3, 7, 11     // 3-3 = 0 // 7 -6 = 1 // 11-9 = 2
            if (j == 3) {
                moves[i][j-3] = board[i][j];
            }else if ( j == 7 ) {
                moves[i][j-(6)] = board[i][j];
            } else if (j == 11 ){ 
                //printf("\n The character at %d %d is : %c", i, j, board[i][j]);
                moves[i][j-9] = board[i][j];
                //printf("\nMoves has : %c" , moves[i][j-(3*offset)]);
            }
        }
        //printf("Row %d of Moves is : %s\n", i,  moves[i]);
        offset ++; 
    }

    for (int i = 0 ; i < 3 ; i ++){
        if (moves[i][0] == symbol && moves[i][1] == symbol && moves[i][2] == symbol){               // Horizontal 3 "XXX" or "OOO" for any row
            win = true;
        } else if (moves[0][i] == symbol && moves[1][i] == symbol && moves[2][i] == symbol) {       // Vertical 3 in a column i 
            win = true;
        }
    }  
    // check 2 diagonals 
    if (moves[1][1] == symbol){
        if (moves[0][0] == symbol && moves[2][2] == symbol)  {
            win = true;
        } else if (moves[0][2] == symbol && moves[2][0] == symbol){
            win = true;
        }
    }
    return win;
}

void resetboard(int rows, int columns, char gameboard[rows][columns], char defaultboard[rows][columns]){
    // reset the gameboard to default, start playing again
    for (int i = 0 ; i < rows ; i ++) {
        for (int j = 0 ; j < columns ; j ++) {
            gameboard[i][j] = defaultboard[i][j];       // reset gameboard values with the values from default board
        }
    }
}

int main (void) {
    int rows = 4 ;  
    int columns = 20;
    char gameboard[4][20] = { // use 2D array to store modifiable strings
                    "3 ___|___|___",
                    "2 ___|___|___",
                    "1 ___|___|___",
                    "   A   B   C "  };
    char defaultboard[4][20] = { // store a newboard to reset gameboard when called for
                    "3 ___|___|___",
                    "2 ___|___|___",
                    "1 ___|___|___",
                    "   A   B   C "  };

    bool gameover = false;
    int turn = 0;       // 0 = player A turn. 1 = player B turn
    // Main game while loop
    while (!gameover) {
        char move[20];  // extra space in the move char array in case user inputs longer invalid move
        while (turn == 0) {
            printboard(rows, columns, gameboard);
            printf("\nPlayer 1's Move ('quit' to exit game | 'r' to start new game): ");
            scanf("%10s", move);
            int length = strlen(move);
            bool char1Check = (move[0] == 'A' ) || (move[0] == gameboard[3][7]) || move[0] == gameboard[3][11] ;
            bool char2Check = ((int)move[1] - 52 < 0 );
            if (strcmp(move, "quit") == 0 ) {
                printf("Exiting Game...\n");
                gameover = true;
                break;
            } else if (length == 2 && (char1Check == true)  && (char2Check  == true) ) {
                if (checkmove(move, rows, columns, gameboard) == true) {
                    updateboard(turn, move, rows, columns, gameboard);
                    if ( checkwin(0, rows, columns, gameboard) ){
                        printboard(rows, columns, gameboard);
                        printf("Player 1 wins!\n");    // player 1 wins, exit game
                        gameover = true;
                        break;
                    } else {
                        turn = 1;   // no win yet, continue
                    }
                } else {
                    printf("Invalid move, position already marked.");
                }
            } else {
                if (length < 2 ) {
                    if (strcmp(move, "r") == 0 ){
                        resetboard(rows, columns, gameboard, defaultboard);
                    } else {
                        printf("Invalid move, please specify both column and row.\n");
                    }
                } else {
                    printf("Invalid move. Enter again.\n");
                } 
            }   
        }
        while (turn == 1) {
            printboard(rows, columns, gameboard);
            printf("\nPlayer 2's Move (enter 'quit' to exit game | 'r' to start new game): ");
            scanf("%10s", move);
            bool char1Check = (move[0] == 'A' ) || (move[0] == gameboard[3][7]) || move[0] == gameboard[3][11] ;
            bool char2Check = ((int)move[1] - 52 < 0 );
            int length = strlen(move);
            if (strcmp(move, "quit") == 0) {
                printf("Exiting Game...\n");
                gameover = true;
                break;
            } else if (length == 2 && (char1Check == true)  && (char2Check  == true) ) {
                if (checkmove(move, rows, columns, gameboard) == true ) {
                    updateboard(turn, move, rows, columns, gameboard);
                    if (checkwin(1, rows, columns, gameboard)){
                        printf("Player 2 wins!\n");    // player 2 won, exit game
                        printboard(rows, columns, gameboard);
                        gameover = true;
                        break;
                    } else {
                        turn = 0;                      // no win found, switch turns
                    }
                } else {
                    printf("Invalid move. Position already marked.\n");
                }
            }  else {
                if (length < 2) {
                    if (strcmp(move, "r") == 0 ){
                        resetboard(rows, columns, gameboard, defaultboard);
                    } else {
                        printf("Invalid move, please specify both column and row.\n");
                    }
                } else {
                    printf("Invalid move. Enter again.\n");
                }
            }
        }
         
    }

}

//EOF//
