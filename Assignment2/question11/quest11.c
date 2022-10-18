#include <stdio.h>
#include <stdlib.h>
#include "ST.h"


int main(int argc, char *argv[])
{ 
	int N, maxN = atoi(argv[1]), x;
    Item item;
	ST Table1=NULL;

    Table1 = STinit();	//Initialize ST
    for(N = 0; N < maxN; N++)	//Fill it
	{
		item = ITEMrand();
		if(!STinsert(Table1, item))
		{
			FreeItem(item);
		}
	}
	printf("\n");	//Print keys and info
    STsort(Table1, ITEMshow); 
	printf("\n");
    printf("%d keys\n", STcount(Table1));

	item = STselect(Table1, 5);	//Select key with index 5
	ITEMshow(item);	//Print it

	x = GetKey(item);	//Save it's key
	item = STsearch(Table1, x);		//Search it with key now
	ITEMshow(item);	//Print it again

	STdelete(Table1, x);	//Delete this key
	printf("\n");			//Print again
	STsort(Table1, ITEMshow); 
	printf("\n");
    printf("%d keys\n", STcount(Table1));

	
	STend(Table1);	//Destroy all
	return 0;
}