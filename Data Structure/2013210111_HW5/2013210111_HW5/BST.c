#include <stdlib.h>
#include "BST.h"

struct BST* BST_Craete()
{
	struct BST* bst = (struct BST*)malloc(sizeof(struct BST));

	if (bst != NULL)
	{
		bst->rootNode = BSTNode_Create(0);
	}
	return bst;
}

void BST_Insert(struct BST* bst, int value)
{
	if (bst == NULL)
		return;

	private_BST_Insert(bst->rootNode, value);
	return;
}

struct BSTNode* BST_Search(struct BST* bst, int value)
{
	if (bst == NULL)
		return NULL;

	return private_BST_Search(bst->rootNode, value);
}

void BST_Delete(struct BST* bst, int value)
{
	if (bst == NULL)
		return;

	private_BST_Delete(bst->rootNode, value);
	return;
}

static void private_BST_Insert(struct BSTNode* node, int value)
{
	if (node->hasValue)
	{
		struct BSTNode** nextNodePointer = NULL;
		if (value <= node->value)
		{
			nextNodePointer = &(node->leftNode);
		}
		else
		{
			nextNodePointer = &(node->rightNode);
		}
		if (NULL == *nextNodePointer)
		{
			*nextNodePointer = BSTNode_Create();
		}
		private_BST_Insert(*nextNodePointer, value);
	}
	else
	{
		node->hasValue = 1; // true
		node->value = value;
	}
	return;
}

struct BSTNode* BSTNode_Create()
{
	struct BSTNode* node = (struct BSTNode*)malloc(sizeof(struct BSTNode));

	if (node != NULL)
	{
		node->rightNode = NULL;
		node->leftNode = NULL;
		node->value = 0;
		node->hasValue = 0;	// false
	}

	return node;
}

static void private_BST_Delete(struct BSTNode* node, int value)
{
	if (NULL == node)
	{
		return;
	}

	if (node->hasValue)
	{
		// case 1. equal
		if (value == node->value)
		{
			node->hasValue = 0;	//false
			node->value = 0;
			// don't need to memory deallocation. just reset them to re-use.
			return;
		}

		// case 2. not equal. then find successor
		struct BSTNode** nextNodePointer = NULL;
		if (value <= node->value)
		{
			nextNodePointer = &(node->leftNode);
		}
		else
		{
			nextNodePointer = &(node->rightNode);
		}
		if (NULL == *nextNodePointer)
		{
			// case 2.1 no successor -> stop finding.
			return;
		}
		else
		{
			private_BST_Delete(*nextNodePointer, value);
		}
	}
	else
	{
		// not found.	
	}
	return;
}

static struct BSTNode* private_BST_Search(struct BSTNode* node, int value)
{
	if (NULL == node)
	{
		return node;
	}

	if (node->hasValue)
	{
		// case 1. equal
		if (value == node->value)
		{
			return node;
		}

		// case 2. not equal. then find successor
		struct BSTNode** nextNodePointer = NULL;
		if (value <= node->value)
		{
			nextNodePointer = &(node->leftNode);
		}
		else
		{
			nextNodePointer = &(node->rightNode);
		}
		if (NULL == *nextNodePointer)
		{
			// case 2.1 no successor -> stop finding.
			return NULL;
		}
		else
		{
			private_BST_Search(*nextNodePointer, value);
		}
	}
	else
	{
		// not found.	
		return NULL;
	}
	return NULL;
}

void BST_Destory(struct BST* bst)
{
	private_BST_Destory(bst->rootNode);
	free(bst);
}

static void private_BST_Destory(struct BSTNode* node)
{
	if (NULL != node)
	{
		if (node->leftNode)
			private_BST_Destory(node->leftNode);
		if (node->rightNode)
			private_BST_Destory(node->rightNode);
		free(node);
	}
	return;
}
