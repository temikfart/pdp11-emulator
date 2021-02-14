#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100
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
void st_destroy(Stack * s)
{
    if(s != NULL)
    {
        free(s->a);
        free(s);
    }
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
int symb_check(char c)
{
	//Проверка на цифру
	const char * dig = "0123456789";
	for(size_t i = 0; i < strlen(dig); i++)
	{
		if(c == dig[i])
		{
			printf("Digit: %d; ", c-'0');
			return c-'0';
		}
	}
	//Проверка на операцию
    const char * oper = "+-*=";
	for(size_t i = 0; i < strlen(oper); i++)
	{
		if(c == oper[i])
		{
			printf("Operand: %c; ", c);
			return c;
		}
	}
	//Проверка на пробел
	if(c == ' ')
	{
		printf("Space: <%c>; ", c);
		return -1;
	}
	return -100;
}

int main()
{
	char * str;
	str = malloc(N * sizeof(char));
	
	size_t length = N;
	unsigned int len = getline(&str, &length, stdin);
	
	printf("\nlen: %d\n", len);
	printf("len(str): %ld\n", strlen(str));
	printf("str: %s\n", str);
	
	
	Stack * st;
	st = malloc(sizeof(Stack));
	st_init(st);
	
	int pos = def_eq_size(str, len);
	printf("pos: %d\n", pos);
	
	
	for(int i=0; i<=pos; i++)
	{
		printf("%d: ", i);
		int temp = symb_check(str[i]);
		printf("temp: %d\n", temp);
	}
	
	free(str);
	st_destroy(st);
	
	return 0;
}