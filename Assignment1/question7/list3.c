#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list3.h"

/* The code is from Chapter 2 of the book "Data Structures, Algorithms and Software Principles in C" */

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

void InsertListSort (NodePointer *L)
{
	NodePointer Head, HeadPrev, TempHead, TempHeadPrev;
	int temp;

	Head = *L;
	if(Head != NULL)
	{
		Head = Head->link;
		HeadPrev = *L;
	}
	while(Head != NULL)
	{
		temp = Head->number;
		TempHead = *L;
		TempHeadPrev = NULL;
		while((TempHead != NULL) && (temp >= TempHead->number))
		{
			if(TempHead == Head)
			{
				break;
			}
			TempHeadPrev = TempHead;
			TempHead = TempHead->link;
		}
		if(TempHead != Head)
		{
			HeadPrev->link = Head->link;
			Head->link = TempHead;
			if (TempHeadPrev == NULL)
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

NodePointer MergeAndSort(NodePointer *L, NodePointer *K)	//Takes 2 Lists and merges them, after the two lists are empty
{															//and only the new one exists
	NodePointer LHead, KHead, NHead=NULL, NTemp;

	InsertListSort(L); //Merge each list
	InsertListSort(K);
	LHead = *L;	//Keep Original Head untouched for now
	KHead = *K;
	if(LHead == NULL)	//if one is empty just return the other
	{
		*K = NULL;
		return KHead;
	}
	if(KHead == NULL)
	{
		*L = NULL;
		return LHead;
	}
	if (LHead->number <= KHead->number) // Take Node with lesser value as Head
	{
		NHead = LHead;
		LHead = LHead->link;
		NHead->link = NULL;
	}
	else
	{
		NHead = KHead;
		KHead = KHead->link;
		NHead->link = NULL;
	}
	NTemp = NHead;
	while((LHead != NULL) || (KHead != NULL)) //One List is not empty
	{
		if(LHead == NULL) 	//if one is empty just return the rest
		{
			NHead->link = KHead;
			*L = LHead;
			*K = NULL;
			return NTemp;
		}
		if(KHead == NULL)	//Same
		{
			NHead->link = LHead;
			*L = NULL;
			*K = KHead;
			return NTemp;
		}
		if (LHead->number <= KHead->number)	//Else take the smaller everytime
		{
			NHead->link = LHead;
			LHead = LHead->link;
			NHead = NHead->link;
			NHead->link = NULL;
		}
		else
		{
			NHead->link = KHead;
			KHead = KHead->link;
			NHead = NHead->link;
			NHead->link = NULL;
		}
	}
	*L = LHead;
	*K = KHead;
	return NTemp;
}