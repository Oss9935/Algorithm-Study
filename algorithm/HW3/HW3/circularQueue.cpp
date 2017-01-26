#include <stdio.h> 
#include <malloc.h> 
#include <assert.h> 
#include "circularQueue.h"

/*--------------------------------------------------------------------------------------
�Լ���ױ�� : initQueue() - ť �ʱ�ȭ �Լ�
�������� : qPtr - ť ����ü�� �ּ�
size - ť�� ũ��
���ϰ� : ����
--------------------------------------------------------------------------------------*/
void initQueue(Queue * qPtr, int size)
{
	qPtr->qSize = size;
	qPtr->front = 0;
	qPtr->rear = 0;
	qPtr->queue = (DataType *)calloc(qPtr->qSize, sizeof(DataType));
}

/*--------------------------------------------------------------------------------------
�Լ���ױ�� : enqueue() - ť�� ������ �ϳ��� ������
�������� : qPtr - ť ����ü�� �ּ�
inData - ť�� ������ ������
���ϰ� : ���������� �����ϸ� TRUE, �����ϸ� FALSE ����
--------------------------------------------------------------------------------------*/
int enqueue(Queue * qPtr, DataType inData)
{
	if (isQueueFull(qPtr)) { return FALSE; }
	qPtr->queue[qPtr->rear++] = inData;
	qPtr->rear %= qPtr->qSize;

	return TRUE;
}

/*--------------------------------------------------------------------------------------
�Լ��� �� ��� : dequeue() - ť���� ������ �ϳ��� ����
�������� : qPtr - ť ����ü�� �ּ�
getData - ���� �����͸� ������ �������� �ּ�
���ϰ� : ���������� ������ TRUE, �����ϸ� FALSE ����
--------------------------------------------------------------------------------------*/
int dequeue(Queue * qPtr, DataType * getData)
{
	if (isQueueEmpty(qPtr)) { return FALSE; }
	*getData = qPtr->queue[qPtr->front++];
	qPtr->front %= qPtr->qSize;

	return TRUE;
}

/*--------------------------------------------------------------------------------------
�Լ���ױ�� : printQueue() - ť ���� ��� �����͸� ��� ��
�������� : qPtr - ť ����ü�� �ּ�
print -  DataType�� ������ ����ϴ� ��� ���� �Լ�
���ϰ� : ����
--------------------------------------------------------------------------------------*/
void printQueue(const Queue * qPtr, void(*print)(DataType *))
{
	int idx = qPtr->front;
	while (idx != qPtr->rear)
	{
		print(qPtr->queue + idx);
		++idx %= qPtr->qSize;
	}
}

/*--------------------------------------------------------------------------------------
�Լ���ױ�� : destroyQueue() - ť �Ҹ� �Լ�
�������� : qPtr - ť ����ü�� �ּ�
���ϰ� : ����
--------------------------------------------------------------------------------------*/
void destroyQueue(Queue * qPtr)
{
	free(qPtr->queue);
}

/*--------------------------------------------------------------------------------------
�Լ��� �� ���: isQueueEmpty() - ť�� ����ִ°� �˻�
��������: qPtr - ť ����ü�� �ּ�
���ϰ�: ��������� TRUE ����, ������� ������ FALSE ����
--------------------------------------------------------------------------------------*/
int isQueueEmpty(const Queue *qPtr)
{
	if (qPtr->front == qPtr->rear) { return TRUE; }
	return FALSE;
}

/*--------------------------------------------------------------------------------------
�Լ��� �� ���: isQueueFull() - ť ��ȭ���� �˻�
��������: qPtr - ť ����ü�� �ּ�
���ϰ�: ��ȭ ���¶�� TRUE ����, ��ȭ ���°� �ƴ϶�� FALSE ����
--------------------------------------------------------------------------------------*/
int isQueueFull(const Queue *qPtr)
{
	if (qPtr->front == (qPtr->rear + 1) % qPtr->qSize) { return TRUE; }
	return FALSE;
}

int getQueueLength(const Queue *qPtr)
{
	int len = 0;
	int idx = qPtr->front;
	while (idx != qPtr->rear)
	{
		++idx %= qPtr->qSize;
		len++;
	}
	return len;
}