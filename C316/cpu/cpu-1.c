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
    //Создание массива регистров
    int reg[4];
    for(int k = 0; k<4; k++)
    {
        reg[k] = 0;
    }
    
    //Считывание команд из одной строки: 1 строка - много команд.
    //Разбираем его по токенам - числам.
    char * descr = NULL;
    size_t lend;
    
    //Если строка пуста - завершается программа
    if(getline(&descr, &lend, stdin) == -1)
    {
        return 0;
    }
    
    int i = 0;
    char * str[N];
    
    const char * delim = " \n\t\r";
    for (char * p = strtok(descr, delim);
            p != NULL;
            p = strtok(NULL, delim))
    {
        str[i] = p;
        i++;
    }
    
    
    //Если числа больше 1 символа, то надо строчки конвертировать в числа
    int temp[N];
    for(int k = 0; k < i; k++)
    {
        if(strlen(str[k]) == 1)
        {
            temp[k] = str[k][0] - '0';
        }
        else
        {
            int pow = 1;
            temp[k] = 0;
            for(size_t q = 0; q < strlen(str[k]); q++)
            {
                temp[k] += pow * (str[k][strlen(str[k]) - q - 1] - '0');
                pow *= 10;
            }
        }
    }
    
    //Распишем все случаи команд и их действия
    int j = 0;
    while(j != i)
    {
        int x = temp[j+1] - A;
        int y = temp[j+2] - A;
        
        switch(temp[j])
        {
            case 0:
                j = i - 3;
                break;
            case 1:
                reg[x] = ADD(reg[x], reg[y]);
                break;
            case 2:
                reg[x] = SUB(reg[x], reg[y]);
                break;
            case 3:
                y += A;
                reg[x] = MOV(reg[x], y);
                break;
            case 4:
                IR(reg);
                j -= 2;
                break;
        }
        j += 3;
    }
    
    free(descr);
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
