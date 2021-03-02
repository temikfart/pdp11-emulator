#include <stdio.h>
#include <stdlib.h>

void det_sex(unsigned int n)
{
    // ma = ???? ???1; fe = ???? ???0
    if(n & 1)
        printf("ma\n");
    else
        printf("fe\n");
}
void det_brain(unsigned int n)
{
    if(n >> 1)
        printf("cl\n");
    else
        printf("du\n");
}
void det_hair(unsigned int n)
{
    //if(n & 4)
    if(n >> 2)
        printf("ha\n");
    else
        printf("nh\n");
}

int main()
{
    unsigned int n;
    
    scanf("%x", &n);
    //printf("Num: %x\n", n);
    
    det_sex(n);
    det_brain(n);
    det_hair(n);
    
    return 0;
}
