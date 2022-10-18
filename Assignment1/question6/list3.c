#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list3.h"


typedef struct NodeTag 
{
   Number number;
   NodePointer link;
} NodeType;


void InsertNewLastNode(Number A, NodeType **L)
{
	NodeType *N, *P;

	N=(NodeType *)malloc(sizeof(NodeType));
	N->number = A;
	N->link=NULL;

	if (*L == NULL) {
		*L=N;
	} else {
		P=*L;
		while (P->link != NULL) P=P->link;
		P->link=N;
	}

}



void PrintList(NodeType *L)
{
	NodeType *N;

	printf("(");
	N=L;
	while(N != NULL) {
		printf("%d", N->number);
		N=N->link;
		if (N!=NULL) printf(",");
	}
	printf(")\n");
}


void DeleteLastNode(NodeType **L)
{
	NodeType *PreviousNode, *CurrentNode;

	if (*L != NULL) {
		if ((*L)->link == NULL){
		free(*L);
		*L=NULL;
		} else {
		PreviousNode=*L;
		CurrentNode=(*L)->link;
		while (CurrentNode->link != NULL){
			PreviousNode=CurrentNode;
			CurrentNode=CurrentNode->link;
		}
		PreviousNode->link=NULL;
		free(CurrentNode);
		}
	}
}


void InsertNewSecondNode (NodeType **L)
{
	NodeType *N;
	N=(NodeType *)malloc(sizeof(NodeType));
	N->number = 30;
	N->link=(*L)->link;
	(*L)->link=N;
}



NodeType *ListSearch(Number A, NodeType *L)
{
	NodeType *N;

	N=L;
	while (N != NULL){
	if (N->number == A){
		return N;
	} else {
		N=N->link;
	}
	}
	return N;
}

void InsertListSort (NodePointer *L)	//Sorting a List using Insertion Sort
{
	NodePointer Head, HeadPrev, TempHead, TempHeadPrev;
	int temp;

	Head = *L;	//To keep Original Head as it is
	if(Head != NULL)
	{
		Head = Head->link;	//Keep the address of the previous node also
		HeadPrev = *L;
	}
	while(Head != NULL)
	{
		temp = Head->number;
		TempHead = *L;	//We start from the beggining every time
		TempHeadPrev = NULL;	//Same here keep this previous also
		while((TempHead != NULL) && (temp >= TempHead->number))	//Be inside List and current Node value > than the Node from the beggining
		{
			if(TempHead == Head)	//No need to go further than current Node
			{
				break;
			}
			TempHeadPrev = TempHead;
			TempHead = TempHead->link;
		}
		if(TempHead != Head)	//If value was lesser than already sorted Nodes
		{
			HeadPrev->link = Head->link;	//Bypass the Node
			Head->link = TempHead;	//Make it point to the next bigger value Node
			if (TempHeadPrev == NULL)	//Make previous, lesser value Node point to current Node
			{
				*L = Head;
			}
			else
			{
				TempHeadPrev->link = Head;
			}
			Head = HeadPrev->link;
		}
		else
		{
			HeadPrev = Head;
			Head = Head->link;
		}
	}
	return;
}
