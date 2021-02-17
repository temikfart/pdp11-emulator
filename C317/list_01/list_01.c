#include <stdio.h>
#include <stdlib.h>

#ifdef AAA

typedef int Data;
struct Node {
    Data val;
    struct Node * next;
};
typedef struct Node * List;

List list_create ();
void list_push (List * plist, Data x);
Data list_pop (List * plist);
Data list_get(List list);
void list_print (List list);
int list_size(List list);
int list_is_empty(List list);
void list_clear(List * plist);

int main()
{
    List list = list_create();
    
    printf("List is %s\n", list_is_empty(list) ? "empty" : "not empty");
    
    Data x = 7;
    list_push(&list, x);
    printf("Val: %d\n", list->val);
    
    list_push(&list, 5);
    printf("Val: %d\n", list->val);
    
    Data y = list_pop(&list);
    printf("Pop: %d\n", y);
    printf("Val: %d\n", list->val);
    
    y = list_get(list);
    printf("Get: %d\n", y);
    
    list_push(&list, 17);
    list_push(&list, 1);
    list_print(list); // 1 17 7
    
    int size = list_size(list);
    printf("Size: %d\n", size);
    
    printf("List is %s\n", list_is_empty(list) ? "empty" : "not empty");
    
    list_clear(&list);
    printf("List is %s\n", list_is_empty(list) ? "empty" : "not empty");
    list_print(list);
    
    
    List list2 = list_create();
    list_push(&list2, 5);
    list_print(list2);
    list_clear(&list2);
    
    return 0;
}

#endif

List list_create ()
{
    return NULL;
}
void list_push (List * plist, Data x)
{
    List p = malloc(sizeof(struct Node));
    p->val = x;
    p->next = *plist;
    *plist = p;
}
Data list_pop (List * plist)
{
    List newlist = (*plist)->next;
    Data x = (*plist)->val;
    free(*plist);
    *plist = newlist;
    return x;
}
Data list_get(List list)
{
    return list->val;
}
void list_print (List list)
{
    if(list_is_empty(list))
        printf("Empty stack"); //В задании просят писать list, а не stack :-(
    for(List p = list; p != NULL; p = p->next)
    {
        printf("%d ", p->val);
    }
    printf("\n");
}
int list_size(List list)
{
    int n = 0;
    for(List p = list; p != NULL; p = p->next)
    {
        n++;
    }
    return n;
}
int list_is_empty(List list)
{
    return list == NULL;
}
void list_clear(List * plist)
{
    List p = *plist;
    while(p != NULL)
    {
        list_pop(&p);
    }
    *plist = p;
}
