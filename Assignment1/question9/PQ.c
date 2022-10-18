#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "PQ.h"
#include "STACK.h"
#include "STACKImpl.h"


typedef struct PriorityTag2
{
   int Count2;
   PQArray2 ItemArray2;
} PriorityQueue2;


void Swap2(PQItem2 *a, PQItem2 *b)
{
	PQItem2 temp;
	temp = *a;
	*a = *b;
	*b = temp;
}


void Heapify2(PQArray2 A, int j, PriorityPointer2 PQ)
{
	int i = j + 1;
	int left_child = 2 * i;
	int right_child = (2 * i) + 1;
	int max;

	if ((left_child <= PQ->Count2) && (GetLastItem(A[left_child - 1]) > GetLastItem(A[i - 1])))
	{
		max = left_child;
	}
	else
	{
		max = i;
	}
	if ((right_child <= PQ->Count2) && (GetLastItem(A[right_child - 1]) > GetLastItem(A[max - 1])))
	{
		max = right_child;
	}
	if (max != i)
	{
		Swap2(&A[i-1], &A[max-1]);
		Heapify2(A, (max-1), PQ);
	}

}


void Initialize2(PriorityPointer2 *PQ)
{
	*PQ = malloc(sizeof(PriorityQueue2));
   	(*PQ)->Count2 = 0;
}


int Empty2(PriorityPointer2 PQ)
{
  	if(PQ->Count2 == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


int Full2(PriorityPointer2 PQ)
{
	if(PQ->Count2 >= MAXCUBES)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void Insert2(PQItem2 Item, PriorityPointer2 PQ)
{
	int i;
	if (Full2(PQ) != 1) 
	{
		PQ->Count2++;
		PQ->ItemArray2[PQ->Count2-1]=Item;
		i = PQ->Count2;
		while((i > 1) && (GetLastItem(PQ->ItemArray2[(i/2) - 1]) < GetLastItem(PQ->ItemArray2[(i-1)])))
		{
			Swap2(&PQ->ItemArray2[(i/2) - 1], &PQ->ItemArray2[(i-1)]);
			i = i / 2;
		}
	}
	else
	{
		printf("Error! Heap overflow!");
	}
}


PQItem2 Remove2(PriorityPointer2 PQ)
{
	PQItem2 max;

	if (Empty2(PQ) != 1)
	{
		max = PQ->ItemArray2[0];
		PQ->ItemArray2[0] = PQ->ItemArray2[(PQ->Count2 - 1)];
		PQ->Count2--;
		Heapify2(PQ->ItemArray2, 0, PQ);
		return max;
	}
	else
	{
		printf("Error! Heap underflow!");
		return NULL;
	}
}


void PriorityQueueSort(PQArray2 A) 	//Sorts Array by inserting non Null pointers to a second PQ
{									//Otherwise PQ will get seg fault during comparison
	int i, j=0;
	PriorityPointer2 PQ = NULL;

	Initialize2(&PQ);
	for (i=0; i<MAXCUBES; ++i) 
	{
		if(A[i] != NULL)	//If it has a Cube
		{
			Insert2(A[i], PQ);
		}
		else
		{
			j++;
		}
	}
	for (i=MAXCUBES-1-j; i>=0; --i)	//Remove as many as you got in
	{
		A[i]=Remove2(PQ);
	}
	for (i=MAXCUBES-1; i>=MAXCUBES-j; --i)	//make rest NULL
	{
		A[i]=NULL;
	}
	free(PQ);
}