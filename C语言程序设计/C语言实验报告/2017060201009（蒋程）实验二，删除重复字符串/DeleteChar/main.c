#include <stdio.h>
#include <stdlib.h>

int main() {
    int i,j,k;
    char str1[51];
    char str2[51];
    gets(str1);

    for (i = 0,k = 0; str1[i]!='\0';) {
        if((str1[i] == str1[i+1])&& !('A'<=str1[i]&&str1[i]<='z')&&!('0'<=str1[i]&&str1[i]<='9')){
            j = 1;
            while(str1[i] == str1[i+j]){
                j++;
            }
            i = i+j-1;
            str2[k] = str1[i];
        } else{
            str2[k] = str1[i];
        }
        i++;
        k++;
    }

    str2[k] = '\0';
    puts(str2);
    return 0;
}
