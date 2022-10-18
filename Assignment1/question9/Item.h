#define MAXCOUNT 10000000
#define MAXCUBES 50


typedef char Item;
typedef struct StateTag *StatePointer;
typedef StatePointer PQItem;
typedef PQItem PQArray[MAXCOUNT];
typedef struct STACKTag *StackPointer;
typedef StackPointer StateArray[MAXCUBES];