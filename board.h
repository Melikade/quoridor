#ifndef UNTITLED52_BOARD_H
#define UNTITLED52_BOARD_H
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
