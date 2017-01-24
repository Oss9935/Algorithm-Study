#pragma once
#pragma warning(disable:4996)
#include "datatype.h"

// struct type Node to store data
typedef struct _node Node;
struct _node {
	Node *prev;
	DataType data;
	Node *next;
};

// for management double Linked List
typedef struct _linkedList {
	Node *head;
	Node *cur;
	Node *tail;
	int length;	//Number of actual data nodes
}LinkedList;

/*	double Linked List management function	*/
void create(LinkedList *lp);	//init list
Node * makeNode(DataType *dataPtr, Node *prev, Node *next);
Node * appendFromHead(LinkedList *lp, DataType *pData);
Node * appendFromTail(LinkedList *lp, DataType *pData);
void display(LinkedList *lp, void(*printData)(DataType *));
void deleteNode(LinkedList *lp, Node *target);
Node * searchUnique(LinkedList *lp, DataType *dataPtr, 
	int(*compare)(DataType *, DataType *));
Node ** searchDuplicate(LinkedList *lp, int *searchCnt, DataType *dataPtr, 
	int(*compare)(DataType *, DataType *));
void sortList(LinkedList *lp, int(*compare)(DataType *, DataType *));
void destroy(LinkedList *lp);