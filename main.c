#include "global declarations.h"
#include "board.h"
#include "DFS.h"
#include "build wall.h"
#include "move piece.h"
#include "curses.h"
#include "gifts.h"
#include "save and load.h"

// curse or gift function
void CurseOrGift(int x1, int x2, int y1, int y2, int count, int nodes, int *countblock, int *countwall1, int *counwall2) {
    srand(time(NULL));
    int random=rand() % 5;
    printf("A box is opening...\n");
    if (random == 0) {
        printf("You've gotten a curse!\nAll of the walls will be removed!\n");
        ClearAllWalls(x1, x2, y1, y2, count, nodes);
    }
    else if (random == 1) {
        // check if run error
        printf("You've gotten a curse!\nThe capacity of your walls has been reduced!\n");
        DecreaseCountWall(countwall1);
        printf("You have only %d walls left!\n",*countwall1);
    }
    else if (random == 2) {
        BlockPlayer(countblock);
        printf("You've gotten a curse!\nYou cannot play for %d round!\n",*countblock);
    }
    else if (random == 3) {
        printf("You've gotten a gift!\nThe capacity of your walls has been increased!\n");
        IncreaseCountWall(countwall1);
        printf("You now have %d walls!\n",*countwall1);
    }
    else {
        printf("You've gotten a gift!\nThe capacity of you and your opponents walls have been changed!\n");
        IncreaseAndDecreaseCountWall(countwall1, counwall2);
        printf("You now have %d walls and your opponent has %d walls!\n",*countwall1,*counwall2);
    }
}


