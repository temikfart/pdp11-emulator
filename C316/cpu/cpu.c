#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define A 5
#define B 6
#define C 7
#define D 8

void IR(int *reg);
int ADD(int x, int y);
int SUB(int x, int y);
int MOV(int x, int y);

#define N 1000

int main()
{
    int reg[4];
    for(int k = 0; k<4; k++)
    {
        reg[k] = 0;
    }
    //IR(reg);
    
    //Считывание команд из одной строки: 1 строка - много команд.
    char * descr = NULL;
    size_t lend;
    
    if(getline(&descr, &lend, stdin) == -1)
    {
        //printf("Nothing\n");
        return 0;
    }
    
    int i = 0;
    char * str[N];
    
    const char * delim = " \n\t\r";
    for (char * p = strtok(descr, delim);
            p != NULL;
            p = strtok(NULL, delim))
    {
        /* if(size_temp <= i)
        {
            size_temp += 10;
            temp = (char *)realloc(temp, size_temp*sizeof(char));
        } */
        str[i] = p;
        //printf("%s ", str[i]);
        i++;
    }
    //printf("\n");
    
    int temp[N];
    for(int k = 0; k < i; k++)
    {
        if(strlen(str[k]) == 1)
        {
            temp[k] = str[k][0] - '0';
            //printf("Один символ: %d\n", temp[k]);
        }
        else
        {
            int pow = 1;
            temp[k] = 0;
            //printf("Несколько символов: %s (len: %ld)\n", str[k], strlen(str[k]));
            for(size_t q = 0; q < strlen(str[k]); q++)
            {
                temp[k] += pow * (str[k][strlen(str[k]) - q - 1] - '0');
                pow *= 10;
                //printf("temp: %d; str: %d\n", temp[k], str[k][strlen(str[k]) - q - 1]);
            }
        }
    }
    
    /* for(int k = 0; k < i; k++)
        printf("%d ", temp[k]);
    printf("\n"); */
    
    int j = 0;
    while(j != i)
    {
        
        if(temp[j] == 0)
        {
            //printf("HLT\n");
            //IR(reg);
            break;
        }
        else if(temp[j] == 3)
        {
            int x = temp[j+1] - A;
            int y = temp[j+2];
            //printf("MOV: x=%d; y=%d;\n", x, y);
            reg[x] = MOV(reg[x], y);
            //printf("MOV: reg[x]=%d; y=%d;\n", reg[x], y);
            //IR(reg);
            j += 3;
        }
        else if(temp[j] == 1)
        {
            int x1 = temp[j+1] - A;
            int x2 = temp[j+2] - A;
            reg[x1] = ADD(reg[x1], reg[x2]);
            //printf("ADD: reg[x1]=%d; reg[x2]=%d;\n", reg[x1], reg[x2]);
            //IR(reg);
            j += 3;
        }
        else if(temp[j] == 2)
        {
            int x1 = temp[j+1] - A;
            int x2 = temp[j+2] - A;
            reg[x1] = SUB(reg[x1], reg[x2]);
            //printf("SUB: reg[x1]=%d; reg[x2]=%d;\n", reg[x1], reg[x2]);
            //IR(reg);
            j += 3;
        }
        else if(temp[j] == 4)
        {
            IR(reg);
            j++;
        }
    }
    
    //printf("Final\n");
    free(descr);
    //free(temp);
    
    
    
    
    
    
    
    //Считывание команд построчно: 1 строка = 1 команда
    /* while(1)
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
            //printf("HLT\n");
            //IR(reg);
            free(descr);
            break;
        }
        else if(strcmp(temp[0], "3") == 0)
        {
            int x = *temp[1] - '0' - A;
            char y = *temp[2] - '0';
            reg[x] = MOV(reg[x], y);
            //printf("MOV: x=%d; y=%d;\n", reg[x], y);
            //IR(reg);
        }
        else if(strcmp(temp[0], "1") == 0)
        {
            int x1 = *temp[1] - '0' - A;
            int x2 = *temp[2] - '0' - A;
            reg[x1] = ADD(reg[x1], reg[x2]);
            //printf("ADD: reg[x1]=%d; reg[x2]=%d;\n", reg[x1], reg[x2]);
            //IR(reg);
        }
        else if(strcmp(temp[0], "2") == 0)
        {
            int x1 = *temp[1] - '0' - A;
            int x2 = *temp[2] - '0' - A;
            reg[x1] = SUB(reg[x1], reg[x2]);
            //printf("SUB: reg[x1]=%d; reg[x2]=%d;\n", reg[x1], reg[x2]);
            //IR(reg);
        }
        else if(strcmp(temp[0], "4") == 0)
        {
            IR(reg);
        }
        
        free(descr);
    } */
    
    return 0;
}

void IR(int *reg)
{
    for(int q = 0; q < 4; q++)
        printf("%d ", reg[q]);
    printf("\n");
}
int ADD(int x, int y)
{
    x += y;
    if(x > 128)
        return (x % 128);
    else
        return x;
}
int SUB(int x, int y)
{
    x -= y;
    if(x > 128)
        return (x % 128);
    else
        return x;
}
int MOV(int x, int y)
{
    x += y;
    if(x > 128)
        return (x % 128);
    else
        return x;
}
