#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "list3.h"
#define MAX 25

int main(void)
{
	NodePointer L;

	L=NULL;
	srand(time(NULL));
	PrintList(L);
	for(int i=0; i<=MAX; i++)
	{
		InsertNewLastNode((rand() % (10*MAX)), &L);	//Fill List with random numbers
	}
	PrintList(L);	//Print it
	InsertListSort(&L); //Sort
	PrintList(L);	//And Print again
	while (L != NULL)	//Destroy list
	{
		DeleteLastNode(&L);
	}
}