//if second player is human, this function is used to continue the game and announce the winner:
void
HumanPlayer(int count, char name1[], int LengthName1, char name2[], int LengthName2, int countwall1, int countwall2) {
    int x1, y1, x2, y2, sww1, sww2;
    int countblock1=0, countblock2=0;
    char enter[5];
    char commandstr[100];
    int xwall1, ywall1, xwall2, ywall2;
    char typewall1;
    char typewall2;
    char CommandSave[50];

    // placing the pieces at the beginning
    board[1][(count / 2) * 5 + 3] = pieces1;
    board[2 * count - 1][(count / 2) * 5 + 3] = pieces2;
    x1 = 1;
    y1 = (count / 2) * 5 + 3;
    x2 = 2 * count - 1;
    y2 = (count / 2) * 5 + 3;

    // show each player's piece
    printf("Dear %s ,your piece is : %c\n", name1, pieces1);
    printf("Dear %s ,your piece is : %c\n", name2, pieces2);
    // turning the board into  a graph
    int nodes = count * count;
    InitialVisited(nodes);
    DeclareNodeName(count);
    InitialGraph(count, nodes);

    //Updating the board
    PrintBoard(count);
    while (1) {
        if(countblock1==0)
            sww1 = 1;
        else {
            sww1 = 0;
            countblock1--;
        }
        while (sww1 == 1) {
            // Asking about the next move of player1
            printf("Dear %s ,do you want to move your piece(1) or do you want to build a wall(2) ?\n", name1);
            gets(commandstr);

            // if command is moving the piece
            if (commandstr[0] == '1' && commandstr[1] == 0) {
                int xtemp1 = x1;
                int ytemp1 = y1;
                printf("Enter the x and y component with the format: <x y> ;pay attention that we count from from zero!\n");
                scanf("%d %d", &x1, &y1);
                gets(enter);
                if (CheckMove(x1, y1, xtemp1, ytemp1, count) == 1) {
                    board[xtemp1][ytemp1] = space;
                    board[2 * x1 + 1][5 * y1 + 3] = pieces1;
                    x1 = 2 * x1 + 1;
                    y1 = 5 * y1 + 3;
                    sww1 = 0;
                } else {
                    x1 = xtemp1;
                    y1 = ytemp1;
                }
            }
                //if command is building the wall
            else if (commandstr[0] == '2' && commandstr[1] == 0) {
                printf("Enter the x and y of the starting point of the wall and enter the type of wall(H or V) with the format: <x y type> ; pay attention that we start counting from zero !\n");
                scanf("%d %d %c", &xwall1, &ywall1, &typewall1);
                gets(enter);
                if (typewall1 != 'V' && typewall1 != 'H') {
                    printf("incorrect input, please try Again !\n");
                }

                    // Let's check if there is a wall left
                else if (countwall1 == 0) {
                    printf("YOU ARE OUT OF WALL!\n");
                } else {
                    // check that if it is logically possible to build a wall there or not
                    if (CommandWall(nodes, xwall1, ywall1, typewall1, x1, y1, x2, y2, count) == 1) {
                        sww1 = 0;
                        countwall1--;
                    }

                }
            }
                //if user input was not one of our options:
            else {
                printf("incorrect input, please try Again !\n");
            }
            if(sww1==0)
                system("cls");
            //opening a random gift or curse box
            if(sww1==0 && x1 != 2 * count - 1){
                CurseOrGift(x1,x2,y1,y2,count,nodes,&countblock1,&countwall1,&countwall2);
            }
            if(sww1==0) {
                PrintBoard(count);
                //asking if the player wants to save the game
                while (1) {
                    printf("do you want to save the game (1) or do you want to continue (2)? \n");
                    gets(CommandSave);
                    if (strcmp(CommandSave, "1") == 0) {
                        SaveGameHuman(x1, y1, x2, y2, countwall1, countwall2, name1, 40, name2, 40, count, 2, countblock1, countblock2);
                        break;
                    } else if (strcmp(CommandSave, "2") == 0) {
                        break;
                    } else {
                        printf("your input is not one of our options!please try again\n");
                    }
                }
            }
        }
        if (x1 == 2 * count - 1) {
            printf(" **%s** you won", name1);
            break;
        }
        system("cls");
        PrintBoard(count);
        if(countblock2==0)
            sww2 = 1;
        else {
            sww2 = 0;
            countblock2--;
        }
        while (sww2 == 1) {
            // Asking about the next move of player2
            printf("Dear %s ,do you want to move your piece(1) or do you want to build a wall(2) ?\n", name2);
            gets(commandstr);

            //if command is moving the piece
            if (commandstr[0] == '1' && commandstr[1] == 0) {
                int xtemp2 = x2;
                int ytemp2 = y2;
                printf("Enter the x and y component with the format: <x y> ;pay attention that we count from from zero!\n");
                scanf("%d %d", &x2, &y2);
                gets(enter);
                if (CheckMove(x2, y2, xtemp2, ytemp2, count) == 1) {
                    board[xtemp2][ytemp2] = space;
                    board[2 * x2 + 1][5 * y2 + 3] = pieces2;
                    x2 = 2 * x2 + 1;
                    y2 = 5 * y2 + 3;
                    sww2 = 0;
                } else {
                    x2 = xtemp2;
                    y2 = ytemp2;
                }
            }
                //if command is building the wall
            else if (commandstr[0] == '2' && commandstr[1] == 0) {
                printf("Enter the x and y of the starting point of the wall and enter the type of wall(H or V) with the format: <x y type> ; pay attention that we start counting from zero !\n");
                scanf("%d %d %c", &xwall2, &ywall2, &typewall2);
                gets(enter);
                if (typewall2 != 'V' && typewall2 != 'H') {
                    printf("incorrect input, please try Again !\n");
                }

                    // Let's check if there is a wall left
                else if (countwall2 == 0) {
                    printf("YOU ARE OUT OF WALL!\n");
                } else {
                    // check that if it is logically possible to build a wall there or not
                    if (CommandWall(nodes, xwall2, ywall2, typewall2, x1, y1, x2, y2, count) == 1) {
                        sww2 = 0;
                        countwall2--;
                    }
                }
            }
                //if user input was not one of our options:
            else {
                printf("incorrect input, please try Again !\n");
            }
            if(sww2==0)
                system("cls");
            //opening a random gift or curse box
            if(sww2==0 && x2 != 1){
                CurseOrGift(x1,x2,y1,y2,count,nodes,&countblock2,&countwall2,&countwall1);
            }
            if(sww2==0){
                PrintBoard(count);
                //asking if the player wants to save the game
                while (1) {
                    printf("do you want to save the game (1) or do you want to continue (2)? \n");
                    gets(CommandSave);
                    if (strcmp(CommandSave, "1") == 0) {
                        SaveGameHuman(x1, y1, x2, y2, countwall1, countwall2, name1, 40, name2, 40, count, 1, countblock1, countblock2);
                        break;
                    } else if (strcmp(CommandSave, "2") == 0) {
                        break;
                    } else {
                        printf("your input is not one of our options!please try again\n");
                    }
                }
            }
        }
        if (x2 == 1) {
            printf(" **%s** you won", name2);
            break;
        }
        system("cls");
        PrintBoard(count);
    }
}

