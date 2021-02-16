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
	
	Data y = 0;
	list = list_pop(list, &y);
	printf("pop: %d\n", y);
	printf("Empty: %s\n", list_is_empty(list) ? "YES" : "NO");
	
	free(list);
	return 0;
}