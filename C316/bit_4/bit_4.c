#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int shift;
    int mask;
    char * name[4];
}Priznak;

int main()
{
    Priznak human [] = {
        {0, 1, {"fe", "ma"} },
        {1, 1, {"du", "cl"} },
        {2, 1, {"nh", "ha"} },
        {3, 1, {"sk", "tr"} },
        {4, 3, {"bn", "rd", "bw", "bk"} },
        {6, 3, {"bu", "ge", "gy", "da"} }
    };
    
    unsigned int a, b;
    
    scanf("%x", &a);
    //printf("Num: %x\n", n);
    
    for(int i = 0; i < 6; i++)
    {
        b = (a >> (human[i]).shift) & (human[i]).mask;
        printf("%s ", (human[i]).name[b]);
    }
    printf("\n");
    
    return 0;
}
