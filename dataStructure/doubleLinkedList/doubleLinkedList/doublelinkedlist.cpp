#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include "doublelinkedlist.h"


/*--------------------------------------------------------------------------------------
�Լ��� �� ���: create() - ��ũ�帮��Ʈ �ʱ�ȭ
��������:  lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void create(LinkedList * lp)
{
	lp->head = (Node *)malloc(sizeof(Node));
	assert(lp->head != NULL);
	lp->tail = (Node *)malloc(sizeof(Node));
	assert(lp->tail != NULL);

	lp->head->next = lp->tail;
	lp->tail->prev = lp->head;

	lp->head->prev = lp->head;
	lp->tail->next = lp->tail;

	lp->cur = NULL;
	lp->length = 0;

	return;
}

/*--------------------------------------------------------------------------------------
�Լ��� �� ���: makeNode() - �� ��� ���� �Լ�
��������:  dataPtr - �� ��忡 ������ ������ ������ �ּ�
prev - �� ����� �� ����� �ּ�
next - �� ����� �� ����� �ּ�
���ϰ�: ������ ����� �ּ�
--------------------------------------------------------------------------------------*/
Node * makeNode(DataType *dataPtr, Node *prev, Node *next)
{

	return NULL;
}

/*--------------------------------------------------------------------------------------
�Լ��� �� ���: appendFromHead() - ����� �ڿ� �� ��� �߰�(���� ����)
��������: lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
dataPtr - �� ��忡 ������ ������ ������ �ּ�
���ϰ�: �߰��� ����� �ּ�
--------------------------------------------------------------------------------------*/
Node * appendFromHead(LinkedList *lp, DataType *dataPtr)
{
	lp->cur = (Node *)malloc(sizeof(Node));
	assert(lp->cur != NULL);

	lp->cur->next = lp->head->next;
	lp->cur->prev = lp->head;

	lp->head->next->prev = lp->cur;
	lp->head->next = lp->cur;


	lp->cur->data = *dataPtr;
	lp->length++;

	return lp->cur;
}

/*--------------------------------------------------------------------------------------
�Լ��� �� ���: appendFromTail() - ���ϳ�� �տ� �� ��� �߰�(���� ����)
��������: lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
dataPtr - �� ��忡 ������ ������ ������ �ּ�
���ϰ�: �߰��� ����� �ּ�
--------------------------------------------------------------------------------------*/
Node * appendFromTail(LinkedList *lp, DataType *dataPtr)
{
	lp->cur = (Node *)malloc(sizeof(Node));
	assert(lp->cur != NULL);

	lp->cur->prev = lp->tail->prev;
	lp->cur->next = lp->tail;
	
	lp->tail->prev->next = lp->cur;
	//lp->cur->prev->next = lp->cur;
	lp->tail->prev = lp->cur;
	
	lp->cur->data = *dataPtr;
	lp->length++;

	return lp->cur;
}

/*--------------------------------------------------------------------------------------
�Լ��� �� ���: display() - ����Ʈ���� ��� ������ ��� ���
��������: lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
print - ��� �� data���� ����� ���� �����Լ��� �����ּ�
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void display(LinkedList *lp, void(*print)(DataType *))
{
	lp->cur = lp->head->next;
	while (lp->cur != lp->tail) {
		print(&lp->cur->data);
		lp->cur = lp->cur->next;
	}

	return;
}

/*--------------------------------------------------------------------------------------
�Լ��� �� ���: searchUnique() - ���޵� �����Ϳ� ��ġ�ϴ� ��� �˻� �Լ�
��������: lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
dataPtr - �˻��� �����Ͱ� ����� ������ �ּ�
compare - data���� �񱳸� ���� �����Լ��� �����ּ�
���ϰ�: ã�� ����� �ּ� ����/���� �� NULL pointer ����
--------------------------------------------------------------------------------------*/
Node * searchUnique(LinkedList *lp, DataType *dataPtr, int(*compare)(DataType *, DataType *))
{
	lp->cur = lp->head->next;
	while (lp->cur != lp->tail) {
		if (compare(dataPtr, &lp->cur->data) == NULL) {
			return lp->cur;
		}
		lp->cur = lp->cur->next;
	}

	return NULL;
}

/*--------------------------------------------------------------------------------------
�Լ��� �� ���: searchDuplicate() - ���޵� �����Ϳ� ��ġ�ϴ� ��� ��带 ���� �˻��ϴ� �Լ�
��������: lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
searchCnt - ã�� ����� ������ ������ ������ �ּ�
dataPtr - �˻��� �����Ͱ� ����� ������ �ּ�
compare - data���� �񱳸� ���� �����Լ��� �����ּ�
���ϰ�: ã�� ����� �ּҸ�� �迭�� ���� �ּ� ����/���� �� NULL pointer ����
--------------------------------------------------------------------------------------*/
Node ** searchDuplicate(LinkedList *lp, int *searchCnt, 
	DataType *dataPtr, int(*compare)(DataType *, DataType *)) 
	// dataPtr�� ��ġ�ϴ� ����� �ּҸ� ��� �ִ� Node *�迭�� �����ּ� ����/���� �� NULL pointer ����
{
	Node **np = NULL;
	*searchCnt = 0;
	lp->cur = lp->head->next;
	while (lp->cur != lp->tail) {
		if (compare(&lp->cur->data, dataPtr) == NULL) {
			np = (Node**)realloc(np, (*searchCnt+1) * sizeof(Node *));
			np[*searchCnt] = lp->cur;
			++(*searchCnt);
		}
		lp->cur = lp->cur->next;
	}

	return np;
}

/*--------------------------------------------------------------------------------------
�Լ��� �� ���: deleteNode() - ����Ʈ������ target ��� ����
��������: lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
target - ������ ����� �����ּ�
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void deleteNode(LinkedList *lp, Node *target)
{
	target->prev->next = target->next;
	target->next->prev = target->prev;
	free(target);
	lp->length--;

	return;
}

/*--------------------------------------------------------------------------------------
�Լ��� �� ���: destroy() - ����Ʈ������ ��� ��� ����(head, tail ��� ����)
��������: lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void destroy(LinkedList *lp)
{
	Node *tp;

	lp->cur = lp->head->next;
	while (lp->cur != lp->tail) {
		tp = lp->cur;
		lp->cur = lp->cur->next;
		free(tp);
	}
	free(lp->head);
	free(lp->tail);

	return;
}

/*--------------------------------------------------------------------------------------
�Լ��� �� ���: sortList() - ����Ʈ���� ��带 �����Լ��� ���ش�� �����ϴ� �Լ�
��������: lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
compare - data���� �񱳸� ���� �����Լ��� �����ּ�
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void sortList(LinkedList *lp, int(*compare)(DataType *, DataType *))  // ��� ����
{
	Node *tp = NULL;
	lp->cur = lp->head->next;
	while (lp->cur != lp->tail->prev) {
		tp = lp->cur->next;
		while (tp != lp->tail) {
			if (compare(&lp->cur->data, &tp->data) > 0) {
				DataType temp;
				temp = lp->cur->data;
				lp->cur->data = tp->data;
				tp->data = temp;
			}
			tp = tp->next;
		}
		lp->cur = lp->cur->next;
	}

	return;
}
