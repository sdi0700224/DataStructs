#include "Item.h"


void STACKinit(int, StackPointer*);
int STACKempty(StackPointer);
int STACKpush(Item, StackPointer*);
Item STACKpop(StackPointer*);

void ReadStateArray(StateArray, char*);
void FreeStateArray(StateArray);
int StackCompare(StackPointer, StackPointer);
void STACKcopy(StackPointer*, StackPointer*);
Item GetLastItem(StackPointer);
void StackReverse(StackPointer*);