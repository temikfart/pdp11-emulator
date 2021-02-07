#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10
#define Brackets 4

typedef char Data;
typedef struct
{
	unsigned int n;
	size_t size;
	Data * a;
}Stack;

void st_init(Stack * s)
{
	s->a = NULL;
	s->n = 0;
	s->size = 0;
};
int st_is_empty(Stack * s)
{
	return s->n == 0;
};
int st_is_full(Stack * s)
{
	return s->n == s->size;
};
void st_push(Stack * s, Data x)
{
	if(st_is_full(s))
	{
		s->size += N;
		s->a = realloc(s->a, s->size * sizeof(Data));
	}
	s->a[s->n] = x;
	s->n ++;
};
void st_print(Stack * s)
{
	if(st_is_empty(s) == 1)
		printf("Empty stack\n");
	else
	{
	for(unsigned int i = 0; i < s->n; i++)
		printf("%c ", s->a[i]);
	printf("\n");
	}
};
Data st_pop(Stack * s)
{
	if(st_is_empty(s))
		return -1;
	Data x = s->a[s->n - 1];
	s->n --;
	return x;
};
void st_destroy(Stack * s)
{
	if(s != NULL)
	{
		free(s->a);
		free(s);
	}
};
int br_comp(const char * br, const char * temp)
{
	int count = 0;
	for(int i = 0; i < Brackets; i++)
	{
		if(strcmp(br, temp))
		{
			count++;
			break;
		}
	}
	return (count != 0) ? 1 : 0;
};
/* Stack * stack_create(int size)
{
	struct Stack * s = malloc(sizeof(struct Stack));
	s->a = malloc(size * sizeof(Data));
	s->size = size;
	s->n = 0;
	return s;
};
Data stack_get(struct Stack * s)
{
	Data x = s->a[s->n - 1];
	return x;
};
int stack_size(struct Stack * s)
{
	
};
void stack_clear(struct Stack * s)
{
	free(s->a);
	s->n = 0;
}; */

int main()
{
	const char * begin = "([{<";
	const char * end = ")]}>";

	Stack * st;
	st = malloc(sizeof(Stack));
	st_init(st);
	
	
	/* printf("is empty: %d\n", st_is_empty(st)); 		//1
	st_print(st);									//empty stack
	st_push(st, '{');
	st_push(st, '>');
	printf("is empty: %d\n", st_is_empty(st));		//0

	st_print(st);									//{ >
	printf("%c\n", st_pop(st));						//>
	st_print(st);									//{
	
	printf("%c\n", st_pop(st));						//{
	st_print(st);									//Empty
	
	printf("%c %c %c\n", begin[0], begin[3], end[2]); //( < } */
	
	st_print(st);
	Data temp;
	while(scanf("%c", &temp) != EOF)
	{
		if(st_is_empty(st) == 1 && br_comp(begin, &temp) == 1)
		{
			st_push(st, temp);
			printf("if works\n");
		}
		printf("%c", temp);
	}
	
	printf("EOF\n");
	st_print(st);
	
	/* Data x;
	scanf("%d", &x); */

	/* int nsize = 0;
	int i = 0;

	while(1)
	{
	if(i >= nsize)
	{
	nsize += N;
	s = realloc(s, nsize * sizeof(char));
	}
	if(1 != scanf("%c", &s[i]))
	break;
	i++; */
	
	st_destroy(st);
	
	return 0;
}