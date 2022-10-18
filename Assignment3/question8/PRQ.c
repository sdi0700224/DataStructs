#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "PRQ.h"


typedef struct PriorityTag *PriorityPointer;

static PriorityPointer PQ = NULL;

typedef struct EdgeTag
{
	Vertex start;
	Vertex end;
	int weight;
}EdgeNode;

typedef struct PriorityTag
{
	int Count;
	PQArray ItemArray;
} PriorityQueue;


void Swap(PQItem *a, PQItem *b)	//Swaps values
{
	PQItem temp;
	temp = *a;
	*a = *b;
	*b = temp;
}


void Heapify(PQArray A, int j)	//Makes a Heap again after extraction of Item for PQ
{
	int i = j + 1;	//Simpler Code with this variable
	int left_child = 2 * i;
	int right_child = (2 * i) + 1;
	int min;

	if ((left_child <= PQ->Count) && (A[left_child - 1]->weight < A[i - 1]->weight))	//if we are inside array and left child > parent
	{
		min = left_child;	//make left child temp max
	}
	else
	{
		min = i;	//else parent is temp max
	}
	if ((right_child <= PQ->Count) && (A[right_child - 1]->weight < A[min - 1]->weight))	//if we are inside array and right child > temp max
	{
		min = right_child;	//Becomes new max
	}
	if (min != i)	//If a child is > parent
	{
		Swap(&A[i-1], &A[min-1]);	//Swap parent and child values
		Heapify(A, (min-1));	//Do the same with next child until no child > than parrent or array finishes
	}

}


void PrQInitialize(void)
{
	PQ = malloc(sizeof(PriorityQueue));
   	PQ->Count = 0;
}


int Empty(void)
{
  	if(PQ->Count == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


int Full(void)
{
	if(PQ->Count >= MAXCOUNT)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void Insert(PQItem Item)
{
	int i;
	if (Full() != 1) 
	{
		PQ->Count++;
		PQ->ItemArray[PQ->Count-1]=Item;	//Insert last
		i = PQ->Count;
		while((i > 1) && (PQ->ItemArray[(i/2) - 1]->weight > PQ->ItemArray[(i-1)]->weight))	//if we are inside array and child is bigger than parent
		{
			Swap(&PQ->ItemArray[(i/2) - 1], &PQ->ItemArray[(i-1)]);	//Swap values
			i = i / 2;		//Check for next child
		}
	}
	else
	{
		printf("Error! Heap overflow!");
	}
}


PQItem Remove(void)
{
	PQItem min;

	if (Empty() != 1)
	{
		min = PQ->ItemArray[0];	//max is the first item
		PQ->ItemArray[0] = PQ->ItemArray[(PQ->Count - 1)];	//Last element becomes first
		PQ->Count--;
		Heapify(PQ->ItemArray, 0);	//Make a Heap again by begining from start of array
		return min;
	}
	else
	{
		printf("Error! Heap underflow!");
		return NULL;
	}
}


PQItem NewNode(Vertex start, Vertex end, int weight) //Creates a New Node for the PQ
{
	PQItem Temp;
	Temp = malloc(sizeof(EdgeNode));
	Temp->start = start;
	Temp->end = end;
	Temp->weight = weight;
	return Temp;
}

int GetVertex(PQItem CurEdge, int x)
{
	if(x == 1)
	{
		return CurEdge->start;
	}
	else
	{
		return CurEdge->end;
	}
}

void PrintPQArr(PQItem Array[], int size)
{
	int weightcount=0;

	printf("MST: ");
	for(int i=0; i < size; i++)
	{
		printf("(%d, %d, %d) ", Array[i]->start, Array[i]->end, Array[i]->weight);
		weightcount += Array[i]->weight;
	}
	printf("\nTotal MST weight: %d\n\n", weightcount);
}


void EndPQ(void)
{
	for(int i=0; i<PQ->Count; i++)
	{
		free(PQ->ItemArray[i]);
	}
	free(PQ);
}