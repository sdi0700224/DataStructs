#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <math.h>
#include "PRQ.h"
#include "STACK.h"
#include "STACKImpl.h"
#include "PQ.h"

//#define FAST


extern char GoalCubes[MAXCUBES];
extern char GoalStand[MAXCUBES];


typedef struct StateTag
{
	int f;
	int g;
	int h;
	char moves[1000];
	StateArray CubeStacks;
} StateNode;


typedef struct PriorityTag
{
   int Count;
   PQArray ItemArray;
} PriorityQueue;


void Swap(PQItem *a, PQItem *b)
{
	PQItem temp;
	temp = *a;
	*a = *b;
	*b = temp;
}


void Heapify(PQArray A, int j, PriorityPointer PQ)
{
	int i = j + 1;
	int left_child = 2 * i;
	int right_child = (2 * i) + 1;
	int min;

	if ((left_child <= PQ->Count) && (A[left_child - 1]->f < A[i - 1]->f))
	{
		min = left_child;
	}
	else
	{
		min = i;
	}
	if ((right_child <= PQ->Count) && (A[right_child - 1]->f < A[min - 1]->f))
	{
		min = right_child;
	}
	if (min != i)
	{
		Swap(&A[i-1], &A[min-1]);
		Heapify(A, (min-1), PQ);
	}

}


void Initialize(PriorityPointer *PQ)
{
	*PQ = malloc(sizeof(PriorityQueue));
   	(*PQ)->Count = 0;
}


int Empty(PriorityPointer PQ)
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


int Full(PriorityPointer PQ)
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


void Insert(PQItem Item, PriorityPointer PQ)
{
	int i;
	if (Full(PQ) != 1) 
	{
		PQ->Count++;
		PQ->ItemArray[PQ->Count-1]=Item;
		i = PQ->Count;
		while((i > 1) && (PQ->ItemArray[(i/2) - 1]->f > PQ->ItemArray[(i-1)]->f))
		{
			Swap(&PQ->ItemArray[(i/2) - 1], &PQ->ItemArray[(i-1)]);
			i = i / 2;
		}
	}
	else
	{
		printf("Error! Heap overflow!");
	}
}


PQItem Remove(PriorityPointer PQ)
{
	PQItem max;

	if (Empty(PQ) != 1)
	{
		max = PQ->ItemArray[0];
		PQ->ItemArray[0] = PQ->ItemArray[(PQ->Count - 1)];
		PQ->Count--;
		Heapify(PQ->ItemArray, 0, PQ);
		return max;
	}
	else
	{
		printf("Error! Heap underflow!");
		return NULL;
	}
}


PQItem NewNode(StateArray Node, int g, int h) //Creates a New Node for the PQ
{
	PQItem Temp;
	Temp = malloc(sizeof(StateNode));
	Temp->g = g;
	Temp->h = h;
	Temp->f = Temp->g + Temp->h;
	for (int i=0; i<MAXCUBES; i++)
	{
		Temp->CubeStacks[i] = Node[i];
	}
	return Temp;
}


int GetNodeVal(PQItem Node) //Returns f
{
	return Node->f;
}


void FreeState(PQItem State) //Frees StateNode
{
	FreeStateArray(State->CubeStacks);
	free(State);
}


StackPointer* GetArray(PQItem State) //Returns a States Array
{
	return State->CubeStacks;
}


void NewStateInsert(PQItem State, PriorityPointer PQ, int j) //Make a State's Copy and puts it in PQ
{
	PQItem NewState;

	NewState = malloc(sizeof(StateNode));
	for(int i=0; i<MAXCUBES; i++) //Copy State Array
	{
		STACKinit(MAXCUBES, &NewState->CubeStacks[i]);
		STACKcopy(&State->CubeStacks[i], &NewState->CubeStacks[i]);
	}
	NewState->moves[2*(State->g)] = NewState->CubeStacks[j]->item; //Copy moves
	if(NewState->CubeStacks[j]->next != NULL)
	{
		NewState->moves[(2*State->g) + 1] = NewState->CubeStacks[j]->next->item;
	}
	else
	{
		NewState->moves[(2*State->g) + 1] = '_';
	}
	for(int i=0 ; i<(2*State->g); i++)
	{
		NewState->moves[i]= State->moves[i];
	}
	PriorityQueueSort(NewState->CubeStacks);	//Sort Array Stack Pointers
	NewState->g = State->g + 1;	//Increase g
	#ifdef FAST
		HCalc2(NewState);     	//Hill Climbing - not admisible but very fast
	#else
		HCalc(NewState); //Admisible, penalty for wrong place, plus double move penalty for right placed cube above wrong placed cube
	#endif 
	NewState->f = NewState->g + NewState->h;	//Calculate g
	Insert(NewState, PQ);	//And finilly insert it in PQ
}

