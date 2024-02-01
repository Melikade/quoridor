#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
char border = 219;
char wall = 176;
char pieces1 = 232;
char pieces2 = 233;
char space = 32;
int visited[10000];
char board[100][100];
int graph[10000][10000];
int nodename[100][100];
FILE *inFile;

// defining variables and constants and initializing some of them
int count;
int countblock1, countblock2;
int countwall1;
int countwall2;
char name[40];
char name1[40];
char name2[40];
char enter[5];
char TypePlayer[50];
int x1, y1, x2, y2;
char LoadCommand[10];
char Query[50];
int PlayerTurn;
int PlayerType;
// making the board
void screen(int count) {
    int i, j;
    for (i = 0; i < 2 * count + 1; i++) {
        if (i % 2 == 0) {
            for (j = 0; j < 5 * count + 2; j++) {
                board[i][j] = border;
            }
        } else {
            for (j = 0; j < 5 * count + 2; j++) {
                if (j % 5 == 0 || j % 5 == 1) {
                    board[i][j] = border;
                } else {
                    board[i][j] = space;
                }
            }
        }
    }
}
void PrintBoard(int count) {
    int i, j;
    for (i = 0; i < 2 * count + 1; i++) {
        for (j = 0; j < 5 * count + 2; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}
#endif
