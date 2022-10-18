#include <stdlib.h>
#include "STACK.h"


typedef struct STACKnode* link;
struct STACKnode { Item item; link next; };
static link head;


link NEW(Item item, link next)
{ 	
	link x = malloc(sizeof *x);
	x->item = item; x->next = next;
	return x;
}

void STACKinit(int maxN)
{ 
	head = NULL; 
}

int STACKempty()
{ 
	return head == NULL; 
}

int STACKpush(Item item)
{ 	
	head = NEW(item, head);
    return 1;
}

Item STACKpop()
{ 
	Item item = head->item;
    link t = head->next;
    free(head); head = t;
    return item;
}
  
