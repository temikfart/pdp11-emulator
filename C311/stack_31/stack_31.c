#include <stdio.h>
#include <stdlib.h>

#define N 10

/* typedef int Data;

struct Stack {
    int n;
    int size;
    Data * a; 
}; */

struct Stack * stack_create(int size)
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
int stack_is_empty(struct Stack * s)
{
    return s->n == 0;
};
int stack_is_full(struct Stack * s)
{
    return s->n == s->size;
};
void stack_push(struct Stack * s, Data x)
{
	if(stack_is_full(s))
	{
		s->size += N;
		s->a = realloc(s->a, s->size * sizeof(Data));
	}
	s->a[s->n] = x;
    s->n ++;
};
Data stack_pop(struct Stack * s)
{
    Data x = s->a[s->n - 1];
    s->n --;
    return x;
};
void stack_print(struct Stack * s)
{
    if(stack_is_empty(s) == 1)
        printf("Empty stack\n");
    else
    {
        for(int i = 0; i < s->n; i++)
            printf("%d ", s->a[i]); 
        printf("\n");
    }
};
int stack_size(struct Stack * s)
{
    return s->n;
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
};

/* int main()
{
    struct Stack * sp = stack_create(4);

    stack_push(sp, 5);
    stack_push(sp, 19);
    stack_push(sp, -2);
    stack_print(sp);
    //5 19 -2

    stack_push(sp, 27);
    stack_print(sp);
    //5 19 -2 27
    printf("is_empty=%d\n", stack_is_empty(sp));
    //is_empty=0

    Data x;
    x = stack_pop(sp);
    printf("x=%d\n", x);
    //x=27

    x = stack_pop(sp);
    printf("x=%d\n", x);
    //x=-2

    stack_print(sp);
    //5 19

    while (!stack_is_empty(sp)) {
        stack_pop(sp);
        stack_print(sp);
    }
    //5
    //Empty stack

    stack_destroy(sp);
    
    return 0;
} */
