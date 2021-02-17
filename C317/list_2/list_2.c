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
Data list_pop_front(struct Node * list);
Data list_pop_back(struct Node * list);
Data list_delete(struct Node * t);
void list_print (struct Node * list);
int list_is_empty(struct Node * list);
void list_clear(struct Node * list);
void my_tests();

int main ()
{
    struct Node x[10];
    struct Node * a = malloc(sizeof(struct Node));
    struct Node * b = malloc(sizeof(struct Node));

    list_init(a);
    list_init(b);
    // End of test 1
    
    for(int i = 0; i<10; i++) {
        x[i].data = i;
        list_insert(a, &x[i]);
    }
    list_print(a);   // 9 8 7 6 5 4 3 2 1 0 
    // End of test 2
    
    list_remove(&x[5]);
    list_print(a);
    list_remove(&x[0]);
    list_print(a);
    list_remove(&x[9]);
    list_print(a);
    // End of test 3
    
    list_insert_before(a, &x[0]);
    list_print(a);
    list_insert(a, &x[9]);
    list_print(a);
    list_insert(&x[6], &x[5]);
    list_print(a);
    // End of test 4
    
    while(!list_is_empty(a))
        list_remove(a->next);
    // End of test 5

    for(int i = 0; i<10; i++)
        list_push_back(a, i);
    list_print(a);
    // End of test 6
    
    for(int i = 0; i<10; i++)
        list_push_front(b, list_pop_back(a));
    list_print(b);
    // End of test 7
    
    for(int i = 0; i<10; i++) {
        list_push_front(a, i);
        list_pop_front(b);
    }
    list_print(a);
    // End of test 8

    for(int i = 0; i<10; i++)
        list_push_back(b, list_pop_front(a));
    list_print(b);
    // End of test 9
    
    list_clear(a);
    list_clear(b);
    // End of test 10
    
    //my_tests();
    
    free(a);
    free(b);
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
void my_tests()
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
    
    Data pop_x = list_pop_front(list);
    printf("Pop x: %d\n", pop_x);
    list_print(list); // 11 7 100 101
    
    Data pop_y = list_pop_back(list);
    printf("Pop y: %d\n", pop_y);
    list_print(list); // 11 7 100
    
    printf("----------\n");
    list = list_push_front(list, 199);
    list_print(list); //199 11 7 100
    
    list_delete(list->next);
    list_print(list); // 11 7 100
    
    ///////////////for list_clear
    
    list_remove(&c);
    list_remove(&b);
    list_remove(&d);
    printf("List is %s\n", list_is_empty(list) ? "empty" : "NOT empty");
    
    list_push_front(list, 2);
    list_push_back(list, 3);
    list_push_front(list, 1);
    list_print(list);
    
    list_clear(list);
    printf("List is %s\n", list_is_empty(list) ? "empty" : "NOT empty");
}
