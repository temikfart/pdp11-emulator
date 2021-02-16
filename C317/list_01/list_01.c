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

int main()
{
    /* struct Node * list = list_create();
    
    printf("Empty: %s\n", list_is_empty(list) ? "YES" : "NO");
    
    Data x = 15;
    list = list_push(list, x);
    printf("Empty: %s\n", list_is_empty(list) ? "YES" : "NO");
    
    printf("list get: %d\n", list_get(list));
    
    list = list_push(list, 14);
    list = list_push(list, 13);
    list = list_push(list, 12);
    
    list_print(list); // 12 13 14 15
    printf("Size: %d\n", list_size(list));
    
    Data y = 0;
    list = list_clear(list);
    list = list_push(list, x);
    
    list = list_pop(list, &y);
    printf("pop: %d\n", y);
    printf("Empty: %s\n", list_is_empty(list) ? "YES" : "NO"); */
	
	List list = list_create();
	
	Data x = 7;
	list_push(&list, x);
	printf("Val: %d\n", list->val);
    
	
    free(list);
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
