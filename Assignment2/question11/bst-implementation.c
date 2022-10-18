#include <stdio.h>
#include <stdlib.h>
#include <ST.h>

#define FALSE 0
#define TRUE 1
#define M 4		//Maximum number of children
#define MAX (M-1) //Maximum number of keys

#if ((M%2) == 0)	
	#define CEIL_MDIV2 (M/2)
#else						//Minimun number of children
	#define CEIL_MDIV2 ((M+1)/2)
#endif

#define MIN (CEIL_MDIV2-1) //Minimum number of keys


typedef struct STnode* link;

typedef struct HandleTag	//Handle Node
{
	link head, z;
}HandleNode;

struct STnode 	//Main Node
{ 
	int numKeys;
	Item key[M];
	link child[M];
	int count[M];	
};

static int freeflag; 	//Helps with freeing Item info
static int deleteflag, insertflag;	//Return if each operation was succesfull

int countNode(link n)
{
    int count = 0;
    int i;

    if (!n)
	{
		return 0;
	}
    for (i = 0; i<=n->numKeys; i++)
	{
		count += n->count[i];
	}
    count += n->numKeys;
    return count;
}



ST STinit(void)
{
	link temp;

	ST ST = malloc(sizeof(HandleNode));	//Creation of z

	temp = malloc(sizeof(*temp));
	temp->numKeys = 0;
	for(int i=0; i<M; i++)
	{
		temp->child[i] = NULL;
	}
	for(int i=1 ; i<M; i++)
	{
		temp->key[i] = NULLitem;
	}
	for(int i=0; i<M; i++)
	{
		temp->count[i] = 0;
	}
	ST->head = temp;	//Link z to handles
	ST->z = temp;

	return ST; 
}


int STcount(ST ST) 
{ 
	return countNode(ST->head);
}


int searchNode(int v, link h, int *n)	//Returns position via pointer and if key was found
{
	if(v < GetKey(h->key[1])) //Key not found return false
	{
		*n = 0; //next search position is all left
		return FALSE;
	}

	*n = h->numKeys;
	while((v < GetKey(h->key[*n]) && *n>1))
	{
		(*n)--; //Define next search position by comparing to nodes keys
	}

	if(v == GetKey(h->key[*n]))
	{
		return TRUE; //If key found return true
	}
	else
	{
		return FALSE;	//else false
	}
}


Item searchR(link h, link z, Key v)
{
	int n=0;

    if(h == z) //Key can't exist in tree
	{
		return NULLitem;
	}
    if(searchNode(v, h, &n)) 
	{
		return h->key[n];	//Key found in current node
	}
	return searchR(h->child[n], z, v); //Search in current node's child
}


Item STsearch(ST ST, Key v)
{ 
	return searchR(ST->head, ST->z, v); 
}


void split(link h, link z, int n, Item *iKey, link *iKeyRchild)
{
	int i, j, d, lastCount;
	link lastChild, newNode;
	Item medianKey, lastKey;

	if(n == MAX)
	{
		lastKey = *iKey;
		lastChild = *iKeyRchild;
		lastCount = countNode(*iKeyRchild);
	}
	else
	{
		lastKey = h->key[MAX];
		lastChild = h->child[MAX];
		lastCount = h->count[MAX];
		for(i=h->numKeys-1; i>n; i--)
		{
			h->key[i+1] = h->key[i];
			h->child[i+1] = h->child[i];
			h->count[i+1] = h->count[i];
		}
		h->key[i+1] = *iKey;
		h->child[i+1] = *iKeyRchild;
		h->count[i+1] = countNode(*iKeyRchild);
	}

	d = CEIL_MDIV2;
	medianKey = h->key[d];

	newNode = malloc(sizeof(*newNode));
	newNode->numKeys = M - d;

	newNode->child[0] = h->child[d];
	newNode->count[0] = h->count[d];
	for(i=1, j=d+1; j<=MAX; i++, j++)
	{
		newNode->key[i] = h->key[j];
		newNode->child[i] = h->child[j];
		newNode->count[i] = h->count[j];
	}

	newNode->key[i] = lastKey;
	newNode->child[i] = lastChild;
	newNode->count[i] = lastCount;

	h->numKeys = d-1;

	*iKey = medianKey;
	*iKeyRchild = newNode;
}


void insertByShift(link h, link z, int n, Item iKey, link iKeyRchild)
{
	int i;

	for(i=h->numKeys; i>n; i--) //First shift the keys
	{
		h->key[i+1] = h->key[i];
		h->child[i+1] = h->child[i];
		h->count[i+1] = h->count[i];
	}
	h->key[n+1] = iKey;	//Then insert at the right position
	h->child[n+1] = iKeyRchild; //Take splited child if exists
	h->count[n+1] = countNode(iKeyRchild); //count nodes of subtree
	h->numKeys++;
}


