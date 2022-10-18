#include "Item.h"

typedef struct HandleTag *ST;

  ST STinit(void);
 int STcount(ST);
 int STinsert(ST, Item);
Item STsearch(ST, Key);
 int STdelete(ST, Key);
Item STselect(ST, int);
void STsort(ST, void (*visit)(Item));

void STend(ST);