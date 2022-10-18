typedef int Number;
typedef struct NodeTag *NodePointer;

void InsertNewSecondNode(NodePointer*);
void InsertNewLastNode(Number, NodePointer*);
void DeleteLastNode(NodePointer*);
NodePointer ListSearch(Number, NodePointer);
void PrintList(NodePointer);
void SelectListSort (NodePointer*);
void InsertListSort (NodePointer*);