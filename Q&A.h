#ifndef Q&A_H_INCLUDED
#define Q&A_H_INCLUDED

// questions and answers
int QandA(char TypePlayer[50], char name1[40], char name2[40], char name[40], int *countwall1, int *countwall2) {
    while (1) {
        printf("Would you like to play with the computer or a friend?\n");
        gets(TypePlayer);
        if (strcmp(TypePlayer, "friend") == 0) {
            // Asking the number of walls allowed for each player and the name of each player
            printf("How many walls are allowed for player1 ?\n");
            scanf("%d", countwall1);
            printf("How many walls are allowed for player2 ?\n");
            scanf("%d", countwall2);
            printf("What is the name of player1 ?\n");
            gets(enter);
            gets(name1);
            printf("What is the name of player2 ?\n");
            gets(name2);
            system("cls");
            return 1;
        } else if (strcmp(TypePlayer, "computer") == 0) {
            // asking the number of walls allowed for player and the computer
            printf("How many walls are allowed for human ?\n");
            scanf("%d", countwall1);
            printf("How many walls are allowed for computer ?\n");
            scanf("%d", countwall2);
            printf("What is the name of human ?\n");
            gets(enter);
            gets(name);
            system("cls");
            return 2;
        } else {
            printf("incorrect input!\n");
        }
    }
}

#endif
