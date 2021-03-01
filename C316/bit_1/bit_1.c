#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned int n;
    
    scanf("%x", &n);
    //printf("Num: %x\n", n);
    
    // ma = ???? ???1; fe = ???? ???0
    if(n & 1)
        printf("ma\n");
    else
        printf("fe\n");
    
    return 0;
}