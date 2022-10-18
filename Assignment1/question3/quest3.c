#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maxrec.h"
#define MAX 15

int main(int argc, char *argv[])
{
	int x;

	srand(time(NULL));
	for(int i=0; i<= MAX; i++)	//Fill with random values
	{
		AddFist(&Head, (rand()%1000));
	}
	Print(Head);	//Print Lists
	x = maxrec(Head);	//Find max
	printf("List max is: %d\n", x);		//print max
	Destroy(&Head);
	return 0;
}


void AddFist(ListPointer *Headaddr, int v)	/*Adds a new Node at Head*/
{
	ListPointer Temp;
	Temp = malloc(sizeof(ListType));
	Temp-> value = v;
	Temp->next = *Headaddr;
	(*Headaddr) = Temp;	
}


void Destroy(ListPointer *Headaddr) // Destroys List and frees all nodes
{
	ListPointer Temp;
	while (*Headaddr != NULL)
	{
		Temp = *Headaddr;
		*Headaddr = (*Headaddr)->next;
		free(Temp);
	}
}


void Print(ListPointer Head)	/*Prints List from Head to Tail*/
{
	ListPointer TempHead = Head;
	printf("[ ");
	while (TempHead != NULL)
	{
		printf("(");
		printf("%d", TempHead->value);
		printf(") ");
		TempHead = TempHead->next;
	}
	printf("]\n");
}