#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DListInterface.h"
//#define DEBUG

typedef struct EndNodeTag *EndNodePointer;

static EndNodePointer Head, Tail;

typedef struct DlistTag		/*List with name and value information*/
{
	name name;
	value value;
	struct DlistTag *next;
	struct DlistTag *previous;
} DlistType;
typedef DlistType *DlistPointer;

typedef struct EndNodeTag	/*Head and Tail Nodes*/
{
	int count;
	DlistPointer Pointer;
} EndNodeType;
typedef EndNodeType *EndNodePointer;


void Create()	/*Creates empty list*/
{
	Head = malloc(sizeof(EndNodeType));
	Tail = malloc(sizeof(EndNodeType));
	Head->count = 0;
	Head->Pointer = NULL;
	Tail->count = 0;
	Tail->Pointer = NULL;
}


int Size()	/*Returns List size*/
{
	return Head->count;
}


int IsEmpty()	/*Returns 1 if List is empty, else returns 0*/
{
	if (Head->count == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


DlistPointer GetFirst()	/*Returns First Node if it exists, else returns NULL*/
{
	if (Head->Pointer != NULL)
	{
		return Head->Pointer;
	}
	else
	{
		return NULL;
	}
}


DlistPointer GetLast()	/*Returns Last Node if it exists, else returns NULL*/
{	
	if (Tail->Pointer != NULL)
	{
		return Tail->Pointer;
	}
	else
	{
		return NULL;
	}
}


DlistPointer GetPrev(DlistPointer GivenNode)	/*Returns Previous Node of a given Node if it exists, else returns NULL*/
{
	return GivenNode->previous;
}


DlistPointer GetNext(DlistPointer GivenNode)	/*Returns Next Node of a given Node if it exists, else returns NULL*/
{
	return GivenNode->next;
}


void AddBefore(DlistPointer NodeIn, DlistPointer GivenNode) /*Adds a given Node before an given Node if the given Node exists, else does nothing*/
{
	if (Head->count == 0)
	{
		return;
	}
	NodeIn->next = GivenNode;
	NodeIn->previous = GivenNode->previous;
	GivenNode->previous = NodeIn;
	if(NodeIn->previous == NULL)
	{
		Head->Pointer = NodeIn;
	}
	else
	{
		NodeIn->previous->next = NodeIn;
	}
	Head->count++;
	Tail->count++;
}


void AddAfter(DlistPointer NodeIn, DlistPointer GivenNode) /*Adds a given Node after an given Node if exists, else does nothing*/
{
	if (Tail->count == 0)
	{
		return;
	}
	NodeIn->next = GivenNode->next;
	NodeIn->previous = GivenNode;
	GivenNode->next = NodeIn;
	if(NodeIn->next == NULL)
	{
		Tail->Pointer = NodeIn;
	}
	else
	{
		NodeIn->next->previous = NodeIn;
	}
	Tail->count++;
	Head->count++;
}


void AddFirst(DlistPointer NodeIn) 	/*Adds a given Node at Head*/
{
	NodeIn->next = Head->Pointer;
	NodeIn->previous = NULL;
	if(Head->Pointer != NULL)
	{
		Head->Pointer->previous = NodeIn;
	}
	else
	{
		Tail->Pointer = NodeIn;
	}
	Head->Pointer = NodeIn;
	Head->count++;
	Tail->count++;
}


void AddLast(DlistPointer NodeIn)	/*Adds a given Node at Tail*/
{
	NodeIn->next = NULL;
	NodeIn->previous = Tail->Pointer;
	if(Tail->Pointer != NULL)
	{
		Tail->Pointer->next = NodeIn;
	}
	else
	{
		Head->Pointer = NodeIn;
	}
	Tail->Pointer = NodeIn;
	Tail->count++;
	Head->count++;
}


void Remove(DlistPointer GivenNode)		/*Removes a given Node from List*/
{
	if (Head->count == 0)
	{
		return;
	}
	if(GivenNode->next != NULL)
	{
		GivenNode->next->previous = GivenNode->previous;
	}
	else
	{
		Tail->Pointer = GivenNode->previous;
	}
	if(GivenNode->previous != NULL)
	{
		GivenNode->previous->next = GivenNode->next;
	}
	else
	{
		Head->Pointer = GivenNode->next;
	}
	free(GivenNode->name);
	free(GivenNode);
	Head->count--;
	Tail->count--;
}


void Print()	/*Prints List from Head to Tail*/
{
	DlistPointer TempHead = Head->Pointer;
	printf("[ ");
	#ifdef DEBUG
		printf("(%d, %p) ", Head->count, Head->Pointer);
	#endif
	while (TempHead != NULL)
	{
		printf("(");
		printf("%s, ", TempHead->name);
		printf("%d", TempHead->value);
		#ifdef DEBUG
			printf(", ");
			printf ("%p, ", TempHead->next);
			printf ("%p", TempHead->previous);
		#endif
		printf(") ");
		TempHead = TempHead->next;
	}
	#ifdef DEBUG
		printf("(%d, %p) ", Tail->count, Tail->Pointer);
	#endif
	printf("]\n");
}


name GetName(DlistPointer NodeP)	/*Returns a given Node name*/
{
	return NodeP->name;
}


value GetValue(DlistPointer NodeP)	/*Returns a given Node value*/
{
	return NodeP->value;
}


DlistPointer NewNode(char *name, int value)		/*It creates a new node with a given name and value and returns it*/
{
	DlistPointer Temp;
	Temp = malloc(sizeof(DlistType));
	Temp->name = malloc((strlen(name)+1)*sizeof(char));
	strcpy(Temp->name, name);
	Temp->value = value;
	return Temp;
}


void EndList(void)
{
	free(Head);
	free(Tail);
}