int insertR(Item item, link h, link z, Item *iKey, link *iKeyRchild)
{ 
	Key v = GetKey(item);
	int n=0, flag;

	if(h == z) //Key does't exist already
	{
		*iKey = item;
		*iKeyRchild = z;
		return TRUE;
	}

	if(searchNode(v, h, &n)) //Key exists so can't allow second insertion
	{
		printf("\nDuplicate keys are not allowed\n");
		insertflag = 0;
		return FALSE; //Cancel insertion
	}

	flag = insertR(item, h->child[n], z, iKey, iKeyRchild);

	h->count[n] = countNode(h->child[n]);

	if(flag)
	{
		if(h->numKeys < MAX)
		{
			insertByShift(h, z, n, *iKey, *iKeyRchild);
			return FALSE; //Insertion is done
		}
		else
		{
			split(h, z, n, iKey, iKeyRchild);
			return TRUE;	//Insertion hasn't finished, median key must be inserted upwards
		}
	}
	return FALSE;
}


int STinsert(ST ST, Item item)
{ 
	int taller;
	Item iKey = NULLitem;
	link iKeyRchild = ST->z, temp;

	if(item == NULLitem)
	{
		return FALSE;
	}

	insertflag = 1;
	taller = insertR(item, ST->head, ST->z, &iKey, &iKeyRchild);

	if(taller) //Height is incresed here by 1, new root is created
	{
		temp = malloc(sizeof(*temp));
		temp->numKeys = 1;
		temp->child[0] = ST->head;
		temp->count[0] = countNode(ST->head);
		temp->key[1] = iKey;
		temp->child[1] = iKeyRchild;
		temp->count[1] = countNode(iKeyRchild);
		ST->head = temp;
	}
	return insertflag;
}


void sortR(link h, link z, void (*visit)(Item))
{
	int i;
	
	if(h == z) 
	{
		return;
	}
	for(i=0; i<h->numKeys; i++)
	{
		sortR(h->child[i], z, visit);
		visit(h->key[i+1]);
	}
	sortR(h->child[i], z, visit);
}


void STsort(ST ST, void (*visit)(Item))
{ 
	sortR(ST->head, ST->z, visit); 
}


Item selectR(link h, link z, int k)
{
	int i, t;

	for(i=0; i<=h->numKeys; i++)
	{
		t = 0;
		if(h->child[i] != z)
		{
			t = h->count[i];
		}
		if(k < t)
		{
			return selectR(h->child[i], z, k);
		}
		else if(k == t && i != h->numKeys)
		{
			return h->key[i+1];
		}
		else
		{
			k -= t + 1;
		}
	}
	return NULLitem;
}


Item STselect(ST ST, int k)  
{
	if(k >= 0)
	{ 
		return selectR(ST->head, ST->z, k);
	}
	else
	{
		return NULLitem;
	}
}


void combine(link h, int m)
{
	int i;
	link nodeA = h->child[m-1];
	link nodeB = h->child[m];

	nodeA->numKeys++;

	nodeA->key[nodeA->numKeys] = h->key[m]; //Move the key from the parent node to nodeA

	for(i=m; i<h->numKeys; i++)	//Shift the keys thay are after seperator key in parent node by 1
	{
		h->key[i] = h->key[i+1];
		h->child[i] = h->child[i+1];
		h->count[i] = h->count[i+1];
	}
	h->numKeys--;

	nodeA->child[nodeA->numKeys] = nodeB->child[0];	//Most left child of nodeB becomes most right child of nodeA
	nodeA->count[nodeA->numKeys] = nodeB->count[0];

	for(i=1; i<=nodeB->numKeys; i++)	//Insert all the keys and children of nodeB at the end of nodeA
	{
		nodeA->numKeys++;
		nodeA->key[nodeA->numKeys] = nodeB->key[i];
		nodeA->child[nodeA->numKeys] = nodeB->child[i];
		nodeA->count[nodeA->numKeys] = nodeB->count[i];
	}
	free(nodeB);
}


void borrowLeft(link h, int n)
{
	int i;
	link underflowNode = h->child[n];
	link leftSibling = h->child[n-1]; //Left sibling of underflow Node

	underflowNode->numKeys++;

	for(i = underflowNode->numKeys; i>0; i--) //Shift all keys and children in underflow node right so borrowed key can be inserted
	{
		underflowNode->key[i+1] = underflowNode->key[i];
		underflowNode->child[i+1] = underflowNode->child[i];
		underflowNode->count[i+1] = underflowNode->count[i];
	}
	underflowNode->child[1] = underflowNode->child[0];
	underflowNode->count[1] = underflowNode->count[0];

	underflowNode->key[1] = h->key[n]; //Move seperator key from parent node to undeflow node

	h->key[n] = leftSibling->key[leftSibling->numKeys]; //Move the most right key of leftsibling to parent node

	underflowNode->child[0] = leftSibling->child[leftSibling->numKeys]; //Most right child of leftsibling becomes most left child of underflow node
	underflowNode->count[0] = leftSibling->count[leftSibling->numKeys];

	leftSibling->numKeys--;
}


