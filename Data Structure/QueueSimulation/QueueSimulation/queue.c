#include "queue.h"
#include <stdlib.h>



struct Queue* CreateQueue()
{
	struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
	if (queue == NULL)
		return NULL;
	queue->m_End = queue->m_Front = NULL;
	queue->m_Size = 0;
	return queue;
}

void PushBack(struct Queue* queue, struct Node* node)
{
	if (queue == NULL)
		return;
	_PushBack(queue, node);
}

struct Node* PopFront(struct Queue* queue)
{
	if (queue == NULL)
		return NULL;
	return _PopFront(queue);
}


int GetCurrentQueueSize(struct Queue* queue)
{	
	if (queue == NULL)
		return -1;
	return queue->m_Size;
}



static void _PushBack(struct Queue* queue, struct Node* node)
{

	if (queue->m_End != NULL)
	{
		queue->m_End->next = node;
	}
	node->next = NULL;
	queue->m_End = node;
	queue->m_Size++;
	
	if (queue->m_Size == 1)
	{
		queue->m_Front = node;
	}
	return;
}

static struct Node* _PopFront(struct Queue* queue)
{
	struct Node* ret = queue->m_Front;

	

	if (queue->m_Front != NULL)
	{
		queue->m_Front = queue->m_Front->next;
	}
	queue->m_Size--;

	if (queue->m_Size == 0)
	{
		queue->m_End = NULL;
	}
	return ret;
}