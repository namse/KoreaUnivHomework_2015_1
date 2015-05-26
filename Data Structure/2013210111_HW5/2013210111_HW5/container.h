typedef struct Node
{
	int value;
	struct Node* nextNode;
};

typedef struct LinearList
{
	struct Node* startNode;
};

struct Node* Node_Create(int value);

struct LinearList* LinearList_Craete();
void LinearList_Insert(struct LinearList* list, int value);
struct Node* LinearList_Search(struct LinearList* list, int value);
void LinearList_Delete(struct LinearList* list, int value);

static void private_LinearList_Insert(struct LinearList* list, int value);
static struct Node* private_LinearList_Search(struct LinearList* list, int value);
static void private_LinearList_Delete(struct LinearList* list, int value);
