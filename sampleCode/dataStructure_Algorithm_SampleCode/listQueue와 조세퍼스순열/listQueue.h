#pragma once 
#pragma warning(disable:4996)
#include "datatype.h"
enum {FALSE, TRUE};

typedef struct _node Node;
struct _node
{
	DataType data;
	Node *next;
};

typedef struct _queue { 
	Node *head;
	Node *tail;
	Node *cur;
}Queue; 

void initQueue(Queue * qPtr); // ť ���� �� �ʱ�ȭ �Լ�
int enqueue(Queue * qPtr, DataType inData);   // ť�� ������ �ϳ��� ������
int dequeue(Queue * qPtr, DataType * getData);  // ť���� ������ �ϳ��� ����
void printQueue(Queue * qPtr, void (*print)(DataType *) );  // ť ���� ��� �����͸� ���(dequeue�ϴ� ���� �ƴ�)
void destroyQueue(Queue * qPtr);  // ť �Ҹ� �Լ�
int isQueueEmpty(const Queue *qPtr); // ť�� ����ִ°� �˻�

