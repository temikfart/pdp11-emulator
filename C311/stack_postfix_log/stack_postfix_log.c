#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

typedef int Data;
typedef struct
{
    unsigned int n;
    size_t size;
    Data * a;
} Stack;

void st_init(Stack * s)
{
    s->a = NULL;
    s->n = 0;
    s->size = 0;
}
void st_destroy(Stack * s)
{
    if(s != NULL)
    {
        free(s->a);
        free(s);
    }
}
int st_is_empty(Stack * s)
{
    return s->n == 0;
}
int st_is_full(Stack * s)
{
    return s->n == s->size;
}
void st_push(Stack * s, Data x)
{
    if(st_is_full(s))
    {
        s->size += 10;
        s->a = realloc(s->a, s->size * sizeof(Data));
    }
    s->a[s->n] = x;
    s->n ++;
}
void st_print(Stack * s)
{
    if(st_is_empty(s) == 1)
        printf("Empty stack\n");
    else
    {
        for(unsigned int i = 0; i < s->n; i++)
            printf("%d ", s->a[i]);
        printf("\n");
    }
}
Data st_pop(Stack * s)
{
    if(st_is_empty(s))
        return 0;
    Data x = s->a[s->n - 1];
    s->n --;
    return x;
}
int symb_check(char c) //1 - цифра, 2 - +-*=, 0 - мусор
{
    //Проверка на цифру
    if(c == '0' || c == '1')
    {
        //printf("<Digit: %d>\n", c-'0');            
        return 1;
    }
    //Проверка на операцию или пробел
    const char * oper = "!|&=";
    for(size_t i = 0; i < strlen(oper); i++)
    {
        if(c == oper[i])
        {
            //printf("Operator: %c; ", c);
            return 2;
        }
    }
    return 0;
}
int oper_check(char c)
{
    //printf("c: %d; =: %d; !: %d; |: %d; &: %d>\n", c, '=', '!', '|', '&');
    if(c == '=')
    {
        //printf("Это =\n");
        return 1;
    }
    if(c == '!')
    {
        //printf("Это !(NO)\n");
        return 2;
    }
    if(c == '|')
    {
        //printf("Это |(OR)\n");
        return 3;
    }
    if(c == '&')
    {
        //printf("Это &(AND)\n");
        return 4;
    }
    return -1;
}

int main()
{
    char * str;
    str = malloc(N * sizeof(char));
    
    size_t length = N;
    getline(&str, &length, stdin);
    
    Stack * st;
    st = malloc(sizeof(Stack));
    st_init(st);
    
    for(size_t i = 0; i <= strlen(str); i++)
    {
        int x, y;
        if(symb_check(str[i]) == 1) //Если цифра - кладем в стек
        {
            //printf("<Это цифра!>\n");
            int res = str[i] - '0';
            st_push(st, res);
            //st_print(st);
        }
        else if(symb_check(str[i]) == 2) //Если лог. оператор - выполняем действие
        {
            //printf("<Это логический оператор!>\n");
            int temp_oper = oper_check(str[i]);
            //printf("Оператор №%d обнаружен.\n", temp_oper);
            if(temp_oper == 1)
            {
                //printf("\nres: ");
                st_print(st);
                break;
            }
            else if(temp_oper == 2)
            {
                x = st_pop(st);
                x = !x;
                st_push(st, x);
                //st_print(st);
                //printf("(+)\n");
            }
            else if(temp_oper == 3)
            {
                x = st_pop(st);
                y = st_pop(st);
                x = !!(x + y);
                st_push(st, x);
                //st_print(st);
                //printf("(-)\n");
            }
            else if(temp_oper == 4)
            {
                x = st_pop(st);
                y = st_pop(st);
                st_push(st, ((x + y == 2) ? 1 : 0));
                //st_print(st);
                //printf("(*)\n"); 
            }
            else
            {
                printf("\n<ОШИБКА ВЫБОРА ЛОГИЧЕСКОГО ОПЕРАТОРА>\n");
                break;
            }    
        }
        else if(symb_check(str[i]) == 0) //Если мусор то ошибка
        {
            printf("\n<Неправильная запись выражения>\n");
        }
    }
    
    free(str);
    st_destroy(st);
    
    return 0;
}