void borrowRight(link h, int n)
{
	int i;
	link underflowNode = h->child[n];
	link rightSibling = h->child[n+1]; //Right sibling of underflow Node

	underflowNode->numKeys++;
	underflowNode->key[underflowNode->numKeys] = h->key[n+1]; //Move seperator key from parent node to underflow Node

	underflowNode->child[underflowNode->numKeys] = rightSibling->child[0];	//Most left child of node right sibling becomes the most right child of underflow Node
	underflowNode->count[underflowNode->numKeys] = rightSibling->count[0];

	h->key[n+1] = rightSibling->key[1];	//Move the most left key from node right sibling to parent node
	rightSibling->numKeys--;

	rightSibling->child[0] = rightSibling->child[1];	//Shift all keys and children of node right sibling one posotion left
	rightSibling->count[0] = rightSibling->count[1];
	for(i=1; i<=rightSibling->numKeys; i++)
	{
		rightSibling->key[i] = rightSibling->key[i+1];
		rightSibling->child[i] = rightSibling->child[i+1];
		rightSibling->count[i] = rightSibling->count[i+1];
	}
}


void restore(link h, int n) //Called when underflow happens
{
	if(n != 0 && h->child[n-1]->numKeys > MIN)
	{
		borrowLeft(h, n);
		h->count[n-1] = countNode(h->child[n-1]);
		h->count[n] = countNode(h->child[n]);
		
	}
	else if(n != h->numKeys && h->child[n+1]->numKeys > MIN)
	{
		borrowRight(h, n);
		h->count[n] = countNode(h->child[n]);
		h->count[n+1] = countNode(h->child[n+1]);
	}
	else
	{
		if(n != 0) //There is a left sibling
		{
			combine(h, n); //Combine with left sibling
			h->count[n-1] = countNode(h->child[n-1]);
		}
		else
		{
			combine(h, n+1);	//Combine with right sibling
			h->count[n] = countNode(h->child[n]);
		}
	}
}


void deleteByShift(link h, int n)
{
	int i;

	if(freeflag == TRUE)
	{
		FreeItem(h->key[n]);
	}
	for(i = n+1; i<=h->numKeys; i++) //Shilt all keys needed left
	{
		h->key[i-1] = h->key[i];
		h->child[i-1] = h->child[i];
		h->count[i-1] = h->count[i];
	}
	h->numKeys--;
}


void deleteR(link h, link z, Key v)
{ 
	int n=0;
	link s;

	if(searchNode(v, h, &n)) //Key is found in Node
	{
		if(h->child[n] == z)	//If Node is a leaf
		{
			deleteByShift(h, n);
			return;
		}
		else	//If Node is non-leaf
		{
			s = h->child[n]; //Go to the right subtree
			while(s->child[0] != z)	//Go down untill Leaf Node is found
			{
				s = s->child[0];
			}
			FreeItem(h->key[n]);
			freeflag = FALSE;
			h->key[n] = s->key[1];
			deleteR(h->child[n], z, GetKey(s->key[1]));
			h->count[n] = countNode(h->child[n]);
		}
	}
	else //Key not found in Node
	{
		if(h->child[n] == z)	//If Node is a leaf
		{
			deleteflag = FALSE;
			printf("\nKey %d is not present in the tree\n", v);
			return;
		}
		deleteR(h->child[n], z, v);
		h->count[n] = countNode(h->child[n]);
	}
	if(h->child[n]->numKeys < MIN) //Checking for underflow here
	{
		restore(h, n);
	}
}


int STdelete(ST ST, Key v)
{
	link temp;

	if(ST->head == ST->z)
	{
		printf("Tree is empty");
		return FALSE;
	}

	freeflag = TRUE;
	deleteflag = TRUE;
	deleteR(ST->head, ST->z, v);

	if((ST->head != ST->z) && (ST->head->numKeys == 0)) //Height decreased here by 1
	{
		temp = ST->head;
		ST->head = ST->head->child[0]; //Root becomes most left child
		free(temp);
	}
	return deleteflag;
}


void STend(ST ST)
{
	while(ST->head != ST->z)
	{
		STdelete(ST, GetKey(ST->head->key[1]));
	}
	free(ST->z);
	free(ST);
}