#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char * descr = NULL;
    size_t lend;
    
    if(getline(&descr, &lend, stdin) == -1)
    {
        printf("Nothing\n");
        return 0;
    }
    
    printf("line: %sLen: %ld\n", descr, lend);
    
    const char * delim = " \n\t\r";    // алфавит разделителей
    
    //характеристики
    char par_sex[2] = NULL; //будем хранить характеристики в массиве строк
    par_sex[0] = "fe";
    par_sex[1] = "ma";
    
    for (char * p = strtok(descr, delim);   // начинаем разбор, передаем строку s 
            p != NULL;                  // пока не нашли новый разделитель
            p = strtok(NULL, delim))  // в следующий раз вызываем от NULL
    {
        //printf("%s\n", p);
        
        //Проверка на характеристику: ma/fe
        //if(strcmp(p, "ma") == 0 || strcmp(p, "fe") == 0)
        if() //нужно в условии проверить на ma/fe
        {
            printf("ma_fe\n");
        }
        else
        {
            printf("trash\n");
            break;
        }
    }
    
    return 0;
}