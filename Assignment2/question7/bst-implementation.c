#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ST.h>


typedef struct STnode* link;

typedef struct HandleTag
{
	link head, z;
}HandleNode;

struct STnode 
{ 
	Item item; 
	link l, r; 
	int N; 
};

static int deleteflag; //Helps with deleting all same keys


link NEW(Item item, link l, link r, int N)
{ 
	link x = malloc(sizeof *x);
	x->item = item; 
	x->l = l; 
	x->r = r; 
	x->N = N;
	return x;
}


ST STinit(void)
{
	ST ST = malloc(sizeof(HandleNode));
	ST->head = (ST->z = NEW(NULLitem, NULL, NULL, 0));
	return ST; 
}


int STcount(ST ST) 
{ 
	return ST->head->N; 
}


Item searchR(link h, link z, Key v)
{ 
	Key t = key(GetKey(h->item));
    if(h == z) 
	{
		return NULLitem;
	}
    if eq(v, t) 
	{
		return h->item;
	}
    if less(v, t) 
	{
		return searchR(h->l, z, v);
	}
    else 
	{
		return searchR(h->r, z, v);
	}
}


Item STsearch(ST ST, Key v)
{ 
	return searchR(ST->head, ST->z, v); 
}


link insertR(link h, link z, Item item)
{ 
	Key v = key(GetKey(item)), t = -1;

	if(h->item != NULL)
	{
		t = key(GetKey(h->item));
	}
	if (h == z) 
	{
		return NEW(item, z, z, 1);
	}
	if less(v, t)
	{
		h->l = insertR(h->l, z, item);
	}
	else 
	{
		h->r = insertR(h->r, z, item);
	}
	(h->N)++; 
	return h;
}


// void STinsert(ST ST, Item item)
// { 
// 	ST->head = insertR(ST->head, ST->z, item); 
// }


void sortR(link h, link z, void (*visit)(Item))
{
	if(h == z) 
	{
		return;
	}
	sortR(h->l, z, visit);
	visit(h->item);
	sortR(h->r, z, visit);
}


void STsort(ST ST, void (*visit)(Item))
{ 
	sortR(ST->head, ST->z, visit); 
}


link rotR(link h)
{ 
	link x = h->l;
	int i = h->l->N;
	h->l->N = h->N; 
	h->l = x->r;
	i = i - x->r->N;
	x->r = h;
	x->r->N = x->r->N - i;
    return x; 
}


link rotL(link h)
{ 
	link x = h->r;
	int i = h->r->N;
	h->r->N = h->N; 
	h->r = x->l;
	i = i - x->l->N;
	x->l = h;
	x->l->N = x->l->N - i;
    return x; 
}


link insertT(link h, link z, Item item)
{ 
	Key v = key(GetKey(item));
    if(h == z) 
	{
		return NEW(item, z, z, 1);
	}
    if(less(v, key(GetKey(h->item))))
    { 
		h->l = insertT(h->l, z, item);
		(h->N)++; 
		h = rotR(h); 
	}
    else
    { 
		h->r = insertT(h->r, z, item);
		(h->N)++; 
		h = rotL(h); 
	}
    return h;
}


void STinsert(ST ST, Item item)
{ 
	ST->head = insertT(ST->head, ST->z, item); 
}


Item selectR(link h, link z, int k)
{ 
	int t;
	if(h == z) 
	{
		return NULLitem;
	}
	t = (h->l == z) ? 0 : h->l->N;
	if (t > k) 
	{
		return selectR(h->l, z, k);
	}
	if (t < k) 
	{
		return selectR(h->r, z, k-t-1);
	}
	return h->item;
}


Item STselect(ST ST, int k)  
{ 
	return selectR(ST->head, ST->z, k); 
}


link partR(link h, int k)
{ 
	int t = h->l->N;
    if(t > k )
    { 
		h->l = partR(h->l, k); 
		h = rotR(h); 
	}
    if(t < k )
    { 
		h->r = partR(h->r, k-t-1); 
		h = rotL(h); 
	}
    return h;
}


link joinLR(link a, link b, link z)
{
	if(b == z) 
	{
		return a;
	}
	b = partR(b, 0); 
	b->l = a;
	b->N = b->N + a->N;
	return b;
}


link deleteR(link h, link z, Key v)
{ 
	link x; 
	Key t = -1;

	if(h->item != NULL)
	{
		t = key(GetKey(h->item));
	}	
	if(h == z) 
	{
		deleteflag = 0; 
		return z;
	}
	if(less(v, t)) 
	{
		h->l = deleteR(h->l, z, v);
		if(deleteflag == 1)
		{
			(h->N)--;
		}
	}
	if(less(t, v)) 
	{
		h->r = deleteR(h->r, z, v);
		if(deleteflag == 1)
		{
			(h->N)--;
		}
	}
	if(eq(v, t))
	{ 
		x = h; 
		h = joinLR(h->l, h->r, z);
		FreeItem(x->item);
		free(x);
	}
	return h;
}


void STdelete(ST ST, Key v)
{
	deleteflag = 1;
	ST->head = deleteR(ST->head, ST->z, v); 
}

void STdeleteAll(ST ST, Key v)	//Keeps calling deleteR until key no longer exists
{
	deleteflag = 1;
	while(deleteflag == 1)
	{ 
		ST->head = deleteR(ST->head, ST->z, v);
	} 
}


// link STjoin(link a, link b)
// {
// 	if(b == z)
// 	{	
// 		return a;
// 	}
// 	if (a == z) 
// 	{
// 		return b;
// 	}
// 	STinsert(a->item);
// 	b->l = STjoin(a->l, b->l);
// 	b->r = STjoin(a->r, b->r);
// 	free(a);
// 	return b;
// }


void STend(ST ST)	//Destroys ST
{
	while(ST->head != ST->z)
	{
		STdelete(ST, GetKey(ST->head->item));
	}
	free(ST->z);
	free(ST);
}