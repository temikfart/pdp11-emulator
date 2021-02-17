#include <stdio.h>
#include <stdlib.h>

#ifdef AAA

typedef int Data;
struct Node {
    struct Node * next;
    struct Node * prev;
    Data data;
};

void list_init(struct Node * list);

int main ()
{
    struct Node z;
    struct Node * list = &z;
    list_init(list);
    
    return 0;
}
#endif

void list_init(struct Node * list)
{
    list->prev = list;
    list->next = list;
}