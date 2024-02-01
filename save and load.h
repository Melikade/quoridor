#ifndef UNTITLED52_SAVE_AND_LOAD_H
#define UNTITLED52_SAVE_AND_LOAD_H
// saving moves when playing with computer
void SaveGameComputer(int x1, int y1, int x2, int y2, int countwall1, int countwall2, char name[], int LengthName,
                      int count, int countblock1, int countblock2) {
    char FileName[50];
    char enter[5];
    int i;
    int PlayerType = 1;
    printf("please enter a name for your game:\n");
    gets(FileName);
    inFile = fopen(FileName, "w");
    fwrite(&PlayerType, sizeof(int), 1, inFile);
    fwrite(&x1, sizeof(int), 1, inFile);
    fwrite(&y1, sizeof(int), 1, inFile);
    fwrite(&x2, sizeof(int), 1, inFile);
    fwrite(&y2, sizeof(int), 1, inFile);
    fwrite(&countwall1, sizeof(int), 1, inFile);
    fwrite(&countwall2, sizeof(int), 1, inFile);
    fwrite(name, sizeof(char), 40, inFile);
    fwrite(&count, sizeof(int), 1, inFile);
    fwrite(&countblock1, sizeof(int), 1, inFile);
    fwrite(&countblock2, sizeof(int), 1, inFile);
    for (i = 0; i < 2 * count + 1; i++) {
        fwrite(board[i], sizeof(char), 5 * count + 2, inFile);
    }
    for (i = 0; i < (count) * (count); i++) {
        fwrite(graph[i], sizeof(int), (count) * (count), inFile);
    }
    fclose(inFile);
}

// saving moves when playing with human
void SaveGameHuman(int x1, int y1, int x2, int y2, int countwall1, int countwall2, char name1[], int LengthName1,
                   char name2[], int LengthName2, int count, int PlayerTurn,  int countblock1, int countblock2) {
    char FileName[50];
    char enter[5];
    int i;
    int PlayerType = 2;
    printf("please enter a name for your game:\n");
    gets(FileName);
    inFile = fopen(FileName, "w");
    fwrite(&PlayerType, sizeof(int), 1, inFile);
    fwrite(&x1, sizeof(int), 1, inFile);
    fwrite(&y1, sizeof(int), 1, inFile);
    fwrite(&x2, sizeof(int), 1, inFile);
    fwrite(&y2, sizeof(int), 1, inFile);
    fwrite(&countwall1, sizeof(int), 1, inFile);
    fwrite(&countwall2, sizeof(int), 1, inFile);
    fwrite(name1, sizeof(char), 40, inFile);
    fwrite(name2, sizeof(char), 40, inFile);
    fwrite(&count, sizeof(int), 1, inFile);
    fwrite(&countblock1, sizeof(int), 1, inFile);
    fwrite(&countblock2, sizeof(int), 1, inFile);
    for (i = 0; i < 2 * count + 1; i++) {
        fwrite(board[i], sizeof(char), 5 * count + 2, inFile);
    }
    for (i = 0; i < count * count; i++) {
        fwrite(graph[i], sizeof(int), count * count, inFile);
    }
    fwrite(&PlayerTurn, sizeof(int), 1, inFile);
    fclose(inFile);
}

// loading saved file
int LoadGameFile(char query[50]) {
    inFile = fopen(query, "r");
    if (!inFile) {
        printf("file NOT found, please try AGAIN!\n");
        return 0;
    } else {
        return 1;
    }
}

// get the condition in the last game when second player was computer
void LoadGameConditionWithComputer(int *x1, int *y1, int *x2, int *y2, int *countwall1, int *countwall2, char name[40],
                                   int *count ,int* countblock1, int* countblock2) {
    int i;

    fread(x1, sizeof(int), 1, inFile);
    fread(y1, sizeof(int), 1, inFile);
    fread(x2, sizeof(int), 1, inFile);
    fread(y2, sizeof(int), 1, inFile);
    fread(countwall1, sizeof(int), 1, inFile);
    fread(countwall2, sizeof(int), 1, inFile);
    fread(name, sizeof(char), 40, inFile);
    fread(count, sizeof(int), 1, inFile);
    fread(countblock1, sizeof(int), 1, inFile);
    fread(countblock2, sizeof(int), 1, inFile);
    for (i = 0; i < 2 * (*count) + 1; i++) {
        fread(board[i], sizeof(char), 5 * (*count) + 2, inFile);
    }
    for (i = 0; i < (*count) * (*count); i++) {
        fread(graph[i], sizeof(int), (*count) * (*count), inFile);
    }
    fclose(inFile);
}

// get the condition in the last game when second player was a friend
void LoadGameConditionWithHuman(int *x1, int *y1, int *x2, int *y2, int *countwall1, int *countwall2, char name1[40],
                                char name2[40], int *count, int *PlayerTurn,int* countblock1, int* countblock2) {
    int i;

    fread(x1, sizeof(int), 1, inFile);
    fread(y1, sizeof(int), 1, inFile);
    fread(x2, sizeof(int), 1, inFile);
    fread(y2, sizeof(int), 1, inFile);
    fread(countwall1, sizeof(int), 1, inFile);
    fread(countwall2, sizeof(int), 1, inFile);
    fread(name1, sizeof(char), 40, inFile);
    fread(name2, sizeof(char), 40, inFile);
    fread(count, sizeof(int), 1, inFile);
    fread(countblock1, sizeof(int), 1, inFile);
    fread(countblock2, sizeof(int), 1, inFile);
    for (i = 0; i < 2 * (*count) + 1; i++) {
        fread(board[i], sizeof(char), 5 * (*count) + 2, inFile);
    }
    for (i = 0; i < (*count) * (*count); i++) {
        fread(graph[i], sizeof(int), (*count) * (*count), inFile);
    }
    fread(PlayerTurn, sizeof(int), 1, inFile);
    fclose(inFile);
}

#endif
