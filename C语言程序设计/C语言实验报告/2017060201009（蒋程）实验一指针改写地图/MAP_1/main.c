#include <stdio.h>
#include <malloc.h>

#define ROW 20
#define COL 70

#define BOX(x, y) (*(map + (y) * ROW + (x)))

int main() {

    char *map = (char *) malloc(sizeof(char) * ROW * COL);
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            BOX(i, j) = 'x';
        }
    }
    for (int i = 1; i < ROW -1; i++) {
        for (int j = 1; j < COL -1; j++) {
            BOX(i, j) = ' ';
        }
    }

    for (int i = 3; i < 5; i++) {
        for (int j = 8; j < 16; j++) {
            BOX(i,j) = '#';
        }
    }
    BOX(5,11) = '@';

    for (int i = 13; i < 15; i++) {
        for (int j = 8; j < 16; j++) {
            BOX(i,j) = '#';
        }
    }
    BOX(15,11) = '$';

    for (int i = 3; i < 5; i++) {
        for (int j = 56; j < 64; j++) {
            BOX(i,j) = '#';
        }
    }
    BOX(5,59) = '!';

    for (int i = 13; i < 15; i++) {
        for (int j = 56; j < 64; j++) {
            BOX(i,j) = '#';
        }
    }
    BOX(15,59) = '&';

    for (int i = 8; i < 11; i++) {
        for (int j = 33; j < 36; j++) {
            BOX(i,j) = '*';
        }
    }
    BOX(9,34) = ' ';
    BOX(10,69) = ' ';

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            printf("%c", BOX(i, j));
        }
        printf("\n");
    }
}




