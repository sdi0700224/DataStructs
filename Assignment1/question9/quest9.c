#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "PRQ.h"
#include "STACK.h"


char GoalCubes[MAXCUBES];	//Array with all cubes
char GoalStand[MAXCUBES];	//Where every cube stands


int StateEval(PQItem, PriorityPointer, StateArray);
int StateCompare(StackPointer*, StateArray);


int main(int argc, char *argv[])
{
	PriorityPointer PQ;
	Initialize(&PQ);
	StateArray InitialState;
	StateArray Goal;
	PQItem State = NULL;

	ReadStateArray(InitialState, argv[1]);	//take args and make them a StateArray
	ReadStateArray(Goal, argv[2]);
	ArrayFill(argv[2]);	//Fill external arrays here

	Insert(NewNode(InitialState, 0, 0), PQ); //Make the initial State
	
	while(1 == 1)	//Keep loop until State = Goal
	{
		State = Remove(PQ);
		if(StateEval(State, PQ, Goal))
		{
			break;
		}
		FreeState(State);
	}
	#ifdef FAST
		printf("\nThe best solution that has been found includes %d moves.\n\n", GGet(State)); //Print number of moves of the solution
	#else
		printf("\nThe best solution includes %d moves.\n\n", GGet(State));
	#endif
	PrintMoves(State); //Print moves done to solve
	while(Empty(PQ) == 0)	//Destroy PQ and free it's contents
	{
		FreeState(Remove(PQ));
	}
	FreeState(State);
	FreeStateArray(Goal);
	free(PQ);
	return 0;
}


int StateEval(PQItem State, PriorityPointer PQ, StateArray Goal)
{
	Item Temp;
	int flag;

	if(StateCompare((GetArray(State)), Goal))	//If State = Goal we are done!
	{
		return 1;
	}
	for(int i=0; i<MAXCUBES; i++)
	{
		flag = 0;
		if(*(GetArray(State) + i) != NULL)
		{
			Temp = STACKpop((GetArray(State) + i));	//Pick up cube
			if(*(GetArray(State) + i) == NULL)	//If cube was on the floor
			{
				flag = 1;
			}
		}
		else
		{
			continue;
		}
		for(int j=0; j<MAXCUBES; j++)
		{
			if (j == i)	//If it's the same stack that we picked it up
			{
				continue;
			}
			if((*(GetArray(State) + j) == NULL) && (flag == 1))	//If cube was on the floor or was placed on the floor agian
			{
				continue;
			}
			if(*(GetArray(State) + j) == NULL)	//First time a cube placed on the floor
			{
				flag = 1;
			}
			STACKpush(Temp, (GetArray(State) + j));	//Place cube
			NewStateInsert(State, PQ, j);
			Temp = STACKpop((GetArray(State) + j));	//Return to cube being picked up
		}
		STACKpush(Temp, (GetArray(State) + i));	//Return to initial state to pick up a cube from other Stack in the next loop
	}
	return 0;
}


int StateCompare(StackPointer* StateArr, StateArray Goal) //Compares state with goal
{
	int flag = 1;
	for(int i = 0; i<MAXCUBES; i++)
	{
		if(StackCompare(*(StateArr + i), Goal[i]) == 0)	//Stacks are sorted by the cube on the floor
		{												//so if same State they will be in same order also
			flag = 0;
			break;
		}
	}
	return flag;
}