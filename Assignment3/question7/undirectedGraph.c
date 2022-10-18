#include <stdio.h>
#include <stdlib.h>
#include "undirectedGraph.h"

typedef struct edge Edge;

typedef struct edge 
{
   	Vertex endpoint;
   	struct edge *nextedge;
}Edge;

typedef struct graph 
{
   	int n;     // number of vertices in the graph
   	Edge *firstedge[MAXVERTEX];
}Graph;



void Initialize(G *G, int x)
{
	*G = malloc(sizeof(Graph));
	(*G)->n = x;
	for(int i=0; i < (*G)->n; i++)
	{
		(*G)->firstedge[i] = NULL;
	}
}


void InsertEdge(Vertex From, Vertex To, G G)
{
	E Temp = G->firstedge[From], TempPrev = NULL, Temp2 = NULL;
	Vertex A;

	if(From == To)
	{
		printf("Loops are not allowed\n");
		return;
	}
	while(Temp != NULL && To > Temp->endpoint)
	{
		TempPrev = Temp;
		Temp = Temp->nextedge;
	}

	if(Temp != NULL && Temp->endpoint == To)
	{
		printf("This edge is already existent in given Graph\n");
		return;
	}

	if(TempPrev == NULL)
	{
		Temp2 = malloc(sizeof(Edge));
		Temp2->endpoint = To;
		Temp2->nextedge = Temp;
		G->firstedge[From] = Temp2;
	}
	else
	{
		Temp2 = malloc(sizeof(Edge));
		Temp2->endpoint = To;
		Temp2->nextedge = TempPrev->nextedge;
		TempPrev->nextedge = Temp2;
	}

	A = From;
	From = To;
	To = A;

	Temp = G->firstedge[From];
	TempPrev = NULL;

	while(Temp != NULL && To > Temp->endpoint)
	{
		TempPrev = Temp;
		Temp = Temp->nextedge;
	}

	if(TempPrev == NULL)
	{
		Temp2 = malloc(sizeof(Edge));
		Temp2->endpoint = To;
		Temp2->nextedge = Temp;
		G->firstedge[From] = Temp2;
	}
	else
	{
		Temp2 = malloc(sizeof(Edge));
		Temp2->endpoint = To;
		Temp2->nextedge = TempPrev->nextedge;
		TempPrev->nextedge = Temp2;
	}
}


void ShowGraph(G G)
{
	E Temp;
	Vertex Lists[G->n];
	int count;

	for(int i=0; i < G->n; i++)
	{
		count = 0;
		for(int i=0; i < G->n; i++)
		{
			Lists[i] = -1;
		}
		printf("Vertex: %d\t", i);
		Temp = G->firstedge[i];
		while(Temp != NULL)
		{
			Lists[count] = Temp->endpoint;
			count++;
			Temp = Temp->nextedge;
		}
		printf("Count: %d\t Adjacency List:  ", count);
		for(int i=0; i < count; i++)
		{
			printf("%d ", Lists[i]);
		}
		printf("\n");
	}
	printf("\n");
}


void BreadthFirstSearch(G G, Vertex A)
{
	BreadthFirst(*G, PrintElement, A);
}


int IsConnected(G G)
{
	return BreadthFirstConnected(*G);
}


void ShortestPaths(G G, Vertex A)
{
	BreadthFirstShortest(*G, A);
}


void ConnectedComponents(G G)
{
	BreadthFirstComponents(*G);
}


void Destroy(G G)
{
	E Temp;

	for(int i=0; i < G->n; i++)
	{
		while(G->firstedge[i] != NULL)
		{
			Temp = G->firstedge[i];
			G->firstedge[i] = G->firstedge[i]->nextedge;
			free(Temp);
		}
	}
	free(G);
}