#include "GraphTypes.h"
#define MAXCOUNT (MAXVERTEX*(MAXVERTEX-1))

typedef struct EdgeTag *EdgePointer;
typedef EdgePointer PQItem;
typedef PQItem PQArray[MAXCOUNT];