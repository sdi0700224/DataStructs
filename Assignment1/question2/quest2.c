#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DListInterface.h"

int main(int argc, char *argv[])
{
	int x;
	DlistPointer tempnode, tempnode2;

	Create();

	x = IsEmpty();		//IsEmpty function use
	if (x == 1)
	{
		printf("List is empty\n\n");
	}
	else
	{
		printf("List is not empty\n\n");
	}

	tempnode = NewNode("John", 15);		//Create new Node to test List
	AddFirst(tempnode);	//Test AddFirst

	tempnode = NewNode("Sue", 19);	//same
	AddFirst(tempnode);

	tempnode = NewNode("Mary", 13);	//Here we test AddLast
	AddLast(tempnode);

	Print();	//And we print to see if all is ok

	x = Size();		//Test Size here
	printf("List size is: %d\n\n", x);

	tempnode = NewNode("Kostas", 18);

	tempnode2 = GetLast();

	AddAfter(tempnode, tempnode2);
	Print();

	x = Size();	//Test Size again
	printf("List size is: %d\n\n", x);

	x = IsEmpty();	//And Is Empty with no Empty List
	if (x == 1)
	{
		printf("List is empty\n\n");
	}
	else
	{
		printf("List is not empty\n\n");
	}

	Remove(tempnode2);	//Tets Remove and Print
	Print();

	x = Size();	//Test Size again
	printf("List size is: %d\n\n", x);

	tempnode2 = GetFirst();
	tempnode = NewNode("Steve", 20);	//Add a new Node
	AddAfter(tempnode, tempnode2);
	Print();

	tempnode2 = GetNext(tempnode2);	//Test GetNext
	printf("Node data is: (%s, %d)\n\n", GetName(tempnode2), GetValue(tempnode2));

	tempnode2 = GetPrev(tempnode2);	//Test GetPrev
	printf("Node data is: (%s, %d)\n\n", GetName(tempnode2), GetValue(tempnode2));

	tempnode = NewNode("Giannis", 18);	//Add new and Print
	AddBefore(tempnode, tempnode2);
	Print();
	x = Size();
	printf("\n%d\n", x);

	while (Size() > 0)	//Empty List here using Remove
	{
		Remove(GetFirst());
	}
	EndList();	//Destroy List
	return 0;
}