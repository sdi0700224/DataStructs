#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "STACK.h"
#include "PQ.h"
#include "STACKImpl.h"


StackPointer NEW(Item item, StackPointer next)
{ 	
	StackPointer x = malloc(sizeof *x);
	x->item = item; x->next = next;
	return x;
}


void STACKinit(int maxN, StackPointer *head)
{ 
	*head = NULL; 
}


int STACKempty(StackPointer head)
{ 
	return head == NULL; 
}


int STACKpush(Item item, StackPointer *head)
{ 	
	*head = NEW(item, *head);
    return 1;
}


Item STACKpop(StackPointer *head)
{ 
	Item item = (*head)->item;
    StackPointer t = (*head)->next;
    free(*head); 
	*head = t;
    return item;
}
  

void ReadStateArray(StateArray CubeStacks, char *argv) //Reads a state from arguments and fills a StateArray
{
	int i=0, j=0;
	char ch;

	for(int k=0; k<MAXCUBES; k++)
	{
		STACKinit(MAXCUBES, &CubeStacks[k]);
	}
	ch = *argv;
	while(ch != '\0')
	{
		ch = *(argv + i);
		if(isalpha(ch) != 0)	//if it's a cube
		{
			STACKpush(ch, &CubeStacks[j]);
		}
		else if(ch == ',') //Next Stack
		{
			j++;
		}
		i++;
	}
	PriorityQueueSort(CubeStacks); //Sort Stack Pointers
}


void FreeStateArray(StateArray CubeStacks) //Free a StateArray
{
	for(int k=0; k<MAXCUBES; k++)
	{
		while(STACKempty(CubeStacks[k]) != 1)
		{
			STACKpop(&CubeStacks[k]);
		}
	}
}


int StackCompare(StackPointer StateStack, StackPointer GoalStack) //Compare two Stacks, if the are the same return 1
{
	int flag = 1;

	while((StateStack != NULL) && (GoalStack != NULL))
	{
		if(StateStack->item != GoalStack->item)
		{
			flag = 0;
			break;
		}
		StateStack = StateStack->next;
		GoalStack = GoalStack->next;
	}
	if(((StateStack == NULL) && (GoalStack != NULL)) || ((StateStack != NULL) && (GoalStack == NULL)))
	{
		flag = 0;
	}
	return flag;
}


void STACKcopy(StackPointer *In, StackPointer *Target) //Copy a Stack
{
	StackPointer Temp=NULL;
	Item Char;

	while(*In != NULL)
	{
		Char = STACKpop(In);
		STACKpush(Char, &Temp);
	}
	while(Temp != NULL)
	{
		Char = STACKpop(&Temp);
		STACKpush(Char, In);
		STACKpush(Char, Target);
	}
}


Item GetLastItem(StackPointer Pointer)	//Get the value of the Cube touching the floor
{
	StackPointer StackH = Pointer;
	if(StackH == NULL)
	{
		return '\0';
	}
	while(StackH->next != NULL)
	{
		StackH = StackH->next;
	}
	return StackH->item;
}


void StackReverse(StackPointer *StackP)	//Reverse a Stack, maybe for future use
{
	StackPointer Temp=NULL;
	Item ch;

	while(*StackP != NULL)
	{
		ch = STACKpop(StackP);
		STACKpush(ch, &Temp);
	}
	*StackP = Temp;
}