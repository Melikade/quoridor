#ifndef UNTITLED52_DFS_H
#define UNTITLED52_DFS_H
// initializing visited array
void InitialVisited(int nodes) {
    int i;
    for (i = 0; i < nodes; i++) {
        visited[i] = 0;
    }
}

//declare nodename array
void DeclareNodeName(int count) {
    int i, j;
    int k = 0;
    for (i = 0; i < count; i++) {
        for (j = 0; j < count; j++) {
            nodename[i][j] = k;
            k++;
        }
    }
}

//initializing graph array
void InitialGraph(int count, int nodes) {
    int i, j;
    for (i = 0; i < nodes; i++) {
        for (j = 0; j < nodes; j++) {
            graph[i][j] = 0;
        }
    }
    for (i = 0; i < count; i++) {
        for (j = 0; j < count; j++) {
            if (i - 1 >= 0) {
                graph[nodename[i][j]][nodename[i - 1][j]] = 1;
            }
            if (j - 1 >= 0) {
                graph[nodename[i][j]][nodename[i][j - 1]] = 1;
            }
            if (i + 1 < count) {
                graph[nodename[i][j]][nodename[i + 1][j]] = 1;
            }
            if (j + 1 < count) {
                graph[nodename[i][j]][nodename[i][j + 1]] = 1;
            }
        }
    }
}

// check that if there is a root for winning
void dfs(int vertex, int nodes) {
    visited[vertex] = 1;
    int i;
    for (i = 0; i < nodes; i++) {
        if (graph[vertex][i] && !visited[i]) {
            dfs(i, nodes);
        }
    }
}

#endif
