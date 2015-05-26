#include <stdlib.h>
#include "LinearList.h"


static void private_LinearList_Insert(struct LinearList* list, int value)
{

	struct LinearListNode* newNode = LinearListNode_Create(value);
	if (list->startNode == NULL)
	{
		list->startNode = newNode;
	}
	else
	{
		struct LinearListNode* node = list->startNode;
		while (node->nextNode != NULL)		// until find last node
		{
			node = node->nextNode;
		}
		node->nextNode = newNode;			// just set.
	}
	return;
}
static struct LinearListNode* private_LinearList_Search(struct LinearList* list, int value)
{
	struct LinearListNode* node = list->startNode;
	while (node != NULL)	// iterate All Nodes Linearly.
	{
		if (node->value == value)
			return node;
		node = node->nextNode;
	}
	return NULL;	// dosen't find value -> return NULL
}
static void private_LinearList_Delete(struct LinearList* list, int value)
{
	if (list->startNode != NULL && list->startNode->value == value) // if first node,
	{
		struct LinearListNode* nextNode = list->startNode->nextNode;
		free(list->startNode);
		list->startNode = nextNode;
	}
	else	// else on other node,
	{
		struct LinearListNode* prevNode = list->startNode;
		struct LinearListNode* node = prevNode->nextNode;

		while (node != NULL)	// iterate all.
		{
			if (node->value == value)
			{
				// delete node, and set prevNode's next node = node's next node.
				prevNode->nextNode = node->nextNode;
				free(node);
				break;
			}
			prevNode = node;
			node = node->nextNode;
		}
	}

	return;
}
struct LinearList* LinearList_Craete()
{
	struct LinearList* list = (struct LinearList*)malloc(sizeof(struct LinearList));

	if (list != NULL)
	{
		list->startNode = NULL;
	}
	return list;
}
void LinearList_Insert(struct LinearList* list, int value)
{
	if (list == NULL)
		return;

	private_LinearList_Insert(list, value);
	return;
}

struct LinearListNode* LinearList_Search(struct LinearList* list, int value)
{
	if (list == NULL)
		return NULL;

	return private_LinearList_Search(list, value);
}

void LinearList_Delete(struct LinearList* list, int value)
{
	if (list == NULL)
		return;

	private_LinearList_Delete(list, value);
	return;
}


struct LinearListNode* LinearListNode_Create(int value)
{
	struct LinearListNode* node = (struct LinearListNode*)malloc(sizeof(struct LinearListNode));

	if (node != NULL)
	{
		node->nextNode = NULL;
		node->value = value;
	}

	return node;
}

void LinearList_Destroy(struct LinearList* list)
{
	if (list->startNode != NULL)
	{
		struct LinearListNode* node = list->startNode;
		while (node != NULL)
		{
			struct LinearListNode* deleteNode = node;
			node = node->nextNode;

			free(deleteNode);
		}
	}

	free(list);
}
