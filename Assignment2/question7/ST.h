#include "Item.h"

typedef struct HandleTag *ST;

ST STinit(void);
 int STcount(ST);
void STinsert(ST, Item);
Item STsearch(ST, Key);
void STdelete(ST, Key);
Item STselect(ST, int);
void STsort(ST, void (*visit)(Item));

void STdeleteAll(ST, Key);
void STend(ST);