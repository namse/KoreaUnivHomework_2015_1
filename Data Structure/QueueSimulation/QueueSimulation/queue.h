typedef struct Node
{
	int m_CustomerNumber;
	int m_ArriveTime;

	struct Node* next;

	int m_ServiceStartTime;
	int m_ServiceTime;
};

typedef struct Queue
{
	struct Node* m_Front;
	struct Node* m_End;
	int m_Size;
};

struct Queue* CreateQueue();
void PushBack(struct Queue* queue, struct Node* node);
struct Node* PopFront(struct Queue* queue);
int GetCurrentQueueSize(struct Queue* queue);

static void _PushBack(struct Queue* queue, struct Node* node);
static struct Node* _PopFront(struct Queue* queue);