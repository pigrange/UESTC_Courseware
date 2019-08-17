//
// Created by johnpig on 2018/4/19.
//
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<windows.h>

void mainFunction();

void onEnterClicked(int y);

void gotoXY(int x, int y);

void setDifficulty();


int difficulty = 1;
char *difficulties[] = {"Easy", "Normal", "Hard"};


void mainFunction() {
    int flag = 1;
    int y = 6;
    char ch;

    while (flag) {
        system("cls");
        printf("GameDifficulty:%s", difficulties[difficulty]);
        printf("\n\n\n\n\n");
        printf("              GameStart\n\n");
        printf("              SettingKey\n\n");
        printf("              SetDifficulty\n\n");
        printf("              GameProducer\n\n");
        printf("              Quit\n\n");
        gotoXY(10, y);
        printf("%c%c", 16, 16);


        ch = (char) getch();
        switch (ch) {
            case 'w':
                if (y > 6) {
                    y = y - 2;
                    gotoXY(10, y);
                    printf("%c%c", 16, 16);
                }
                break;
            case 's':
                if (y < 13) {
                    y = y + 2;
                    gotoXY(10, y);
                    printf("%c%c", 16, 16);
                }
                break;
            case '\r':
                flag = 0;
                onEnterClicked(y);
                break;
            default:
                break;
        }
        if (flag)system("cls");
    }
};

void gotoXY(int x, int y) {
    COORD c;
    c.X = (SHORT) (x - 1);
    c.Y = (SHORT) (y - 1);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void setDifficulty() {
    int y = 6, flag = 1;
    char ch;
    while (flag) {
        printf("currentDifficulty:%s", difficulties[difficulty]);
        printf("\n\n\n\n\n");
        printf("              Easy\n\n");
        printf("              Normal\n\n");
        printf("              Hard\n\n");
        gotoXY(10, y);
        printf("%c%c", 16, 16);

        ch = (char) getch();
        switch (ch) {
            case 'w':
                if (y > 6) {
                    y = y - 2;
                    gotoXY(10, y);
                    printf("%c%c", 16, 16);
                }
                break;
            case 's':
                if (y < 9) {
                    y = y + 2;
                    gotoXY(10, y);
                    printf("%c%c", 16, 16);
                }
                break;
            case '\r':
                if (y == 6) {
                    difficulty = 0;
                    flag = 0;
                    system("cls");
                    mainFunction();
                } else if (y == 8) {
                    difficulty = 1;
                    flag = 0;
                    system("cls");
                    mainFunction();
                } else if (y == 10) {
                    difficulty = 2;
                    flag = 0;
                    system("cls");
                    mainFunction();
                }
                break;
            default:
                break;
        }
        if (flag)system("cls");
    }
}

void onEnterClicked(int y) {
    system("cls");
    switch (y) {

        case 6:
            //toStartGame
            break;
        case 8:
            //toSetButton
            break;
        case 10:
            setDifficulty();
            break;
        case 12:
            //showGameCreator
            break;
        case 14:
            exit(0);

        default:
            break;
    }
};
