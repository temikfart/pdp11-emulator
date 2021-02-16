#include <stdio.h>
#include <stdlib.h>

typedef int Data;
struct Node {
    Data val;
    struct Node * next;
};

struct Node * list_create ();
int list_is_empty(struct Node * list);

struct Node * list_create ()
{
	return NULL;
}
int list_is_empty(struct Node * list)
{
	return list == NULL;
}

int main()
{
	struct Node * list = list_create();
	
	printf("Empty: %s\n", list_is_empty(list) ? "YES" : "NO");
	
	return 0;
}