//if second player is computer, this function is used to continue the game and announce the winner:
void ComputerPlayer(int count, char name[], int LengthName, int countwall1, int countwall2) {
    char enter[5];
    int x1, y1, x2, y2;
    char commandstr[100];
    int xwall1, ywall1;
    char typewall1;
    int CommandComputer;
    char typewall2;
    char CommandSave[50];
    int sww1, sww2;
    int countblock1=0, countblock2=0;

    // placing the pieces at the beginning
    board[1][(count / 2) * 5 + 3] = pieces1;
    board[2 * count - 1][(count / 2) * 5 + 3] = pieces2;
    x1 = 1;
    y1 = (count / 2) * 5 + 3;
    x2 = 2 * count - 1;
    y2 = (count / 2) * 5 + 3;

    // show each player's piece
    printf("Dear %s ,your piece is : %c\n", name, pieces1);
    printf("computer piece is : %c\n", pieces2);
    // turning the board into  a graph
    int nodes = count * count;
    InitialVisited(nodes);
    DeclareNodeName(count);
    InitialGraph(count, nodes);

    //Updating the board
    PrintBoard(count);
    while (1) {
        if(countblock1==0)
            sww1 = 1;
        else {
            sww1 = 0;
            countblock1--;
        }
        while (sww1 == 1) {
            // Asking about the next move of player
            printf("Dear %s ,do you want to move your piece(1) or do you want to build a wall(2) ?\n", name);
            gets(commandstr);

            // if command is moving the piece
            if (commandstr[0] == '1' && commandstr[1] == 0) {
                int xtemp1 = x1;
                int ytemp1 = y1;
                printf("Enter the x and y component with the format: <x y> ;pay attention that we count from from zero!\n");
                scanf("%d %d", &x1, &y1);
                gets(enter);
                if (CheckMove(x1, y1, xtemp1, ytemp1, count) == 1) {
                    board[xtemp1][ytemp1] = space;
                    board[2 * x1 + 1][5 * y1 + 3] = pieces1;
                    x1 = 2 * x1 + 1;
                    y1 = 5 * y1 + 3;
                    sww1 = 0;
                } else {
                    x1 = xtemp1;
                    y1 = ytemp1;
                }
            }
                //if command is building the wall
            else if (commandstr[0] == '2' && commandstr[1] == 0) {
                printf("Enter the x and y of the starting point of the wall and enter the type of wall(H or V) with the format: <x y type> ; pay attention that we start counting from zero !\n");
                scanf("%d %d %c", &xwall1, &ywall1, &typewall1);
                gets(enter);
                if (typewall1 != 'V' && typewall1 != 'H') {
                    printf("incorrect input, please try Again !\n");
                }

                    // Let's check if there is a wall left
                else if (countwall1 == 0) {
                    printf("YOU ARE OUT OF WALL!\n");
                } else {
                    // check that if it is logically possible to build a wall there or not
                    if (CommandWall(nodes, xwall1, ywall1, typewall1, x1, y1, x2, y2, count) == 1) {
                        sww1 = 0;
                        countwall1--;
                    }

                }
            }
                //if user input was not one of our options:
            else {
                printf("incorrect input, please try Again !\n");
            }
            if(sww1==0)
                system("cls");
            // opening a random gift or curse box
            if (sww1==0 && x1 != 2 * count - 1 ){
                CurseOrGift(x1,x2,y1,y2,count,nodes,&countblock1,&countwall1,&countwall2);
            }
            if(sww1==0){
                PrintBoard(count);
                //asking if the player wants to save the game
                while (1) {
                    printf("do you want to save the game (1) or do you want to continue (2)? \n");
                    gets(CommandSave);
                    if (strcmp(CommandSave, "1") == 0) {
                        SaveGameComputer(x1, y1, x2, y2, countwall1, countwall2, name, 40, count, countblock1, countblock2);
                        break;
                    } else if (strcmp(CommandSave, "2") == 0) {
                        break;
                    } else {
                        printf("your input is not one of our options!please try again\n");
                    }
                }
            }
        }
        if (x1 == 2 * count - 1) {
            printf(" **%s** you won", name);
            break;
        }
        system("cls");
        PrintBoard(count);
        // Asking about the next move of computer
        if(countblock2==0)
            sww2 = 1;
        else {
            sww2 = 0;
            countblock2--;
        }
        while (sww2 == 1) {
            if (countwall2 == 0)
                CommandComputer = 1;
            else {
                srand(time(NULL));
                CommandComputer = rand() % 2 + 1;
            }

            // if command is moving the piece
            if (CommandComputer == 1) {
                if (CheckCompMove(x2, y2, count) == 1) {
                    board[x2][y2] = space;
                    x2 = x2 - 2;
                    board[x2][y2] = pieces2;
                    sww2 = 0;
                } else if (CheckCompMove(x2, y2, count) == 2) {
                    board[x2][y2] = space;
                    y2 = y2 + 5;
                    board[x2][y2] = pieces2;
                    sww2 = 0;
                } else if (CheckCompMove(x2, y2, count) == 3) {
                    board[x2][y2] = space;
                    x2 = x2 + 2;
                    board[x2][y2] = pieces2;
                    sww2 = 0;
                } else {
                    board[x2][y2] = space;
                    y2 = y2 - 5;
                    board[x2][y2] = pieces2;
                    sww2 = 0;
                }
            }

            // if command is building the wall
            if (CommandComputer == 2) {
                srand(time(NULL));
                typewall2 = rand() % 2 + 1;
                // typewall2=1 means Vertical, typewall2=2 means Horizontal
                if (typewall2 == 1) {
                    if (CheckCompWallVertical(count, nodes, x1, y1, x2, y2) == 1) {
                        sww2 = 0;
                        countwall2--;
                    }
                }
                if (typewall2 == 2) {
                    if (CheckCompWallHorizontal(count, nodes, x1, y1, x2, y2) == 1) {
                        sww2 = 0;
                        countwall2--;
                    }
                }
            }
            // opening a random gift or curse box
            if(sww2==0 && x2 != 1){
                CurseOrGift(x1,x2,y1,y2,count,nodes,&countblock2,&countwall2,&countwall1);
            }
        }
        if (x2 == 1) {
            printf(" **Computer** won");
            break;
        }
        system("cls");
        PrintBoard(count);
    }
}

