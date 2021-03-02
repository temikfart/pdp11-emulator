#include <stdio.h>
#include <stdlib.h>

void det_sex(unsigned int n)
{
    // ma = ???? ???1; fe = ???? ???0
    if(n & 1)
        printf("ma ");
    else
        printf("fe ");
}
void det_brain(unsigned int n)
{
    if((n >> 1) & 1)
        printf("cl ");
    else
        printf("du ");
}
void det_hat(unsigned int n)
{
    if((n >> 2) & 1)
        printf("ha ");
    else
        printf("nh ");
}
void det_bottom(unsigned int n)
{
    if((n >> 3) & 1)
        printf("tr ");
    else
        printf("sk ");
}
void det_hair_col(unsigned int n)
{
    if(((n >> 4) & 3) == 3) //???? ??11
        printf("bk ");
    else if(((n >> 4) & 1) == 1) //???? ??01
        printf("rd ");
    else if(((n >> 4) & 2) == 2) //???? ??10
        printf("bw ");
    else
        printf("bn "); //???? ??00
}
void det_eyes_col(unsigned int n)
{
    if(((n >> 6) & 3) == 3) //???? ??11
        printf("da ");
    else if(((n >> 6) & 1) == 1) //???? ??01
        printf("ge ");
    else if(((n >> 6) & 2) == 2) //???? ??10
        printf("gy ");
    else
        printf("bu "); //???? ??00
}

int main()
{
    unsigned int n;
    
    scanf("%x", &n);
    //printf("Num: %x\n", n);
    
    det_sex(n);
    det_brain(n);
    det_hat(n);
    det_bottom(n);
    det_hair_col(n);
    det_eyes_col(n);
    
    printf("\n");
    
    return 0;
}
