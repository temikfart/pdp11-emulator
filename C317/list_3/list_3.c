#include <stdio.h>
#include <stdlib.h>

#ifdef AAA

#define N 1000000
#define KOL 5

typedef int Data;
typedef struct Node {
    struct Node * next;
    struct Node * prev;
    Data data;
}Node;

void list_init(Node * list);
void list_insert(Node * list, Node * t);
void list_insert_before(Node * list, Node * t);
void list_remove(Node * t);
Node * list_push_front(Node * list, Data d);
Node * list_push_back(Node * list, Data d);
Data list_pop_front(Node * list);
Data list_pop_back(Node * list);
Data list_delete(Node * t);
void list_print (Node * list);
int list_is_empty(Node * list);
void list_clear(Node * list);
Node * list_scan(Node * list);

int main()
{
    //init
    Node z1, z2;
    Node * list1 = &z1;
    Node * list2 = &z2;
    list_init(list1);
    list_init(list2);
    //scan
    list1 = list_scan(list1);
    list_print(list1);
    list2 = list_scan(list2);
    list_print(list2);
    //Cards
    Data c1, c2;
    for(int i = 0; i < N; i++)
    {
        //
        c1 = list_pop_front(list1);
        c2 = list_pop_front(list2);
        
        printf("\n");
        printf("1: %d; 2: %d;\n", c1, c2);
        break;
    }
    
    list_clear(list1);
    list_clear(list2);
    return 0;
}
#endif

void list_init(Node * list)
{
    list->prev = list->next = list;
}
void list_insert(Node * list, Node * t)
{
    Node * list2 = list->next;
    
    list->next = t;
    t->prev = list;
    list2->prev = t;
    t->next = list2;
}
void list_insert_before(Node * list, Node * t)
{
    Node * list0 = list->prev;
    
    list0->next = t;
    t->prev = list0;
    list->prev = t;
    t->next = list;
}
void list_remove(Node * t)
{
    Node * p = t->prev;
    Node * q = t->next;
    
    p->next = q;
    q->prev = p;
}
Node * list_push_front(Node * list, Data d)
{
    Node * t = malloc(sizeof(Node));
    t->data = d;
    
    list_insert(list, t);
    
    return list;
}
Node * list_push_back(Node * list, Data d)
{
    Node * t = malloc(sizeof(Node));
    t->data = d;
    
    list_insert_before(list, t);
    
    return list;
}
Data list_pop_front(Node * list)
{
    Node * list2 = list->next;
    Data d = list2->data;

    list_remove(list2);
    
    free(list2);
    return d;
}
Data list_pop_back(Node * list)
{
    Node * list0 = list->prev; //последний элемент списка
    Data d = list0->data;
    
    list_remove(list0);
    
    free(list0);
    return d;
}
Data list_delete(Node * t)
{
    Data d = t->data;
    
    list_remove(t);
    
    free(t);
    return d;
}
void list_print(Node * list)
{
    for (Node * p = list->next; p != list; p = p->next) {
        printf("%d ", p->data);
    }
    printf("\n");
}
int list_is_empty(Node * list)
{
    return list->next == list;
}
void list_clear(Node * list)
{
    Node * p = list;
    while(!list_is_empty(p))
    {
        list_pop_front(p);
    }
    list = p;
}
Node * list_scan(Node * list)
{
    Data x = -1;
    for(int i = 0; i < KOL; i++)
    {
        scanf("%d", &x);
        list_push_back(list, x);
        //list_print(list);
    }
    return list;
}
