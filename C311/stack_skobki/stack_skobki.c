#include <stdio.h>
#include <stdlib.h>

#define N 10

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
};
void stack_destroy(struct Stack * s)
{
	if(s != NULL)
	{
		stack_clear(s);
		free(s);
	}
}; */

int main()
{
	//const char * begin = "([{<";
	//const char * end = ")]}>";

	Stack * st;
	st = malloc(sizeof(Stack));
	st_init(st);
	
	
	printf("is empty: %d\n", st_is_empty(st)); 		//1
	st_print(st);									//empty stack
	st_push(st, '{');
	st_push(st, '>');
	printf("is empty: %d\n", st_is_empty(st));		//0

	st_print(st);									//{>
	printf("%c\n", st_pop(st));						//>
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
	
	free(st->a);
	free(st);
	
	
	return 0;
}