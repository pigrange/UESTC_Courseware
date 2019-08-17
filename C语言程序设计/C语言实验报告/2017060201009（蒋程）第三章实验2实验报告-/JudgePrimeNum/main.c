#include<stdio.h>
#include<math.h>

int isPrimeNum(int);

int main(void) {
    int num;
    /*第一步判断：如果输入的不为整数且输入的整数小于等于三的话，输出"error"*/
    if ((scanf("%d", &num) != 1) || num <= 3) {
        printf("error");

        /*将输入的num丢进函数isPrimeNum()，如果是素数，则返回1。*/

    } else if (isPrimeNum(num) != 1) {
        printf("no");

    } else {
        printf("yes");
    }

    return 0;
}

/**
 * 判断是否是素数的主体函数，主要算法实现：2至比num的平方根小的最大整数均不能整除num，
 * 那么num即为素数，此时函数的返回值就是1，否则返回0。
 * */
int isPrimeNum(int num) {

    if (num == 4) {
        return 0;
    }
    double num_1 = sqrt((float) num);

    for (int count = 2; count < num_1; count++) {
        if (num % count == 0) {
            return 0;
        } else {
            continue;
        }
    }
    return 1;
}
