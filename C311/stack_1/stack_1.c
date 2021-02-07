#include <stdio.h>
#include <stdlib.h>

/* #define N 100
typedef int Data;

struct Stack {
    int n;
    Data a[N];
}; */

void stack_create(struct Stack * s)
{
    s->n = 0;
};
void stack_push(struct Stack * s, Data x)
{
    s->a[s->n] = x;
    s->n ++;
};
Data stack_pop(struct Stack * s)
{
    Data x = s->a[s->n - 1];
    s->n --;
    return x;
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
void stack_print(struct Stack * s)
{
    if(stack_is_empty(s) != 0)
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
    s->n = 0;
};
/* void stack_destroy(struct Stack * s)
{
    if(s != NULL)
    {
        stack_clear(s);
        free(s);
    }
}; */

/* int main()
{
    struct Stack s;
    stack_create(&s);
    
    stack_push(&s, 5);
    stack_print(&s);
    
    stack_push(&s, 19);
    stack_print(&s);
    
    Data x;
    x = stack_size(&s);
    printf("size=%d\n", x);
    
    x = stack_pop(&s);
    printf("x=%d\n", x);
    
    stack_print(&s);
    x = stack_pop(&s);
    
    printf("x=%d\n", x);
    
    stack_print(&s);
    
    return 0;
} */