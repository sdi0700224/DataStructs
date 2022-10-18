#include <stdio.h>
#include <stdlib.h>
#include "weightedGraph.h"


int main(int argc, char *argv[])
{
	G G = NULL;
	int x, y, w, size;
	FILE *fp;
	char *input = NULL;
	size_t len_max = 0;

	if(argc != 2)
	{
		printf("Error! Graph argument is not present!\n");
		return -1;
	}
	fp = fopen(argv[1], "r");

	getline(&input, &len_max, fp);
	size = atoi(input);
	if(size > MAXVERTEX)
	{
		printf("Max graph size allowed is %d\n", MAXVERTEX);
		return -1;
	}
	else if(size <= 0)
	{
		printf("Graph size must be a positive integer\n");
		return -1;
	}
	Initialize(&G, size);

	while(getline(&input, &len_max, fp) != -1)
	{
		x = atoi(&(*(input)));
		y = atoi(&(*(input + 2)));
		w = atoi(&(*(input + 4)));
		InsertEdge(x, y, w, G);
	}
	fclose(fp);
	free(input);

	printf("\n");
	ShowGraph(G);

	MinimumSpanningTree(G);

	Destroy(G);
	return 0;
}