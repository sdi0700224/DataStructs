#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "bfs.h"

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


// PrintElement: prints the value of its parameter x
void PrintElement(Vertex x)
{
  	printf("%d\n", x);
}


// BreadthFirst: breadth-first traversal of a graph
// Pre: The graph G has been created
// Post: The function visit has been performed at each vertex of G, where the vertices
// are chosen in breadth-first order.
// Uses: Queue functions

void BreadthFirst(Graph G, void (*Visit)(Vertex), Vertex A)
{
	Q Q;
	Boolean placed[MAXVERTEX];
	int Edges[MAXVERTEX][MAXVERTEX];
	Vertex v, u, w;
	Edge *curedge;

	for(v=0; v < G.n; v++)
	{
		placed[v]=FALSE;
		for(int i=0; i < G.n; i++)
		{
			Edges[v][i] = -1;
		}
	}
	Q = QUEUEinit();

	printf("Vertexes by visiting order:\n");
	for(u=A; u < G.n; u++)
	{
		if(!placed[u])
		{
			placed[u] = TRUE;
			QUEUEput(Q, u);
			do 
			{
				v = QUEUEget(Q);
	
				Visit(v);
				
				curedge=G.firstedge[v];  // curedge is a pointer to the first edge (v,_) of V
				while(curedge)
				{
					w=curedge->endpoint;  // w is a successor of v and (v,w) is the current edge
					if(!placed[w])
					{
						placed[w] = TRUE;	
						QUEUEput(Q, w);
						Edges[v][w] = 1;
						Edges[w][v] = 1;
					}
					else
					{
						if(Edges[v][w] == -1)
						{
							Edges[v][w] = 2;
							Edges[w][v] = 2;
						}	
					}
					curedge=curedge->nextedge;  // curedge is a pointer to the next edge (v,_) of V
				}
			}while(!QUEUEempty(Q));
		}
	}
	for(u=0; u < A; u++)
	{
		if(!placed[u])
		{
			placed[u] = TRUE;
			QUEUEput(Q, u);
			do 
			{
				v = QUEUEget(Q);
	
				Visit(v);
				
				curedge=G.firstedge[v];  // curedge is a pointer to the first edge (v,_) of V
				while(curedge)
				{
					w=curedge->endpoint;  // w is a successor of v and (v,w) is the current edge
					if(!placed[w])
					{
						placed[w] = TRUE;	
						QUEUEput(Q, w);
						//printf("Tree Edge: %d-->%d\n", v, w);
						Edges[v][w] = 1;
						Edges[w][v] = 1;
					}
					else
					{
						if(Edges[v][w] == -1)
						{
							//printf("Cross Edge: %d-->%d\n", v, w);
							Edges[v][w] = 2;
							Edges[w][v] = 2;
						}	
					}
					curedge=curedge->nextedge;  // curedge is a pointer to the next edge (v,_) of V
				}
			}while(!QUEUEempty(Q));
		}
	}
	printf("\n");
	printf("Tree Edges\n");
	for(int i=0; i < G.n; i++)
	{
		for(int j=0 ; j < G.n; j++)
		{
			if(Edges[i][j] == 1 && i>j)
			printf("(%d,%d)\n", i, j);
		}
	}
	printf("\n");
	printf("Cross Edges\n");
	for(int i=0; i < G.n; i++)
	{
		for(int j=0 ; j < G.n; j++)
		{
			if(Edges[i][j] == 2 && i>j)
			printf("(%d,%d)\n", i, j);
		}
	}
	printf("\n");
	QUEUEend(Q);
}



int BreadthFirstConnected(Graph G)
{
	Q Q;
	Boolean placed[MAXVERTEX];
	Vertex v, u, w;
	Edge *curedge;

	for(v=0; v < G.n; v++)
	{
		placed[v]=FALSE;
	}
	Q = QUEUEinit();

	for(u=0; u < G.n; u++)
	{
		if(!placed[u])
		{
			if(u > 0)
			{
				QUEUEend(Q);
				return 0;
			}
			placed[u] = TRUE;
			QUEUEput(Q, u);
			do 
			{
				v = QUEUEget(Q);

				curedge=G.firstedge[v];  // curedge is a pointer to the first edge (v,_) of V
				while(curedge)
				{
					w=curedge->endpoint;  // w is a successor of v and (v,w) is the current edge
					if(!placed[w])
					{
						placed[w] = TRUE;	
						QUEUEput(Q, w);
					}
					curedge=curedge->nextedge;  // curedge is a pointer to the next edge (v,_) of V
				}
			}while(!QUEUEempty(Q));
		}
	}
	QUEUEend(Q);
	return 1;
}


void BreadthFirstShortest(Graph G, Vertex A)
{
	Q Q;
	Boolean placed[MAXVERTEX];
	int ShortestPath[MAXVERTEX];
	Vertex v, w;
	Edge *curedge;

	for(v=0; v < G.n; v++)
	{
		placed[v]=FALSE;
		ShortestPath[v]=INT_MAX;
	}
	ShortestPath[A] = 0;
	Q = QUEUEinit();
	
	placed[A] = TRUE;
	QUEUEput(Q, A);
	do 
	{
		v = QUEUEget(Q);
		
		curedge=G.firstedge[v];  // curedge is a pointer to the first edge (v,_) of V
		while(curedge)
		{
			w=curedge->endpoint;  // w is a successor of v and (v,w) is the current edge
			if(!placed[w])
			{
				placed[w] = TRUE;
				ShortestPath[w] = ShortestPath[v] + 1;	
				QUEUEput(Q, w);
			}
			curedge=curedge->nextedge;  // curedge is a pointer to the next edge (v,_) of V
		}
	}while(!QUEUEempty(Q));

	printf("Shortest Paths from Vertex %d:\n", A);
	for(int i=0; i < G.n; i++)
	{
		if(ShortestPath[i] != INT_MAX)
		{
			printf("Vertex %d: %d\n", i, ShortestPath[i]);
		}
		else
		{
			printf("Vertex %d: -\n", i);
		}
	}
	printf("\n");
	QUEUEend(Q);
}


void BreadthFirstComponents(Graph G)
{
	Q Q;
	Boolean placed[MAXVERTEX];
	Vertex v, u, w;
	Edge *curedge;
	int count=0;

	for(v=0; v < G.n; v++)
	{
		placed[v]=FALSE;
	}
	Q = QUEUEinit();

	for(u=0; u < G.n; u++)
	{
		if(!placed[u])
		{
			count++;
			printf("Connected Component %d: ( ", count);
			placed[u] = TRUE;
			QUEUEput(Q, u);
			do 
			{
				v = QUEUEget(Q);
				printf("%d ", v);

				curedge=G.firstedge[v];  // curedge is a pointer to the first edge (v,_) of V
				while(curedge)
				{
					w=curedge->endpoint;  // w is a successor of v and (v,w) is the current edge
					if(!placed[w])
					{
						placed[w] = TRUE;	
						QUEUEput(Q, w);
					}
					curedge=curedge->nextedge;  // curedge is a pointer to the next edge (v,_) of V
				}
			}while(!QUEUEempty(Q));
			printf(")\n");
		}
	}
	QUEUEend(Q);
}