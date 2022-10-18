#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "PRQ.h"


void PriorityQueueSort(PQArray A)
{
	int i;

	Initialize();
	for (i=0; i<MAXCOUNT; ++i) 
	{
		Insert(A[i]);
	}
	for (i=MAXCOUNT-1; i>=0; --i) 
	{
		A[i]=Remove();
	}
	EndPQ(); //Destroy PQ
}


int main(int argc, char *argv[])
{
	int i; 
	PQArray A;

	srand(time(NULL));
	for (i=0; i<MAXCOUNT; ++i)
	{
		A[i]= ((rand()) % (10 * MAXCOUNT));	//Insert random numbers in array
		printf("%d ",A[i]);	//Print the at the same time
	}
	printf("\n");

	PriorityQueueSort(A);	//Sort array using a PQ

	for (i=0; i<MAXCOUNT; ++i) //Print sorted array
	{
		printf("%d ",A[i]);
	}
	printf("\n");
}