int addcalc(int n)
{
    if (n <= 1)
	{
        return 0;
	}
    return (n-1) + addcalc(n-1);
}


// Fast and works with a lot of cubes, but overestimates cost and heuritic is not admisible and thus solution is NOT always optimal!
// Very close to optimal thought

void HCalc2(PQItem State)
{
	char ch, chprev;
	StackPointer Temp;
	int totalcount=0, stackcount, pos, diff, k;

	for(int i=0; i<MAXCUBES; i++)
	{
		stackcount = 0;
		pos = 0;
		Temp = State->CubeStacks[i];
		while(Temp != NULL)
		{
			stackcount++;
			ch = Temp->item;
			if(Temp->next != NULL)
			{
				chprev = Temp->next->item; 	//Here it's the opposite because it's a Stack
			}								//Stacks next is the previous
			else
			{
				chprev = '_';	//If there is no next previous is the Table
			}
			for(k=0; k<MAXCUBES; k++)
			{
				if(GoalCubes[k] == ch)	//Find the same Cube in Array
				{
					break;
				}
			}
			if(chprev != GoalStand[k])	//If it's standing in the wrong Cube change fault position
			{
				pos = stackcount;
			}
			Temp = Temp->next;
		}
		diff = stackcount - pos;
		totalcount += addcalc(stackcount) - (2*addcalc(diff)); //Hill climbing reversed implementation
	}
	State->h = totalcount;	//h is the total penalty points
}


void HCalc(PQItem State) //Same but without mutual prevention penalty
{
	char ch, chprev;
	StackPointer Temp;
	int stackcount, doublem, pos, k;
	int totalcount = 0;

	for(int i=0; i<MAXCUBES; i++)
	{
		doublem = 0;
		stackcount = 0;
		pos = 0;
		Temp = State->CubeStacks[i];
		while(Temp != NULL)
		{
			stackcount++;
			ch = Temp->item;
			if(Temp->next != NULL)
			{
				chprev = Temp->next->item; 	//Here it's the opposite because it's a Stack
			}								//Stacks next is the previous
			else
			{
				chprev = '_';	//If there is no next previous is the Table
			}
			for(k=0; k<MAXCUBES; k++)
			{
				if(GoalCubes[k] == ch)	//Find the same Cube in Array
				{
					break;
				}
			}
			if(chprev != GoalStand[k])	//If it's standing in the wrong Cube change fault position
			{
				totalcount += doublem;	//Cubes that must be moved twice penalty
				doublem = 0;
				pos = stackcount;
			}
			else
			{
				doublem++;
			}
			Temp = Temp->next;
		}
		totalcount += pos;	//Wrong placed cubes penalty
	}
	State->h = totalcount;	//h is the total penalty points
}



int GGet(PQItem State)	//Returns g
{
	return State->g;
}


void PrintMoves(PQItem State)	//Prints a States moves
{
	for(int i = 0; i<(2*State->g); i+=2)
	{
		printf("%c-->", State->moves[i]);
		printf("%c\n", State->moves[i+1]);
	}
}


void ArrayFill(char *GoalString)	//Takes Goal argument and fills the external Arrays
{
	char ch, chprev;
	int i=0;

	chprev = '_';
	while(*GoalString != '\0')
	{
		ch = *GoalString;
		if(isalpha(ch)) //if it's a cube
		{
			GoalCubes[i] = ch;
			if(!isalpha(chprev)) //if previous isn't aplha it sits on the table
			{
				GoalStand[i] = '_';
			}
			else
			{
				GoalStand[i] = chprev;
			}
			i++;
		}
		chprev = ch;
		GoalString++;
	}
}