#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned int n;
    
    scanf("%x", &n);
    //printf("Num: %x\n", n);
    
    //if(n & 4)
    if(n >> 2)
        printf("ha\n");
    else
        printf("nh\n");
    
    return 0;
}
