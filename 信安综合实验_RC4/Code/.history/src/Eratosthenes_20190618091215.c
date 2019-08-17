#include <stdio.h>
#include <math.h>

int eratosthenes(int a)
{
    int j, m = sqrt(a);
    int *set = (int *)malloc(sizeof(int) * (m + 1));
    for (int i = 2; i <= m; i++)
    {
        set[i] = 1;
    }
    for (int i = 2; i <= m; i++)
    {
        //没有必要再做一次sqrt
        j = i * i;
        while (j <= m)
        {
            set[j] = 0;
            j += i;
        }
    }
    //让a把所有的非0的全模一次
    for (int i = 2; i <= m; i++)
    {
        if (set[i] != 0 && a % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char const *argv[])
{
    int nums[100];
    for (int i = 2; i < 100; i++)
    {
        if (eratosthenes(i) == 1)
        {
            printf("%d ,", i);
        }
    }

    return 0;
}
