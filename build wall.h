#ifndef UNTITLED52_BUILD_WALL_H
#define UNTITLED52_BUILD_WALL_H
// building a wall
int CommandWall(int nodes, int xwall, int ywall, char typewall, int x1, int y1, int x2, int y2, int count) {
    int sw1 = 1;
    int sw2 = 1;
    int sw3 = 1;
    int i, j;
    if (typewall == 'V') {
        graph[nodename[xwall][ywall]][nodename[xwall][ywall + 1]] = 0;
        graph[nodename[xwall][ywall + 1]][nodename[xwall][ywall]] = 0;
        graph[nodename[xwall + 1][ywall]][nodename[xwall + 1][ywall + 1]] = 0;
        graph[nodename[xwall + 1][ywall + 1]][nodename[xwall + 1][ywall]] = 0;

        // check that if there is at least one way to win
        dfs(nodename[(x2 - 1) / 2][(y2 - 3) / 5], nodes);
        for (i = 0; i < count && sw1 == 1; i++) {
            if (visited[nodename[0][i]] == 1)
                sw1 = 0;

        }
        InitialVisited(nodes);
        dfs(nodename[(x1 - 1) / 2][(y1 - 3) / 5], nodes);
        for (i = 0; i < count && sw2 == 1; i++) {
            if (visited[nodename[count - 1][i]] == 1)
                sw2 = 0;
        }
        InitialVisited(nodes);
        //Checking if there is already a wall here or if the wall doesn't stick out of the screen
        for (i = 2 * xwall + 1; i <= 2 * xwall + 3 && sw3 == 1; i++) {
            if (board[i][5 * (ywall + 1)] == wall || i >= 2 * (count) || 5 * (ywall + 1) >= 5 * count) {
                sw3 = 0;
            }
        }
        if (sw1 == 0 && sw2 == 0 && sw3 == 1) {
            //Let's build the wall
            board[2 * xwall + 1][5 * (ywall + 1)] = wall;
            board[2 * xwall + 1][5 * (ywall + 1) + 1] = wall;
            board[2 * xwall + 2][5 * (ywall + 1)] = wall;
            board[2 * xwall + 2][5 * (ywall + 1) + 1] = wall;
            board[2 * xwall + 3][5 * (ywall + 1)] = wall;
            board[2 * xwall + 3][5 * (ywall + 1) + 1] = wall;
            return 1;
        } else {
            printf("you can't build a wall here!\n");
            graph[nodename[xwall][ywall]][nodename[xwall][ywall + 1]] = 1;
            graph[nodename[xwall][ywall + 1]][nodename[xwall][ywall]] = 1;
            graph[nodename[xwall + 1][ywall]][nodename[xwall + 1][ywall + 1]] = 1;
            graph[nodename[xwall + 1][ywall + 1]][nodename[xwall + 1][ywall]] = 1;
            return 0;
        }
    }
    if (typewall == 'H') {
        graph[nodename[xwall][ywall]][nodename[xwall + 1][ywall]] = 0;
        graph[nodename[xwall + 1][ywall]][nodename[xwall][ywall]] = 0;
        graph[nodename[xwall][ywall + 1]][nodename[xwall + 1][ywall + 1]] = 0;
        graph[nodename[xwall + 1][ywall + 1]][nodename[xwall][ywall + 1]] = 0;
        // check that if there is at least one way to win
        dfs(nodename[(x2 - 1) / 2][(y2 - 3) / 5], nodes);
        for (i = 0; i < count && sw1 == 1; i++) {
            if (visited[nodename[0][i]] == 1)
                sw1 = 0;
        }
        InitialVisited(nodes);
        dfs(nodename[(x1 - 1) / 2][(y1 - 3) / 5], nodes);
        for (i = 0; i < count && sw2 == 1; i++) {
            if (visited[nodename[count - 1][i]] == 1)
                sw2 = 0;
        }
        InitialVisited(nodes);
        //Checking if there is already a wall here or if the wall doesn't stick out of the screen
        for (i = 5 * ywall + 2; i <= 5 * ywall + 9 && sw3 == 1; i++) {
            if (board[2 * xwall + 2][i] == wall || i >= 5 * count || 2 * xwall + 2 >= 2 * count) {
                sw3 = 0;
            }
        }
        if (sw1 == 0 && sw2 == 0 && sw3 == 1) {
            //Let's build the wall
            for (j = 5 * ywall + 2; j <= 5 * ywall + 9; j++) {
                board[2 * xwall + 2][j] = wall;
            }
            return 1;
        } else {
            printf("you can't build a wall here!\n");
            graph[nodename[xwall][ywall]][nodename[xwall + 1][ywall]] = 1;
            graph[nodename[xwall + 1][ywall]][nodename[xwall][ywall]] = 1;
            graph[nodename[xwall][ywall + 1]][nodename[xwall + 1][ywall + 1]] = 1;
            graph[nodename[xwall + 1][ywall + 1]][nodename[xwall][ywall + 1]] = 1;
            return 0;
        }
    }
}
// checking the computer's vertical wall coordinates
int CheckCompWallVertical(int count, int nodes, int x1, int y1, int x2, int y2) {
    int xwall, ywall, i, sw1 = 1, sw2 = 1, sw3 = 1;
    srand(time(NULL));
    xwall = rand() % (count - 1);
    ywall = rand() % (count - 1);
    graph[nodename[xwall][ywall]][nodename[xwall][ywall + 1]] = 0;
    graph[nodename[xwall][ywall + 1]][nodename[xwall][ywall]] = 0;
    graph[nodename[xwall + 1][ywall]][nodename[xwall + 1][ywall + 1]] = 0;
    graph[nodename[xwall + 1][ywall + 1]][nodename[xwall + 1][ywall]] = 0;

    // check that if there is at least one way to win
    dfs(nodename[(x2 - 1) / 2][(y2 - 3) / 5], nodes);
    for (i = 0; i < count && sw1 == 1; i++) {
        if (visited[nodename[0][i]] == 1)
            sw1 = 0;
    }

    InitialVisited(nodes);
    dfs(nodename[(x1 - 1) / 2][(y1 - 3) / 5], nodes);
    for (i = 0; i < count && sw2 == 1; i++) {
        if (visited[nodename[count - 1][i]] == 1)
            sw2 = 0;
    }
    InitialVisited(nodes);
    //Checking if there is already a wall here or if the wall doesn't stick out of the screen
    for (i = 2 * xwall + 1; i <= 2 * xwall + 3 && sw3 == 1; i++) {
        if (board[i][5 * (ywall + 1)] == wall) {
            sw3 = 0;
        }
    }

    if (sw1 == 0 && sw2 == 0 && sw3 == 1) {
        //Let's build the wall
        board[2 * xwall + 1][5 * (ywall + 1)] = wall;
        board[2 * xwall + 1][5 * (ywall + 1) + 1] = wall;
        board[2 * xwall + 2][5 * (ywall + 1)] = wall;
        board[2 * xwall + 2][5 * (ywall + 1) + 1] = wall;
        board[2 * xwall + 3][5 * (ywall + 1)] = wall;
        board[2 * xwall + 3][5 * (ywall + 1) + 1] = wall;
        return 1;
    } else {
        graph[nodename[xwall][ywall]][nodename[xwall][ywall + 1]] = 1;
        graph[nodename[xwall][ywall + 1]][nodename[xwall][ywall]] = 1;
        graph[nodename[xwall + 1][ywall]][nodename[xwall + 1][ywall + 1]] = 1;
        graph[nodename[xwall + 1][ywall + 1]][nodename[xwall + 1][ywall]] = 1;
        return 0;
    }
}

