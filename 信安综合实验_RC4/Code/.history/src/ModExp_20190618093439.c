#include <stdio.h>
#include <math.h>

int modExp(int a, int e, int m)
{
    int r = 1;
    while (e != 0)
    {
        if (e % 2 == 1)
        {
            r = (r * a) % m;
        }
        a = (a * a) % m;
        e = e / 2;
    }
    return r;
}

int main(int argc, char const *argv[])
{
    int i = modExp(5, 117, 19);
    printf("%d", i);
    return 0;
}