// continue playing in a condition that: second player is human, it is the turn of the first player to play
void ContinueGameWithHumanFirst(int x1, int y1, int x2, int y2, int countwall1, int countwall2, char name1[],
                                int LengthName1, char name2[], int LengthName2, int count,int countblock1, int countblock2) {
    char enter[5];
    char commandstr[100];
    int xwall1, ywall1, xwall2, ywall2;
    char typewall1;
    char typewall2;
    char CommandSave[50];
    int sww1,sww2;

    // show each player's piece
    printf("Dear %s ,your piece is : %c\n", name1, pieces1);
    printf("Dear %s ,your piece is : %c\n", name2, pieces2);
    // turning the board into  a graph
    int nodes = count * count;
    InitialVisited(nodes);
    DeclareNodeName(count);

    //Updating the board
    PrintBoard(count);
    while (1) {
        if(countblock1==0)
            sww1 = 1;
        else {
            sww1 = 0;
            countblock1--;
        }
        while (sww1 == 1) {
            // Asking about the next move of player1
            printf("Dear %s ,do you want to move your piece(1) or do you want to build a wall(2) ?\n", name1);
            gets(commandstr);

            // if command is moving the piece
            if (commandstr[0] == '1' && commandstr[1] == 0) {
                int xtemp1 = x1;
                int ytemp1 = y1;
                printf("Enter the x and y component with the format: <x y> ;pay attention that we count from from zero!\n");
                scanf("%d %d", &x1, &y1);
                gets(enter);
                if (CheckMove(x1, y1, xtemp1, ytemp1, count) == 1) {
                    board[xtemp1][ytemp1] = space;
                    board[2 * x1 + 1][5 * y1 + 3] = pieces1;
                    x1 = 2 * x1 + 1;
                    y1 = 5 * y1 + 3;
                    sww1 = 0;
                } else {
                    x1 = xtemp1;
                    y1 = ytemp1;
                }
            }
                //if command is building the wall
            else if (commandstr[0] == '2' && commandstr[1] == 0) {
                printf("Enter the x and y of the starting point of the wall and enter the type of wall(H or V) with the format: <x y type> ; pay attention that we start counting from zero !\n");
                scanf("%d %d %c", &xwall1, &ywall1, &typewall1);
                gets(enter);
                if (typewall1 != 'V' && typewall1 != 'H') {
                    printf("incorrect input, please try Again !\n");
                }

                    // Let's check if there is a wall left
                else if (countwall1 == 0) {
                    printf("YOU ARE OUT OF WALL!\n");
                } else {
                    // check that if it is logically possible to build a wall there or not
                    if (CommandWall(nodes, xwall1, ywall1, typewall1, x1, y1, x2, y2, count) == 1) {
                        sww1 = 0;
                        countwall1--;
                    }

                }
            }
                //if user input was not one of our options:
            else {
                printf("incorrect input, please try Again !\n");
            }
            if(sww1==0)
                system("cls");
            // opening a random gift or curse box
            if(sww1==0 && x1 != 2 * count - 1){
                CurseOrGift(x1,x2,y1,y2,count,nodes,&countblock1,&countwall1,&countwall2);
            }
            if(sww1==0){
                PrintBoard(count);
                //asking if the player wants to save the game
                while (1) {
                    printf("do you want to save the game (1) or do you want to continue (2)? \n");
                    gets(CommandSave);
                    if (strcmp(CommandSave, "1") == 0) {
                        SaveGameHuman(x1, y1, x2, y2, countwall1, countwall2, name1, 40, name2, 40, count, 2, countblock1, countblock2);
                        break;
                    } else if (strcmp(CommandSave, "2") == 0) {
                        break;
                    } else {
                        printf("your input is not one of our options!please try again\n");
                    }
                }
            }
        }
        if (x1 == 2 * count - 1) {
            printf(" **%s** you won", name1);
            break;
        }
        system("cls");
        PrintBoard(count);
        if(countblock2==0)
            sww2 = 1;
        else {
            sww2 = 0;
            countblock2--;
        }
        while (sww2 == 1) {
            // Asking about the next move of player2
            printf("Dear %s ,do you want to move your piece(1) or do you want to build a wall(2) ?\n", name2);
            gets(commandstr);

            //if command is moving the piece
            if (commandstr[0] == '1' && commandstr[1] == 0) {
                int xtemp2 = x2;
                int ytemp2 = y2;
                printf("Enter the x and y component with the format: <x y> ;pay attention that we count from from zero!\n");
                scanf("%d %d", &x2, &y2);
                gets(enter);
                if (CheckMove(x2, y2, xtemp2, ytemp2, count) == 1) {
                    board[xtemp2][ytemp2] = space;
                    board[2 * x2 + 1][5 * y2 + 3] = pieces2;
                    x2 = 2 * x2 + 1;
                    y2 = 5 * y2 + 3;
                    sww2 = 0;
                } else {
                    x2 = xtemp2;
                    y2 = ytemp2;
                }
            }
                //if command is building the wall
            else if (commandstr[0] == '2' && commandstr[1] == 0) {
                printf("Enter the x and y of the starting point of the wall and enter the type of wall(H or V) with the format: <x y type> ; pay attention that we start counting from zero !\n");
                scanf("%d %d %c", &xwall2, &ywall2, &typewall2);
                gets(enter);
                if (typewall2 != 'V' && typewall2 != 'H') {
                    printf("incorrect input, please try Again !\n");
                }

                    // Let's check if there is a wall left
                else if (countwall2 == 0) {
                    printf("YOU ARE OUT OF WALL!\n");
                } else {
                    // check that if it is logically possible to build a wall there or not
                    if (CommandWall(nodes, xwall2, ywall2, typewall2, x1, y1, x2, y2, count) == 1) {
                        sww2 = 0;
                        countwall2--;
                    }
                }
            }
                //if user input was not one of our options:
            else {
                printf("incorrect input, please try Again !\n");
            }
            if(sww2==0)
                system("cls");
            //opening a random curse or gift box
            if(sww2==0 && x2 != 1){
                CurseOrGift(x1,x2,y1,y2,count,nodes,&countblock2,&countwall2,&countwall1);
            }
            if(sww2==0){
                PrintBoard(count);
                //asking if the player wants to save the game
                while (1) {
                    printf("do you want to save the game (1) or do you want to continue (2)? \n");
                    gets(CommandSave);
                    if (strcmp(CommandSave, "1") == 0) {
                        SaveGameHuman(x1, y1, x2, y2, countwall1, countwall2, name1, 40, name2, 40, count, 1, countblock1, countblock2);
                        break;
                    } else if (strcmp(CommandSave, "2") == 0) {
                        break;
                    } else {
                        printf("your input is not one of our options!please try again\n");
                    }
                }
            }
        }
        if (x2 == 1) {
            printf(" **%s** you won", name2);
            break;
        }
        system("cls");
        PrintBoard(count);
    }
}

