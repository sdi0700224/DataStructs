#include <stdio.h>
#include <stdlib.h>
#include "maxrec.h"

int maxrec(ListPointer Head)
{
	int max = 0;
	if (Head == NULL)	//If no more Nodes return 0
	{
		return 0;
	}
	max = maxrec(Head->next);	//max of all next Nodes
	if (Head->value > max)		//if is > than current Node Value replace
	{
		max = Head->value;
	}
	return max;	//return max
}