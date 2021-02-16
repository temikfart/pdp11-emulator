#include <stdio.h>
#include <stdlib.h>

typedef int Data;
struct Node {
    Data val;
    struct Node * next;
};

struct Node * list_create ();
struct Node * list_push (struct Node * list, Data x);
struct Node * list_pop (struct Node * plist, Data * px);
Data list_get(struct Node * list);
void list_print (struct Node * list);
int list_is_empty(struct Node * list);

struct Node * list_create ()
{
	return NULL;
}
struct Node * list_push (struct Node * list, Data x)
{
	struct Node * list2 = NULL;
	list2 = malloc(sizeof(struct Node));
	list2->val = x;
	list2->next = list;
	return list2;
}
struct Node * list_pop (struct Node * plist, Data * px)
{
	*px = plist->val;
	struct Node * nextlist = plist->next;
	free(plist);
	return nextlist;
}
Data list_get(struct Node * list)
{
	return list->val;
}
void list_print (struct Node * list)
{
	for(struct Node * p = list; p != NULL; p = p->next)
	{
		printf("%d ", p->val);
	}
	printf("\n");
}
int list_is_empty(struct Node * list)
{
	return list == NULL;
}

int main()
{
	struct Node * list = list_create();
	
	printf("Empty: %s\n", list_is_empty(list) ? "YES" : "NO");
	
	Data x = 15;
	list = list_push(list, x);
	printf("Empty: %s\n", list_is_empty(list) ? "YES" : "NO");
	
	printf("list get: %d\n", list_get(list));
	
	list = list_push(list, 14);
	list = list_push(list, 13);
	list = list_push(list, 12);
	
	list_print(list); // 12 13 14 15
	
	Data y = 0;
	list = list_pop(list, &y);
	list = list_pop(list, &y);
	list = list_pop(list, &y);
	
	list = list_pop(list, &y);
	printf("pop: %d\n", y);
	printf("Empty: %s\n", list_is_empty(list) ? "YES" : "NO");
	
	free(list);
	return 0;
}