#include <stdlib.h>
#include "container.h"


static void private_LinearList_Insert(struct LinearList* list, int value)
{

	struct Node* newNode = Node_Create(value);
	if (list->startNode == NULL)
	{
		list->startNode = newNode;
	}
	else
	{
		struct Node* node = list->startNode;
		while (node->nextNode != NULL)		// until find last node
		{
			node = node->nextNode;
		}
		node->nextNode = newNode;			// just set.
	}
	return;
}
static struct Node* private_LinearList_Search(struct LinearList* list, int value)
{
	struct Node* node = list->startNode;
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
		struct Node* nextNode = list->startNode->nextNode;
		free(list->startNode);
		list->startNode = nextNode;
	}
	else	// else on other node,
	{
		struct Node* prevNode = list->startNode;
		struct Node* node = prevNode->nextNode;

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


struct Node* Node_Create(int value)
{
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));

	if (node != NULL)
	{
		node->nextNode = NULL;
		node->value = value;
	}

	return node;
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

struct Node* LinearList_Search(struct LinearList* list, int value)
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