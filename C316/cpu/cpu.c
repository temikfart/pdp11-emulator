#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ADD (char x, char y);
char SUB (char x, char y);
char MOV (char x, char y);
void IR();

int main()
{
    char A, B, C, D;
    A = B = C = D = 0;
    
    printf("%d %d %d %d\n", A, B, C, D);
    
    
    char * descr = NULL;
    size_t lend;
    
    if(getline(&descr, &lend, stdin) == -1)
    {
        printf("Nothing\n");
        return 0;
    }
    
    
    const char * delim = " \n\t\r";
    for (char * p = strtok(descr, delim);
            p != NULL;
            p = strtok(NULL, delim))
    {
        if(strcmp(p, "0") == 0)
        {
            printf("HLT\n");
            break;
        }
        //else if(strcmp(p, "1")
    }

    free(descr);
    
    return 0;
}
