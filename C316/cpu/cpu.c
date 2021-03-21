#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define A 5
#define B 6
#define C 7
#define D 8

void print_reg();
char ADD (char x, char y);
char SUB (char x, char y);
char MOV (char x, char y);
void IR();

int main()
{
    char reg[4];
    for(int k = 0; k<4; k++)
    {
        reg[k] = 0;
    }
    print_reg(reg);
    
    while(1)
    {
        char * descr = NULL;
        size_t lend;
        
        if(getline(&descr, &lend, stdin) == -1)
        {
            printf("Nothing\n");
            return 0;
        }
    
        char *temp[3];
        int i = 0;
    
        const char * delim = " \n\t\r";
        for (char * p = strtok(descr, delim);
                p != NULL;
                p = strtok(NULL, delim))
        {
            temp[i] = p;
            i++;
        }
        if(strcmp(temp[0], "0") == 0)
        {
            printf("HLT\n");
            print_reg(reg);
            free(descr);
            break;
        }
        else if(strcmp(temp[0], "3") == 0)
        {
            int x = *temp[1] - '0' - A;
            char y = *temp[2] - '0';
            reg[x] = MOV(reg[x], y);
            printf("MOV: x=%d; y=%d;\n", reg[x], y);
            print_reg(reg);
        }
        free(descr);
    }
    
    return 0;
}

void print_reg(char *reg)
{
    for(int q = 0; q < 4; q++)
        printf("%d ", reg[q]);
    printf("\n");
}
char MOV (char x, char y)
{
    x += y;
    return x;
}
