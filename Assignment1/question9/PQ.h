#include "Item2.h"


typedef struct PriorityTag2 *PriorityPointer2;

void Initialize2 (PriorityPointer2*);
int Empty2 (PriorityPointer2);
int Full2 (PriorityPointer2);
void Insert2 (PQItem2, PriorityPointer2);
PQItem2 Remove2 (PriorityPointer2);

void PriorityQueueSort(PQArray2);