// continue playing in a condition that: second player is human, it is the turn of the second player to play
void ContinueGameWithHumanSecond(int x1, int y1, int x2, int y2, int countwall1, int countwall2, char name1[],
                                 int LengthName1, char name2[], int LengthName2, int count,int countblock1, int countblock2) {
    char enter[5];
    char commandstr[100];
    int xwall1, ywall1, xwall2, ywall2;
    char typewall1;
    char typewall2;
    char CommandSave[50];
    int sww1, sww2;
    // show each player's piece
    printf("Dear %s ,your piece is : %c\n", name1, pieces1);
    printf("Dear %s ,your piece is : %c\n", name2, pieces2);
    // turning the board into  a graph
    int nodes = count * count;
    InitialVisited(nodes);
    DeclareNodeName(count);
    //Updating the board
    PrintBoard(count);
    while (1) {
        if(countblock2==0)
            sww2 = 1;
        else {
            sww2 = 0;
            countblock2--;
        }
        while (sww2 == 1) {
            // Asking about the next move of player2
            printf("Dear %s ,do you want to move your piece(1) or do you want to build a wall(2) ?\n", name2);
            gets(commandstr);

            //if command is moving the piece
            if (commandstr[0] == '1' && commandstr[1] == 0) {
                int xtemp2 = x2;
                int ytemp2 = y2;
                printf("Enter the x and y component with the format: <x y> ;pay attention that we count from from zero!\n");
                scanf("%d %d", &x2, &y2);
                gets(enter);
                if (CheckMove(x2, y2, xtemp2, ytemp2, count) == 1) {
                    board[xtemp2][ytemp2] = space;
                    board[2 * x2 + 1][5 * y2 + 3] = pieces2;
                    x2 = 2 * x2 + 1;
                    y2 = 5 * y2 + 3;
                    sww2 = 0;
                } else {
                    x2 = xtemp2;
                    y2 = ytemp2;
                }
            }
                //if command is building the wall
            else if (commandstr[0] == '2' && commandstr[1] == 0) {
                printf("Enter the x and y of the starting point of the wall and enter the type of wall(H or V) with the format: <x y type> ; pay attention that we start counting from zero !\n");
                scanf("%d %d %c", &xwall2, &ywall2, &typewall2);
                gets(enter);
                if (typewall2 != 'V' && typewall2 != 'H') {
                    printf("incorrect input, please try Again !\n");
                }

                    // Let's check if there is a wall left
                else if (countwall2 == 0) {
                    printf("YOU ARE OUT OF WALL!\n");
                } else {
                    // check that if it is logically possible to build a wall there or not
                    if (CommandWall(nodes, xwall2, ywall2, typewall2, x1, y1, x2, y2, count) == 1) {
                        sww2 = 0;
                        countwall2--;
                    }
                }
            }
                //if user input was not one of our options:
            else {
                printf("incorrect input, please try Again !\n");
            }
            if(sww2==0)
                system("cls");
            //opening a random curse or gift box
            if(sww2==0 && x2 != 1){
                CurseOrGift(x1,x2,y1,y2,count,nodes,&countblock2,&countwall2,&countwall1);
            }
            if(sww2==0){
                PrintBoard(count);
                //asking if the player wants to save the game
                while (1) {
                    printf("do you want to save the game (1) or do you want to continue (2)? \n");
                    gets(CommandSave);
                    if (strcmp(CommandSave, "1") == 0) {
                        SaveGameHuman(x1, y1, x2, y2, countwall1, countwall2, name1, 40, name2, 40, count, 1, countblock1, countblock2);
                        break;
                    } else if (strcmp(CommandSave, "2") == 0) {
                        break;
                    } else {
                        printf("your input is not one of our options!please try again\n");
                    }
                }
            }
        }
        if (x2 == 1) {
            printf(" **%s** you won", name2);
            break;
        }
        system("cls");
        PrintBoard(count);
        if(countblock1==0)
            sww1 = 1;
        else {
            sww1 = 0;
            countblock1--;
        }
        while (sww1 == 1) {
            // Asking about the next move of player1
            printf("Dear %s ,do you want to move your piece(1) or do you want to build a wall(2) ?\n", name1);
            gets(commandstr);

            // if command is moving the piece
            if (commandstr[0] == '1' && commandstr[1] == 0) {
                int xtemp1 = x1;
                int ytemp1 = y1;
                printf("Enter the x and y component with the format: <x y> ;pay attention that we count from from zero!\n");
                scanf("%d %d", &x1, &y1);
                gets(enter);
                if (CheckMove(x1, y1, xtemp1, ytemp1, count) == 1) {
                    board[xtemp1][ytemp1] = space;
                    board[2 * x1 + 1][5 * y1 + 3] = pieces1;
                    x1 = 2 * x1 + 1;
                    y1 = 5 * y1 + 3;
                    sww1 = 0;
                } else {
                    x1 = xtemp1;
                    y1 = ytemp1;
                }
            }
                //if command is building the wall
            else if (commandstr[0] == '2' && commandstr[1] == 0) {
                printf("Enter the x and y of the starting point of the wall and enter the type of wall(H or V) with the format: <x y type> ; pay attention that we start counting from zero !\n");
                scanf("%d %d %c", &xwall1, &ywall1, &typewall1);
                gets(enter);
                if (typewall1 != 'V' && typewall1 != 'H') {
                    printf("incorrect input, please try Again !\n");
                }

                    // Let's check if there is a wall left
                else if (countwall1 == 0) {
                    printf("YOU ARE OUT OF WALL!\n");
                } else {
                    // check that if it is logically possible to build a wall there or not
                    if (CommandWall(nodes, xwall1, ywall1, typewall1, x1, y1, x2, y2, count) == 1) {
                        sww1 = 0;
                        countwall1--;
                    }

                }
            }
                //if user input was not one of our options:
            else {
                printf("incorrect input, please try Again !\n");
            }
            if(sww1==0)
                system("cls");
            //opening a random gift or curse box
            if(sww1==0 && x1 != 2 * count - 1){
                CurseOrGift(x1,x2,y1,y2,count,nodes,&countblock1,&countwall1,&countwall2);
            }
            if(sww1==0){
                PrintBoard(count);
                //asking if the player wants to save the game
                while (1) {
                    printf("do you want to save the game (1) or do you want to continue (2)? \n");
                    gets(CommandSave);
                    if (strcmp(CommandSave, "1") == 0) {
                        SaveGameHuman(x1, y1, x2, y2, countwall1, countwall2, name1, 40, name2, 40, count, 2, countblock1, countblock2);
                        break;
                    } else if (strcmp(CommandSave, "2") == 0) {
                        break;
                    } else {
                        printf("your input is not one of our options!please try again\n");
                    }
                }
            }
        }
        if (x1 == 2 * count - 1) {
            printf(" **%s** you won", name1);
            break;
        }
        system("cls");
        PrintBoard(count);
    }
}

