typedef struct LinearListNode
{
	int value;
	struct LinearListNode* nextNode;
};


struct LinearListNode* LinearListNode_Create(int value);

//////////////////////////////////////////////////////////////////////////

typedef struct LinearList
{
	struct LinearListNode* startNode;
};


struct LinearList*		LinearList_Craete();
void					LinearList_Destroy(struct LinearList* list);
void					LinearList_Insert(struct LinearList* list, int value);
struct LinearListNode*	LinearList_Search(struct LinearList* list, int value);
void					LinearList_Delete(struct LinearList* list, int value);

static void						private_LinearList_Insert(struct LinearList* list, int value);
static struct LinearListNode*	private_LinearList_Search(struct LinearList* list, int value);
static void						private_LinearList_Delete(struct LinearList* list, int value);
