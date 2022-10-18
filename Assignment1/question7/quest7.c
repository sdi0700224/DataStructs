#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "list3.h"
#define MAX 15


int main(void)
{
	NodePointer L, K, N;
	int x, y;

	L=NULL;
	K=NULL;
	N=NULL;
	
	PrintList(L);
	PrintList(K);
	srand(time(NULL));	//Create random numbers
	x = rand() % MAX;
	y = rand() % MAX;
	while(x <= 0)
	{
		x = rand() % MAX;
	}
	while(y <= 0)
	{
		y = rand() % MAX;
	}
	for(int i=0; i<=x; i++)
	{
		InsertNewLastNode((rand()%(10*x)), &L);	//Fill list with random numbers
	}
	PrintList(L);	//Print it
	for(int i=0; i<=y; i++)
	{
		InsertNewLastNode((rand()%(10*y)), &K);	//Also here
	}
	PrintList(K);	//Print it
	N = MergeAndSort(&L, &K);	//Merge them into one list
	PrintList(L);
	PrintList(K);
	PrintList(N); //Print new list
	while (N != NULL)	//Destroy New List
	{
		DeleteLastNode(&N);
	}
}