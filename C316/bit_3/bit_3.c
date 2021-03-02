#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned int n;
    
    scanf("%x", &n);
    //printf("Num: %x\n", n);
    
    if(((n >> 4) & 3) == 3) //???? ??11
        printf("bk\n");
    else if(((n >> 4) & 1) == 1) //???? ??01
        printf("rd\n");
    else if(((n >> 4) & 2) == 2) //???? ??10
        printf("bw\n");
    else
        printf("bn\n"); //???? ??00
    
    return 0;
}
