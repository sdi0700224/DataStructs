typedef char *String;
typedef int Key;
typedef struct ItemTag *Item;

#define NULLitem NULL /* NULLitem is a constant */
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define eq(A, B) (!less(A, B) && !less(B, A))

Item ITEMrand(void);
void ITEMscan(Item*);
void ITEMshow(Item);

int GetKey(Item);
void FreeItem(Item);
Item ITEMgen(int);
