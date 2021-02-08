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

int main()
{
	char * str;
	str = malloc(N * sizeof(char));
	
	size_t length = N;
	unsigned int len = getline(&str, &length, stdin);
	
	printf("%d\n", len);
	printf("%s\n", str);
	
	
	Stack * st;
	st = malloc(sizeof(Stack));
	st_init(st);
	
	
	
	
	free(str);
	st_destroy(st);
	
	return 0;
}