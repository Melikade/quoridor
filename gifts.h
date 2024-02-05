#ifndef UNTITLED52_GIFTS_H
#define UNTITLED52_GIFTS_H

// gift of increasing the number of walls
void IncreaseCountWall(int *countwall) {
    srand(time(NULL));
    int random = rand() % 3;
    if (random == 0) {
        *countwall += 2;
    } else if (random == 1) {
        *countwall += 3;
    } else {
        *countwall += 5;
    }
}

// gift of increasing the number of walls for player and decreasing the number of walls of opponent
void IncreaseAndDecreaseCountWall(int *countwall1, int *counwall2) {
    srand(time(NULL));
    if (rand() % 2 == 0) {
        *countwall1 += 1;
        *counwall2 -= 1;
        if (*counwall2 < 0)
            *counwall2 = 0;
    } else {
        *countwall1 += 2;
        *counwall2 -= 2;
        if (*counwall2 < 0)
            *counwall2 = 0;
    }
}

#endif
