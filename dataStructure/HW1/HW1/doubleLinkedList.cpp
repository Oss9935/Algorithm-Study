#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include "doubleLinkedList.h"

void create(LinkedList *lp)	//init list
{

}

Node * makeNode(DataType *dataPtr, Node *prev, Node *next)
{

}

Node * appendFromHead(LinkedList *lp, DataType *pData)
{

}

Node * appendFromTail(LinkedList *lp, DataType *pData)
{

}

void display(LinkedList *lp, void(*printData)(DataType *))
{

}

void deleteNode(LinkedList *lp, Node *target)
{

}

Node * searchUnique(LinkedList *lp, DataType *dataPtr,
	int(*compare)(DataType *, DataType *))
{

}

Node ** searchDuplicate(LinkedList *lp, int *searchCnt, DataType *dataPtr,
	int(*compare)(DataType *, DataType *))
{

}

void sortList(LinkedList *lp, int(*compare)(DataType *, DataType *))
{

}

void destroy(LinkedList *lp)
{

}