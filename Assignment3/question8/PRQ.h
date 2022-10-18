#include "Item.h"

void PrQInitialize(void);
int Empty(void);
int Full(void);
void Insert(PQItem);
PQItem Remove(void);
PQItem NewNode(Vertex, Vertex, int);
int GetVertex(PQItem, int);
void PrintPQArr(PQItem[], int);
void EndPQ(void);
