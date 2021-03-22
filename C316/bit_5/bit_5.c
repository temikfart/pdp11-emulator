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
    
    printf("line: %sSize: %ld\nLen: %ld\n", descr, lend, strlen(descr));
    
    const char * delim = " \n\t\r";    // алфавит разделителей
    
    //характеристики
    //будем хранить характеристики в массиве строк
    char *sex[] = {"fe", "ma"};
    //char *brain[] = {"cl", "du"};
    //char *hat[] = {"ha", "nh"};
    //char *bottom[] = {"tr", "sk"};
    //char *hair_col[] = {"bn", "rd", "bw", "bk"};
    //char *eyes_col[] = {"bu", "ge", "gy", "da"};
    //printf("%s %s %s %s\n", sex[0], hat[2], eyes_col[3], bottom[0]);
    
    
    //Будем заполнять описание в массиве
    char *temp[6];
    for(int i = 0; i<6; i++)
    {
        temp[i] = 0;
    }
    printf("Size of temp: %ld\n\n", sizeof(temp));
    
    unsigned int n = 0;
    
    for (char * p = strtok(descr, delim);   // начинаем разбор, передаем строку s 
            p != NULL;                  // пока не нашли новый разделитель
            p = strtok(NULL, delim))  // в следующий раз вызываем от NULL
    {
        //printf("%s: ", p);
        
        //Проверка на характеристику: ma/fe
        //if(strcmp(p, "ma") == 0 || strcmp(p, "fe") == 0)
        if(temp[0] == 0 && (strcmp(p, sex[0]) == 0 || strcmp(p, sex[1]) == 0) ) //проверка на отсутствие описания по этому параметру
        {
            for(size_t i = 0; i < sizeof(sex)/sizeof(sex[0]); i++)
            {
                if(strcmp(p, sex[i]) == 0)
                {
                    strcat(temp[0], sex[i]);
                    n += i;
                    printf("%s\n%hhd\n", temp[0], n);
                }
            }
            printf("ma_fe\n");
        }
        else
        {
            printf("trash\n");
            break;
        }
    }
    
    free(descr);
    
    return 0;
}