#define NULLitem NULL /* NULLitem is a constant */

typedef char *String;
typedef int Key;
typedef struct ItemTag *Item;

Item ITEMrand(void);
void ITEMscan(Item*);
void ITEMshow(Item);

 int GetKey(Item);
void FreeItem(Item);