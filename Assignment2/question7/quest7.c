#include <stdio.h>
#include <stdlib.h>
#include "ST.h"


int main(int argc, char *argv[])
{ 
	int N, maxN = atoi(argv[1]);
    Item v;
	ST Table1=NULL;
	ST Table2=NULL;

    Table1 = STinit();	//ST 1
    for(N = 0; N < maxN; N++)	//Put Random Items
	{
		v = ITEMrand();
		STinsert(Table1, v);
	}
	printf("\n");
    STsort(Table1, ITEMshow); 	//Print them
	printf("\n");
    printf("%d keys\n", STcount(Table1));	//Count them

	Table2 = STinit();	//Same for ST 2
    for(N = 0; N < maxN; N++)
	{
		v = ITEMrand();
		STinsert(Table2, v);
	}
	printf("\n");
    STsort(Table2, ITEMshow); 
	printf("\n");
    printf("%d keys\n", STcount(Table2));

	v = STselect(Table2, 7); //Select no 7
	ITEMshow(v);	//Print it

	for(N = 0; N < 5; N++)	//Generate items with specific key
	{
		v = ITEMgen(1000);
		STinsert(Table2, v);
	}
	printf("\n");
    STsort(Table2, ITEMshow); 
	printf("\n");
    printf("%d keys\n", STcount(Table2));

	STdelete(Table2, 1000);	//Delete only one with key 1000
	printf("\n");
    STsort(Table2, ITEMshow); 
	printf("\n");
    printf("%d keys\n", STcount(Table2));

	v = STsearch(Table2, 1000);	//Search for item with key 1000
	ITEMshow(v);

	STdeleteAll(Table2, 1000);	//Delete all with key 1000
	printf("\n");
    STsort(Table2, ITEMshow); 
	printf("\n");
    printf("%d keys\n", STcount(Table2));


	STend(Table1);	//Destroy STs
	STend(Table2);
	return 0;
}
