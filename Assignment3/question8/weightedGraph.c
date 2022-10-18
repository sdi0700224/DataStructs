#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "weightedGraph.h"
#include "PRQ.h"

typedef struct graph Graph;
typedef struct edge Edge;

typedef struct edge 
{
   	Vertex endpoint;
	int weight;
   	struct edge *nextedge;
}Edge;

typedef struct graph 
{
   	int n;     // number of vertices in the graph
	int e;
   	Edge *firstedge[MAXVERTEX];
}Graph;



void Initialize(G *G, int x)
{
	*G = malloc(sizeof(Graph));
	(*G)->n = x;
	(*G)->e = 0;
	for(int i=0; i < (*G)->n; i++)
	{
		(*G)->firstedge[i] = NULL;
	}

	PrQInitialize();
}


void InsertEdge(Vertex From, Vertex To, int Weight, G G)
{
	E Temp = G->firstedge[From], TempPrev = NULL, Temp2 = NULL;
	PQItem NewEdge = NULL;

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
		Temp2->weight = Weight;
		Temp2->nextedge = Temp;
		G->firstedge[From] = Temp2;
	}
	else
	{
		Temp2 = malloc(sizeof(Edge));
		Temp2->endpoint = To;
		Temp2->weight = Weight;
		Temp2->nextedge = TempPrev->nextedge;
		TempPrev->nextedge = Temp2;
	}
	G->e++;

	NewEdge = NewNode(From, To, Weight);
	Insert(NewEdge);
}


void ShowGraph(G G)
{
	E Temp;
	Vertex Lists[G->n];
	int Weights[G->n];
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
			Weights[count] = Temp->weight;
			count++;
			Temp = Temp->nextedge;
		}
		printf("Count: %d\t Adjacency List:  ", count);
		for(int i=0; i < count; i++)
		{
			printf("(%d,%d) ", Lists[i], Weights[i]);
		}
		printf("\n");
	}
	printf("\n");
}

int SameSubset(Vertex p, Vertex q, int id[], int sz[])
{
	int i, j;

	for(i=p; i != id[i]; i=id[i])
	{
		id[i] = id[id[i]];
	}
	for(j=q; j != id[j]; j=id[j])
	{
		id[j] = id[id[j]];
	}

	if(i == j)
	{
		return 1;
	}

	if(sz[i] < sz[j])
	{
		id[i] = j;
		sz[j] += sz[i];
	}
	else
	{
		id[j] = i;
		sz[i] += sz[j];
	}

	return 0;
}

void MinimumSpanningTree(G G)
{
	int i, id[G->n], sz[G->n];
	PQItem MST[G->n-1], CycleEdges[G->n*(G->n-1)], CurEdge=NULL;
	int mstcount=0, cyclecount=0, x;

	for(i=0; i< G->n; i++)
	{
		id[i] = i;
		sz[i] = 1;
	}

	while(mstcount < (G->n-1))
	{
		CurEdge = Remove();

		x = SameSubset(GetVertex(CurEdge, 1), GetVertex(CurEdge, 2), id, sz);
		
		if(x == 0)
		{
			MST[mstcount] = CurEdge;
			mstcount++;
		}
		else
		{
			CycleEdges[cyclecount] = CurEdge;
			cyclecount++;
		}
	}

	PrintPQArr(MST, mstcount);

	for(int i=0; i < mstcount; i++)
	{
		Insert(MST[i]);
	}
	for(int i=0; i < cyclecount; i++)
	{
		Insert(CycleEdges[i]);
	}
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

	EndPQ();
}