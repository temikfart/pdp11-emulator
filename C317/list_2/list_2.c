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
void list_insert(struct Node * list, struct Node * t);
void list_insert_before(struct Node * list, struct Node * t);
void list_remove(struct Node * t);
struct Node * list_push_front(struct Node * list, Data d);
struct Node * list_push_back(struct Node * list, Data d);
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
    
    struct Node c;
    c.data = 11;
    list_insert(list, &c);
    list_print(list); // 11 5 7
    
    struct Node d;
    d.data = 100;
    list_insert_before(list, &d);
    list_print(list); // 11 5 7 100
    
    list_remove(&a);
    list_print(list); // 11 7 100
    
    Data x = 13;
    list = list_push_front(list, x);
    list_print(list); // 13 11 7 100

    Data y = 101;
    list = list_push_back(list, y);
    list_print(list); // 13 11 7 100 101
    
    return 0;
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
    struct Node * list2 = list->next;
    struct Node * t = malloc(sizeof(struct Node));
    t->data = d;
    
    list->next = t;
    t->prev = list;
    list2->prev = t;
    t->next = list2;
    
    return list;
}
struct Node * list_push_back(struct Node * list, Data d)
{
    struct Node * list0 = list->prev;
    struct Node * t = malloc(sizeof(struct Node));
    t->data = d;
    
    list0->next = t;
    t->prev = list0;
    list->prev = t;
    t->next = list;
    
    return list;
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
