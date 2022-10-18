#include "Items.h"

typedef struct DlistTag *DlistPointer;

void Create(void);		//Creates an empty list
int Size(void);		//Returns list size
int IsEmpty(void);		//Returns 1 if List is empty, else 0
DlistPointer GetFirst(void);		//Returns fist Node address
DlistPointer GetLast(void);		//Same, last Node instead
DlistPointer GetPrev(DlistPointer);		//Returns previous Node
DlistPointer GetNext(DlistPointer);		//Same, next Node instead
void AddBefore(DlistPointer, DlistPointer);//Adds Node copy before
void AddAfter(DlistPointer, DlistPointer);	//Same, after insted
void AddFirst(DlistPointer);	// Adds Node copy at first
void AddLast(DlistPointer);	//Same, adds at end instead
void Remove(DlistPointer);	//Delete - Free Node
void Print(void);		//Print List

name GetName(DlistPointer);	//Returns name
value GetValue(DlistPointer);	//Returns value associated with name
DlistPointer NewNode(name, value);	//Creates new Node
void EndList(void);	//Frees Handles