#include "bfs.h"

void Initialize(G*, int);
void InsertEdge(Vertex, Vertex, G);
void ShowGraph(G);
void BreadthFirstSearch(G, Vertex);
 int IsConnected(G);
void ShortestPaths(G, Vertex);
void ConnectedComponents(G);

void Destroy(G);