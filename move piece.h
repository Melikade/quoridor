#ifndef UNTITLED52_MOVE_PIECE_H
#define UNTITLED52_MOVE_PIECE_H
// checking if the move that the player has chosen is allowed or not
int CheckMove(int x, int y, int xtemp, int ytemp, int count) {
    x = 2 * x + 1;
    y = 5 * y + 3;
    if (board[x][y] == pieces1 || board[x][y] == pieces2) {
        printf("you can't put your piece here!\n");
        return 0;
    } else {
        if (x - xtemp == 2 && y - ytemp == 0 && x < 2 * count) {
            if (board[xtemp + 1][y] == wall) {
                printf("you can't put your piece here!\n");
                return 0;
            } else { return 1; }
        } else if (xtemp - x == 2 && y - ytemp == 0 && x > 0) {
            if (board[xtemp - 1][y] == wall) {
                printf("you can't put your piece here!\n");
                return 0;
            } else { return 1; }
        } else if (y - ytemp == 5 && x - xtemp == 0 && y < 5 * count - 1) {
            if (board[x][ytemp + 2] == wall) {
                printf("you can't put your piece here!\n");
                return 0;
            } else { return 1; }
        } else if (ytemp - y == 5 && x - xtemp == 0 && y > 2) {
            if (board[x][ytemp - 2] == wall) {
                printf("you can't put your piece here!\n");
                return 0;
            } else { return 1; }
        } else {
            printf("you can't put your piece here!\n");
            return 0;
        }
    }
}

// checking the computer's piece moves
int CheckCompMove(int x, int y, int count) {
    int option;
    while (1) {
        srand(time(NULL));
        option = rand() % 4 + 1;
        // option=1 means up,  option=2 means right,  option=3 means down,  option=4 means left
        if (option == 1) {
            if (x - 2 > 0 && board[x - 2][y] != pieces1 && board[x - 1][y] != wall) {
                return 1;
            }
        } else if (option == 2) {
            if (y + 5 < 5 * count + 2 && board[x][y + 5] != pieces1 && board[x][y + 2] != wall) {
                return 2;
            }
        } else if (option == 3) {
            if (x + 2 < 2 * count + 1 && board[x + 2][y] != pieces1 && board[x + 1][y] != wall) {
                return 3;
            }
        } else {
            if (y - 5 > 0 && board[x][y - 5] != pieces1 && board[x][y - 2] != wall) {
                return 4;
            }
        }
    }
}

#endif
