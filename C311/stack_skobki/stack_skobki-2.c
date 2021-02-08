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
            printf("%c ", s->a[i]);
        printf("\n");
    }
}
Data st_pop(Stack * s)
{
    if(st_is_empty(s))
        return -1;
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
int br_comp(const char * br, Data temp)
{
    for(int i = 0; i < Brackets; i++)
    {
        if(br[i] == temp )
        {
            return i+1;
            break;
        }
    }
    return 0;
}

int main()
{
    const char * begin = "([{<";
    const char * end = ")]}>";

    Stack * st;
    st = malloc(sizeof(Stack));
    st_init(st);
    
    Data temp;
    Data xpop;
    Data y1, y2;
    int j = 0;
    while(scanf("%c", &temp) != EOF)
    {
        if(br_comp(begin, temp))
        {
            st_push(st, temp);
        }
        if(br_comp(end, temp))
        {
            xpop = st_pop(st);
            if(xpop == -1)
            {
                printf("NO\n");
                j++;
                break;
            }
            y1 = br_comp(begin, xpop);
            y2 = br_comp(end, temp);
            if(y1 != y2)
            {
                printf("NO\n");
                j++;
                break;
            }
        }
    }
    
    if(j == 0 && st_is_empty(st) == 0)
    {
        printf("NO\n");
        j++;
    }
    if(j == 0)
        printf("YES\n");
    
    st_destroy(st);
    
    return 0;
}