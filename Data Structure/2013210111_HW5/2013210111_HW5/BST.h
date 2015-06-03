typedef struct BSTNode
{
	int value;
	int hasValue; // 0 : false, non-zero : true.
	struct BSTNode* leftNode;
	struct BSTNode* rightNode;
};

struct BSTNode* BSTNode_Create();

//////////////////////////////////////////////////////////////////////////

typedef struct BST
{
	struct BSTNode* rootNode;
};


struct BST*				BST_Craete();
void					BST_Destory(struct BST* bst);
void					BST_Insert(struct BST* bst, int value);
struct BSTNode*			BST_Search(struct BST* bst, int value);
void					BST_Delete(struct BST* bst, int value);

static void				private_BST_Destory(struct BSTNode* node);
static void				private_BST_Insert(struct BSTNode* node, int value);
static struct BSTNode*	private_BST_Search(struct BSTNode* node, int value);
static void				private_BST_Delete(struct BSTNode* node, int value);
