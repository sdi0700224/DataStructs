#include "Item.h"

typedef struct queue *Q;
void QUEUEdump(Q);
   Q QUEUEinit(void);
 int QUEUEempty(Q);
void QUEUEput(Q, Item);
Item QUEUEget(Q);

void QUEUEend(Q);
