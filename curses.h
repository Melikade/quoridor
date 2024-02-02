#ifndef UNTITLED52_CURSES_H
#define UNTITLED52_CURSES_H

// curse of clearing all the walls on the board
void ClearAllWalls(int x1, int x2, int y1, int y2, int count, int nodes) {
    InitialGraph(count, nodes);
    screen(count);
    board[x1][y1] = pieces1;
    board[x2][y2] = pieces2;
}

// curse of decreasing the number of walls
void DecreaseCountWall(int *countwall) {
    srand(time(NULL));
    int random = rand() % 3;
    if (random == 0) {
        *countwall -= 2;
        if (*countwall < 0)
            *countwall = 0;
    } else if (random == 1) {
        *countwall -= 3;
        if (*countwall < 0)
            *countwall = 0;
    } else {
        *countwall -= 5;
        if (*countwall < 0)
            *countwall = 0;
    }
}

// curse of being blocked for 1 or 2 rounds
void BlockPlayer(int *countblock) {
    srand(time(NULL));
    if (rand() % 2 + 1 == 1)
        *countblock = 1;
    else
        *countblock = 2;
}

#endif
