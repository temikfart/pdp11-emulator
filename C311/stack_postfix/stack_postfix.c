#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10
#define S 48

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
        s->size += N;
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
void st_destroy(Stack * s)
{
    if(s != NULL)
    {
        free(s->a);
        free(s);
    }
}
int symb_check(const char * symb, Data temp)
{
    for(int i = 0; i < N; i++)
    {
        if(symb[i] == temp )
        {
            return i+1;
        }
    }
    return 0;
}
int st_oper(Data x, Data y, int op_num)
{
	Data res = -1000;
	switch(op_num)
	{
		case 1:
			res = x+y;
			printf("(+)\n");
			break;
		case 2:
			res = y-x;
			printf("(-)\n");
			break;
		case 3:
			res = x*y;
			printf("(*)\n");
			break;			
	}
	return res;
}

int main()
{
    const char * dig = "0123456789";
    const char * oper = "+-*=";

    Stack * st;
    st = malloc(sizeof(Stack));
    st_init(st);
    
    char temp;
	Data dig1, dig2;
	Data res;
	/*
	Пока идут данные
		если число
			положить в стек
		если операнд
			достать два числа из стека
				если в стеке 1 число то ошибка
			произвести операцию
			положить результат в стек
		если равно
			закончить цикл
			вывести результат
	*/
	
    while(scanf("%c", &temp) != EOF)
    {
        if(symb_check(dig, temp) != 0)
		{
			temp -= S;
			st_push(st, temp);
			st_print(st);
			//printf("dig: %c \n", temp);
		}
		if(symb_check(oper, temp) != 0)
		{
			printf("symb_check: %d\n", symb_check(oper, temp));
			if(symb_check(oper, temp) == 4)
			{
				printf("%d\n", st_pop(st));
				break;
			}
			if(st->n < 2)
			{
				printf("Error\n");
				break;
			}
			else
			{
				dig1 = st_pop(st);
				dig2 = st_pop(st);
				
				res = st_oper(dig1, dig2, symb_check(oper, temp));
				st_push(st, res);
				printf("res: %d\n", res);
				st_print(st);
			}
			
			printf("1: %d; 2: %d;\n", dig1, dig2);
		}
    }
    
    st_destroy(st);
    return 0;
}