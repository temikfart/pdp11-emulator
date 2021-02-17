#include <stdio.h>
#include <stdlib.h>

#ifdef AAA

typedef int Data;
struct Node {
    struct Node * next;
    struct Node * prev;
    Data data;
}Node;

void list_init(struct Node * list);
void list_insert(struct Node * list, struct Node * t);
void list_insert_before(struct Node * list, struct Node * t);
void list_remove(struct Node * t);
struct Node * list_push_front(struct Node * list, Data d);
struct Node * list_push_back(struct Node * list, Data d);
Data list_pop_front(struct Node * list);
Data list_pop_back(struct Node * list);
Data list_delete(struct Node * t);
void list_print (struct Node * list);
int list_is_empty(struct Node * list);
void list_clear(struct Node * list);

int main()
{
    
}
#endif

void list_init(struct Node * list)
{
    list->prev = list->next = list;
}
void list_insert(struct Node * list, struct Node * t)
{
    struct Node * list2 = list->next;
    
    list->next = t;
    t->prev = list;
    list2->prev = t;
    t->next = list2;
}
void list_insert_before(struct Node * list, struct Node * t)
{
    struct Node * list0 = list->prev;
    
    list0->next = t;
    t->prev = list0;
    list->prev = t;
    t->next = list;
}
void list_remove(struct Node * t)
{
    struct Node * p = t->prev;
    struct Node * q = t->next;
    
    p->next = q;
    q->prev = p;
}
struct Node * list_push_front(struct Node * list, Data d)
{
    struct Node * t = malloc(sizeof(struct Node));
    t->data = d;
    
    list_insert(list, t);
    
    return list;
}
struct Node * list_push_back(struct Node * list, Data d)
{
    struct Node * t = malloc(sizeof(struct Node));
    t->data = d;
    
    list_insert_before(list, t);
    
    return list;
}
Data list_pop_front(struct Node * list)
{
    struct Node * list2 = list->next;
    Data d = list2->data;

    list_remove(list2);
    
    free(list2);
    return d;
}
Data list_pop_back(struct Node * list)
{
    struct Node * list0 = list->prev; //последний элемент списка
    Data d = list0->data;
    
    list_remove(list0);
    
    free(list0);
    return d;
}
Data list_delete(struct Node * t)
{
    Data d = t->data;
    
    list_remove(t);
    
    free(t);
    return d;
}
void list_print(struct Node * list)
{
    for (struct Node * p = list->next; p != list; p = p->next) {
        printf("%d ", p->data);
    }
    printf("\n");
}
int list_is_empty(struct Node * list)
{
    return list->next == list;
}
void list_clear(struct Node * list)
{
    struct Node * p = list;
    while(!list_is_empty(p))
    {
        list_pop_front(p);
    }
    list = p;
}
