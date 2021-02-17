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
void list_print (struct Node * list);
int list_is_empty(struct Node * list);

int main ()
{
    struct Node z;
    struct Node * list = &z;
    list_init(list);
    
    printf("List is %s\n", list_is_empty(list) ? "empty" : "NOT empty");
    
    struct Node a, b;
    a.data = 5;
    b.data = 7;
    
    list->next = &a;
    list->prev = &b;
    a.next = &b;
    a.prev = list;
    b.next = list;
    b.prev = &a;
    list_print(list); //5 7
    printf("List is %s\n", list_is_empty(list) ? "empty" : "NOT empty");
    
    return 0;
}
#endif

void list_init(struct Node * list)
{
    list->prev = list->next = list;
}
void list_print(struct Node * list) {
    for (struct Node * p = list->next; p != list; p = p->next) {
        printf("%d ", p->data);
    }
    printf("\n");
}
int list_is_empty(struct Node * list)
{
    return list->next == list;
}
