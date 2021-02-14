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
int def_eq_size(char * str, unsigned int len)
{
    int pos = -1;
    int eq = '=';
    
    if(strchr(str, eq) != NULL)
    {
        //printf("%s\n", strchr(str, eq));
        //printf("%ld\n", strlen(strchr(str, eq)));
        pos = len - strlen(strchr(str, eq));
        //printf("%d\n", pos);
        return pos;
    }
    return -1;
}
int symb_check(char c) //1 - цифра, 2 - +-*=, 0 - мусор
{
    //Проверка на цифру
    const char * dig = "0123456789";
    for(size_t i = 0; i < strlen(dig); i++)
    {
        if(c == dig[i])
        {
            //printf("<Digit: %d; >", c-'0');            
            return 1;
        }
    }
    //Проверка на операцию или пробел
    const char * oper = "+-*=";
    for(size_t i = 0; i < strlen(oper); i++)
    {
        if(c == oper[i])
        {
            //printf("Operand: %c; ", c);
            return 2;
        }
    }
    /* //Проверка на пробел
    if(c == ' ')
    {
        //printf("Space: <%c>; ", c);
        return ' ';
    } */
    return 0;
}
int oper_check(char c)
{
    //printf("%d %d %d\n", c, '+', '=');
    if(c == '=')
    {
        //printf("Это =\n");
        return 1;
    }
    if(c == '+')
    {
        //printf("Это +\n");
        return 2;
    }
    if(c == '-')
    {
        //printf("Это -\n");
        return 3;
    }
    if(c == '*')
    {
        //printf("Это *\n");
        return 4;
    }
    return -1;
}

int main()
{
    char * str;
    str = malloc(N * sizeof(char));
    
    size_t length = N;
    unsigned int len = getline(&str, &length, stdin);
    
    //printf("\nlen: %d\n", len);
    //printf("len(str): %ld\n", strlen(str));
    //printf("str: %s\n", str);
    
    
    int pos = def_eq_size(str, len); 
    //printf("pos: %d\n", pos);
    
    /*
    Примерно на этапе: "Я закончил" Я понял,
    что эта функция def_eq_size не нужна, т.к.
    for может закончиться с помощью break, сразу
    после первого "=".
    */
    
    
    Stack * st;
    st = malloc(sizeof(Stack));
    st_init(st);
    
    for(int i = 0; i <= pos; i++)
    {
        int x, y;
        if(symb_check(str[i]) == 1) //Если цифра кладем в стек число
        {
            //printf("<Это цифра или число!>\n");
            int c = i;
            int res = str[i] - '0';
            while(symb_check(str[c+1]) == 1) //Создание числа
            {
                res *= 10;
                res += str[c+1] - '0';
                c++;
                //printf("<Найдена еще одна цифра>\n");
            }
            st_push(st, res);
            //st_print(st);
            i = c;
        }
        else if(symb_check(str[i]) == 2) //Если оператор - выполняем действие
        {
            //printf("<Это оператор!>\n");
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
                y = st_pop(st);
                st_push(st, x+y);
                //st_print(st);
                //printf("(+)\n");
            }
            else if(temp_oper == 3)
            {
                x = st_pop(st);
                y = st_pop(st);
                st_push(st, y-x);
                //st_print(st);
                //printf("(-)\n");
            }
            else if(temp_oper == 4)
            {
                x = st_pop(st);
                y = st_pop(st);
                st_push(st, x*y);
                //st_print(st);
                //printf("(*)\n"); 
            }
            else
            {
                printf("\n<ОШИБКА ВЫБОРА ОПЕРАТОРА>\n");
                break;
            }    
        }
        else if(symb_check(str[i]) == 0 && str[i] != ' ') //Если мусор то ошибка
        {
            printf("\n<Неправильная запись выражения>\n");
        }
    }
    
    free(str);
    st_destroy(st);
    
    return 0;
}