// checking the computer's horizontal wall coordinates
int CheckCompWallHorizontal(int count, int nodes, int x1, int y1, int x2, int y2) {
    int xwall, ywall, i, j, sw1 = 1, sw2 = 1, sw3 = 1;
    srand(time(NULL));
    xwall = rand() % (count - 1);
    ywall = rand() % (count - 1);
    graph[nodename[xwall][ywall]][nodename[xwall + 1][ywall]] = 0;
    graph[nodename[xwall + 1][ywall]][nodename[xwall][ywall]] = 0;
    graph[nodename[xwall][ywall + 1]][nodename[xwall + 1][ywall + 1]] = 0;
    graph[nodename[xwall + 1][ywall + 1]][nodename[xwall][ywall + 1]] = 0;
    // check that if there is at least one way to win
    dfs(nodename[(x2 - 1) / 2][(y2 - 3) / 5], nodes);
    for (i = 0; i < count && sw1 == 1; i++) {
        if (visited[nodename[0][i]] == 1)
            sw1 = 0;
    }
    InitialVisited(nodes);
    dfs(nodename[(x1 - 1) / 2][(y1 - 3) / 5], nodes);
    for (i = 0; i < count && sw2 == 1; i++) {
        if (visited[nodename[count - 1][i]] == 1)
            sw2 = 0;
    }
    InitialVisited(nodes);
    //Checking if there is already a wall here or if the wall doesn't stick out of the screen
    for (i = 5 * ywall + 2; i <= 5 * ywall + 9 && sw3 == 1; i++) {
        if (board[2 * xwall + 2][i] == wall) {
            sw3 = 0;
        }
    }
    if (sw1 == 0 && sw2 == 0 && sw3 == 1) {
        //Let's build the wall
        for (j = 5 * ywall + 2; j <= 5 * ywall + 9; j++) {
            board[2 * xwall + 2][j] = wall;
        }
        return 1;
    } else {
        graph[nodename[xwall][ywall]][nodename[xwall + 1][ywall]] = 1;
        graph[nodename[xwall + 1][ywall]][nodename[xwall][ywall]] = 1;
        graph[nodename[xwall][ywall + 1]][nodename[xwall + 1][ywall + 1]] = 1;
        graph[nodename[xwall + 1][ywall + 1]][nodename[xwall][ywall + 1]] = 1;
        return 0;
    }
}

#endif