// continue playing in a condition that: second player is computer
void
ContinueGameWithComputer(int x1, int y1, int x2, int y2, int countwall1, int countwall2, char name[], int LengthName,
                         int count,int countblock1, int countblock2) {
    char enter[5];
    char commandstr[100];
    int xwall1, ywall1;
    char typewall1;
    int CommandComputer;
    char typewall2;
    char CommandSave[50];
    int sww1, sww2;

    // show each player's piece
    printf("Dear %s ,your piece is : %c\n", name, pieces1);
    printf("computer piece is : %c\n", pieces2);
    // turning the board into  a graph
    int nodes = count * count;
    InitialVisited(nodes);
    DeclareNodeName(count);
    PrintBoard(count);
    clock_t goal = 2500 + clock();
    while (goal > clock());
    while (1) {
        // Asking about the next move of computer
        if(countblock2==0)
            sww2 = 1;
        else {
            sww2 = 0;
            countblock2--;
        }
        while (sww2 == 1) {
            if (countwall2 == 0)
                CommandComputer = 1;
            else {
                srand(time(NULL));
                CommandComputer = rand() % 2 + 1;
            }

            // if command is moving the piece
            if (CommandComputer == 1) {
                if (CheckCompMove(x2, y2, count) == 1) {
                    board[x2][y2] = space;
                    x2 = x2 - 2;
                    board[x2][y2] = pieces2;
                    sww2 = 0;
                } else if (CheckCompMove(x2, y2, count) == 2) {
                    board[x2][y2] = space;
                    y2 = y2 + 5;
                    board[x2][y2] = pieces2;
                    sww2 = 0;
                } else if (CheckCompMove(x2, y2, count) == 3) {
                    board[x2][y2] = space;
                    x2 = x2 + 2;
                    board[x2][y2] = pieces2;
                    sww2 = 0;
                } else {
                    board[x2][y2] = space;
                    y2 = y2 - 5;
                    board[x2][y2] = pieces2;
                    sww2 = 0;
                }
            }

            // if command is building the wall
            if (CommandComputer == 2) {
                srand(time(NULL));
                typewall2 = rand() % 2 + 1;
                // typewall2=1 means Vertical, typewall2=2 means Horizontal
                if (typewall2 == 1) {
                    if (CheckCompWallVertical(count, nodes, x1, y1, x2, y2) == 1) {
                        sww2 = 0;
                        countwall2--;
                    }
                }
                if (typewall2 == 2) {
                    if (CheckCompWallHorizontal(count, nodes, x1, y1, x2, y2) == 1) {
                        sww2 = 0;
                        countwall2--;
                    }
                }
            }
            //opening a random gift or curse box
            if(sww2==0 && x2 != 1){
                CurseOrGift(x1,x2,y1,y2,count,nodes,&countblock2,&countwall2,&countwall1);
            }
        }
        if (x2 == 1) {
            printf(" **Computer** won");
            break;
        }
        system("cls");
        PrintBoard(count);
        if(countblock1==0)
            sww1 = 1;
        else {
            sww1 = 0;
            countblock1--;
        }
        while (sww1 == 1) {
            // Asking about the next move of player
            printf("Dear %s ,do you want to move your piece(1) or do you want to build a wall(2) ?\n", name);
            gets(commandstr);

            // if command is moving the piece
            if (commandstr[0] == '1' && commandstr[1] == 0) {
                int xtemp1 = x1;
                int ytemp1 = y1;
                printf("Enter the x and y component with the format: <x y> ;pay attention that we count from from zero!\n");
                scanf("%d %d", &x1, &y1);
                gets(enter);
                if (CheckMove(x1, y1, xtemp1, ytemp1, count) == 1) {
                    board[xtemp1][ytemp1] = space;
                    board[2 * x1 + 1][5 * y1 + 3] = pieces1;
                    x1 = 2 * x1 + 1;
                    y1 = 5 * y1 + 3;
                    sww1 = 0;
                } else {
                    x1 = xtemp1;
                    y1 = ytemp1;
                }
            }
                //if command is building the wall
            else if (commandstr[0] == '2' && commandstr[1] == 0) {
                printf("Enter the x and y of the starting point of the wall and enter the type of wall(H or V) with the format: <x y type> ; pay attention that we start counting from zero !\n");
                scanf("%d %d %c", &xwall1, &ywall1, &typewall1);
                gets(enter);
                if (typewall1 != 'V' && typewall1 != 'H') {
                    printf("incorrect input, please try Again !\n");
                }

                    // Let's check if there is a wall left
                else if (countwall1 == 0) {
                    printf("YOU ARE OUT OF WALL!\n");
                } else {
                    // check that if it is logically possible to build a wall there or not
                    if (CommandWall(nodes, xwall1, ywall1, typewall1, x1, y1, x2, y2, count) == 1) {
                        sww1 = 0;
                        countwall1--;
                    }

                }
            }
                //if user input was not one of our options:
            else {
                printf("incorrect input, please try Again !\n");
            }
            if(sww1==0)
                system("cls");
            //opening a random gift or curse box
            if(sww1==0 && x1 != 2 * count - 1){
                CurseOrGift(x1,x2,y1,y2,count,nodes,&countblock1,&countwall1,&countwall2);
            }
            if(sww1==0){
                PrintBoard(count);
                //asking if the player wants to save the game
                while (1) {
                    printf("do you want to save the game (1) or do you want to continue (2)? \n");
                    gets(CommandSave);
                    if (strcmp(CommandSave, "1") == 0) {
                        SaveGameComputer(x1, y1, x2, y2, countwall1, countwall2, name, 40, count, countblock1, countblock2);
                        break;
                    } else if (strcmp(CommandSave, "2") == 0) {
                        break;
                    } else {
                        printf("your input is not one of our options!please try again\n");
                    }
                }
            }
        }
        if (x1 == 2 * count - 1) {
            printf(" **%s** you won", name);
            break;
        }
        system("cls");
        PrintBoard(count);
    }
}


 int main() {
    //asking if user wants to play new game or continue the saved one
    while (1) {
        printf("Do you want to play a new game(1) or continue the saved one(2) ?\n");
        gets(LoadCommand);
        if (strcmp(LoadCommand, "1") == 0) {
            // making the board
            printf("Please enter the dimension of board :\n");
            scanf("%d", &count);
            gets(enter);
            screen(count);
            // asking if the player wants to play with a computer or a friend
            while (1) {
                printf("Would you like to play with the computer or a friend?\n");
                gets(TypePlayer);
                if (strcmp(TypePlayer, "friend") == 0) {
                    // Asking the number of walls allowed for each player and the name of each player
                    printf("How many walls are allowed for player1 ?\n");
                    scanf("%d", &countwall1);
                    printf("How many walls are allowed for player2 ?\n");
                    scanf("%d", &countwall2);
                    printf("What is the name of player1 ?\n");
                    gets(enter);
                    gets(name1);
                    printf("What is the name of player2 ?\n");
                    gets(name2);
                    system("cls");
                    // use a function to continue the game and announce the winner
                    HumanPlayer(count, name1, 40, name2, 40, countwall1, countwall2);
                    return 0;
                } else if (strcmp(TypePlayer, "computer") == 0) {
                    // asking the number of walls allowed for player and the computer
                    printf("How many walls are allowed for human ?\n");
                    scanf("%d", &countwall1);
                    printf("How many walls are allowed for computer ?\n");
                    scanf("%d", &countwall2);
                    printf("What is the name of human ?\n");
                    gets(enter);
                    gets(name);
                    system("cls");
                    //use function to continue the game and announce the winner
                    ComputerPlayer(count, name, 40, countwall1, countwall2);
                    return 0;
                } else {
                    printf("incorrect input!\n");
                }
            }

        } else if (strcmp(LoadCommand, "2") == 0) {
            printf("please enter the name of your game:\n");
            gets(Query);
            int i;
            if (LoadGameFile(Query) == 1) {
                fread(&PlayerType, sizeof(int), 1, inFile);
                if (PlayerType == 1) {
                    //It means that second player was computer
                    LoadGameConditionWithComputer(&x1, &y1, &x2, &y2, &countwall1, &countwall2, name, &count, &countblock1, &countblock2);
                    if (x1 == 2 * count - 1 || x2 == 1) {
                        printf("This game has been finished,please choose another one!\n");
                    } else {
                        ContinueGameWithComputer(x1, y1, x2, y2, countwall1, countwall2, name, 40, count, countblock1, countblock2);
                        return 0;
                    }
                    // if PlayerType==2
                } else {
                    //It means that second player was human
                    LoadGameConditionWithHuman(&x1, &y1, &x2, &y2, &countwall1, &countwall2, name1, name2, &count,
                                               &PlayerTurn, &countblock1, &countblock2);
                    if (x1 == 2 * count - 1 || x2 == 1) {
                        printf("This game has been finished,please choose another one!\n");
                    } else {
                        if (PlayerTurn == 1) {
                            ContinueGameWithHumanFirst(x1, y1, x2, y2, countwall1, countwall2, name1, 40, name2, 40,
                                                       count, countblock1, countblock2);
                            return 0;
                        } else {
                            // if PlayerTurn==2
                            ContinueGameWithHumanSecond(x1, y1, x2, y2, countwall1, countwall2, name1, 40, name2, 40,
                                                        count, countblock1, countblock2);
                            return 0;
                        }
                    }
                }
            }
        } else {
            printf("your input is not one of options!\n");
        }
    }

}
