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
		printf("%s\n", strchr(str, eq));
		printf("%ld\n", strlen(strchr(str, eq)));
		pos = len - strlen(strchr(str, eq));
		printf("%d\n", pos);
		return pos;
	}
	return -1;
};

int main()
{
	char * str;
	str = malloc(N * sizeof(char));
	
	size_t length = N;
	unsigned int len = getline(&str, &length, stdin);
	
	printf("\n%d\n", len);
	printf("%ld\n", strlen(str));
	printf("%s\n", str);
	
	
	Stack * st;
	st = malloc(sizeof(Stack));
	st_init(st);
	
	printf("%d\n", def_eq_size(str, len));
	
	free(str);
	//free(dst);
	st_destroy(st);
	
	return 0;
}