struct ListTag
{
	int value;
	struct ListTag *next;
}*Head;

typedef struct ListTag ListType;
typedef ListType *ListPointer;

void AddFist(ListPointer*, int);
void Destroy(ListPointer*);
void Print(ListPointer);