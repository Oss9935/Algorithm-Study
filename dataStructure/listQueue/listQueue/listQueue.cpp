#include <stdio.h>
#include <assert.h>
#include <malloc.h> 
#include "listQueue.h" 

/*--------------------------------------------------------------------------------------
Function name	: createQueue - ť �ʱ�ȭ �Լ�
Parameters		: qp - ť ����ü�� �ּ�
Returns			: ���� - TRUE / ���� - FALSE
--------------------------------------------------------------------------------------*/
BOOL createQueue(Queue * qp)
{
	qp->head = (Node *)malloc(sizeof(Node));
	assert(qp->head != NULL);
	qp->tail = (Node *)malloc(sizeof(Node));
	assert(qp->tail != NULL);

	qp->head->next = qp->tail;
	qp->tail->next = NULL;

	return TRUE;  // ���ϰ��� �������ּ���
}


/*--------------------------------------------------------------------------------------
Function name	: isQueueEmpty - ť�� ����ִ°� �˻�
Parameters		: qp - ť ����ü�� �ּ�
Returns			: ������ ��������� TRUE ����, ������� ������ FALSE ����
--------------------------------------------------------------------------------------*/
BOOL isQueueEmpty(const Queue *qp)
{
	if (qp->head->next == qp->tail)
		return TRUE;
	return FALSE;  // ���ϰ��� �������ּ���
}


/*--------------------------------------------------------------------------------------
Function name	: enqueue - ť�� ������ �ϳ��� ������
Parameters		: qp - ť ����ü�� �ּ�
enqueData - ť�� ������ ������
Returns			: ���������� �����ϸ� TRUE, �����ϸ� FALSE ����
--------------------------------------------------------------------------------------*/
BOOL enqueue(Queue * qp, int enqueData)
{
	Node *newData, *cur;
	newData = (Node *)malloc(sizeof(Node));
	assert(newData != NULL);

	cur = qp->head;
	while (cur->next != qp->tail)
		cur = cur->next;
	cur->next = newData;
	newData->next = qp->tail;
	newData->data = enqueData;

	return TRUE;  // ���ϰ��� �������ּ���
}


/*--------------------------------------------------------------------------------------
Function name	: dequeue - ť���� ������ �ϳ��� ����
Parameters		: qp - ť ����ü�� �ּ�
dequeData - ���� �����͸� ������ �������� �ּ�
Returns			: ���������� ������ TRUE, �����ϸ� FALSE ����
--------------------------------------------------------------------------------------*/
BOOL dequeue(Queue * qp, int * dequeData)
{
	Node *deleteNode;
	if (qp == NULL) { return FALSE; }
	if (isQueueEmpty(qp) == TRUE) { return FALSE; }
	*dequeData = qp->head->next->data;

	deleteNode = qp->head->next;
	qp->head->next = qp->head->next->next;
	
	free(deleteNode);

	return TRUE;  // ���ϰ��� �������ּ���
}


/*--------------------------------------------------------------------------------------
Function name	: printQueue - ť ���� ��� �����͸� ��� ��
Parameters		: qp - ť ����ü�� �ּ�
Returns			: ����
--------------------------------------------------------------------------------------*/
void printQueue(const Queue * qp)
{
	Node *cur;
	cur = qp->head;
	while (cur->next != qp->tail)
	{
		cur = cur->next;
		printf("%4d\n", cur->data);
	}

	return;
}


/*--------------------------------------------------------------------------------------
Function name	: destroyQueue - ť �Ҹ� �Լ�
Parameters		: qp - ť ����ü�� �ּ�
Returns			: ����
--------------------------------------------------------------------------------------*/
void destroyQueue(Queue * qp)
{
	Node *deleteNode;

	while (qp->head->next != qp->tail)
	{
		deleteNode = qp->head->next;
		qp->head->next = qp->head->next->next;
		free(deleteNode);
	}

	free(qp->head);
	free(qp->tail);

	return;
}
