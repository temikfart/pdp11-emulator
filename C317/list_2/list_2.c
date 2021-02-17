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
int list_is_empty(struct Node * list);

int main ()
{
    struct Node z;
    struct Node * list = &z;
    list_init(list);
    
    printf("List is %s\n", list_is_empty(list) ? "empty" : "NOT empty");
    
    return 0;
}
#endif

void list_init(struct Node * list)
{
    list->prev = list->next = list;
}
int list_is_empty(struct Node * list)
{
    return list->next == list;
}
