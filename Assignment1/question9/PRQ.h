#include "Item.h"


typedef struct PriorityTag *PriorityPointer;

void Initialize (PriorityPointer*);
int Empty (PriorityPointer);
int Full (PriorityPointer);
void Insert (PQItem, PriorityPointer);
PQItem Remove (PriorityPointer);

PQItem NewNode(StateArray, int, int);
int GetNodeVal(PQItem);
void FreeState(PQItem);
StackPointer* GetArray(PQItem);
void NewStateInsert(PQItem, PriorityPointer, int);
void HCalc(PQItem);
void HCalc1(PQItem);
void HCalc2(PQItem);
int GGet(PQItem);
void PrintMoves(PQItem);
void ArrayFill(char*);
int addcalc(int);