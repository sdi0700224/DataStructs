#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "PRQ.h"

// PQ implementation is using a MAX Heap
// 'Εχει υπάρξει συνενόηση με τον Κ. Κουμπαράκη στο μάθημα για να υλοποιήσω την PQ με Heap 

typedef struct PriorityTag *PriorityPointer;

static PriorityPointer PQ = NULL;

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
	int max;

	if ((left_child <= PQ->Count) && (A[left_child - 1] > A[i - 1]))	//if we are inside array and left child > parent
	{
		max = left_child;	//make left child temp max
	}
	else
	{
		max = i;	//else parent is temp max
	}
	if ((right_child <= PQ->Count) && (A[right_child - 1] > A[max - 1]))	//if we are inside array and right child > temp max
	{
		max = right_child;	//Becomes new max
	}
	if (max != i)	//If a child is > parent
	{
		Swap(&A[i-1], &A[max-1]);	//Swap parent and child values
		Heapify(A, (max-1));	//Do the same with next child until no child > than parrent or array finishes
	}

}


void Initialize(void)
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
		while((i > 1) && (PQ->ItemArray[(i/2) - 1] < PQ->ItemArray[(i-1)]))	//if we are inside array and child is bigger than parent
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
	PQItem max;

	if (Empty() != 1)
	{
		max = PQ->ItemArray[0];	//max is the first item
		PQ->ItemArray[0] = PQ->ItemArray[(PQ->Count - 1)];	//Last element becomes first
		PQ->Count--;
		Heapify(PQ->ItemArray, 0);	//Make a Heap again by begining from start of array
		return max;
	}
	else
	{
		printf("Error! Heap underflow!");
		return INT_MIN;
	}
}


void EndPQ(void)
{
	free(PQ);
}