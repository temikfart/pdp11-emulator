#include <stdio.h>
#include <stdlib.h>

//#ifdef AAA

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
int card_cmp(Data fir, Data sec);
Node * cards_to_hand(Node * list, Data c1, Data c2);

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
    //list_print(list1);
    list2 = list_scan(list2);
    //list_print(list2);
    //Cards
    Data c1, c2;
    int ind = 0;
    for(int i = 0; i < N; i++)
    {
        if(list_is_empty(list1) + list_is_empty(list2) > 0)
        {
            int f = list_is_empty(list1);
            int s = list_is_empty(list2);
            printf("%s %d\n", (f < s) ? "first" : "second", (i) );
            ind++;
            break;
        }
        //Берем карты
        c1 = list_pop_front(list1);
        c2 = list_pop_front(list2);
        //printf("\n");
        //printf("1: %d; 2: %d;\n", c1, c2);
        
        //printf("%s\n", card_cmp(c1, c2) ? "Первый победил" : "Второй победил");
        
        //Находим победителя и отдаем ему карты
        if(card_cmp(c1, c2) == 2)
        {
            list1 = cards_to_hand(list1, c1, c2);
            //printf("----------\nХод №%d\n", i+1);
            //printf("f: ");
            //list_print(list1);
            //printf("s: ");
            //list_print(list2);
        }
        else if(card_cmp(c1, c2) == 0)
        {
            list2 = cards_to_hand(list2, c1, c2);
            //printf("----------\nХод №%d\n", i+1);
            //printf("f: ");
            //list_print(list1);
            //printf("s: ");
            //list_print(list2);
        }
        else
        {
            printf("<Ошибка! Карта не ложится в руку.>\n");
            break;
        }
        
        //break;
    }
    if(!ind)
        printf("botva\n");
    
    
    list_clear(list1);
    list_clear(list2);
    return 0;
}
//#endif

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
int card_cmp(Data f, Data s)
{
    /* if(f+s == 9 && (!f)+(!s) > 0)) // 0 > 9
        return (f < s) - (f > s);
    else
        return (f > s) - (f < s); */
    //////////////////////
    if(f+s == 9 && (!f)+(!s) > 0)
    {
        f = !f;
        s = !s;
    }
    return (f > s) - (f < s) + 1; //win: f --- 2; s --- 0
}
Node * cards_to_hand(Node * list, Data c1, Data c2)
{
    list_push_back(list, c1);
    list_push_back(list, c2);
    return list;
}
