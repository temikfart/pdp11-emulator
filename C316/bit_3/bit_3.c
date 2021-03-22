#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a, b;
    
    scanf("%x", &a);
    //printf("Num: %x\n", n);
    
    b = (a >> 4) & 3;
    switch(b)
    {
        case 0:
            printf("bn\n"); //???? ??00
            break;
        case 1:
            printf("rd\n"); //???? ??01
            break;
        case 2:
            printf("bw\n"); //???? ??10
            break;
        default:
            printf("bk\n"); //???? ??11
            break;
    }
    
    return 0;
}
