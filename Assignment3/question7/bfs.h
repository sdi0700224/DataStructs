#include "QUEUE.h"
#include "GraphTypes.h"

typedef struct graph Graph;

void PrintElement(Vertex);
void BreadthFirst(Graph, void (*)(Vertex), Vertex);
 int BreadthFirstConnected(Graph G);
void BreadthFirstShortest(Graph G, Vertex A);
void BreadthFirstComponents(Graph G);