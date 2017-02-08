#include <stdio.h> 
#include <malloc.h> 
#include <assert.h> 
#include "listQueue.h" 

/*--------------------------------------------------------------------------------------
  �Լ���ױ�� : initQueue() - ť �ʱ�ȭ �Լ�
  ���ϰ� : ����
--------------------------------------------------------------------------------------*/
void initQueue(Queue * qPtr) 
{  
	qPtr->head = (Node *) calloc(1, sizeof(Node));
	assert(qPtr->head!=NULL);
	qPtr->tail = (Node *) calloc(1, sizeof(Node));
	assert(qPtr->head!=NULL);
	qPtr->head->next = qPtr->tail;
	qPtr->tail->next = qPtr->tail;
	qPtr->cur = NULL;
} 
/*--------------------------------------------------------------------------------------
  �Լ���ױ�� : enqueue() - ť�� ������ �ϳ��� ������
  �������� : qPtr - ť ����ü�� �ּ�
             inData - ť�� ������ ������
  ���ϰ� : ���������� �����ϸ� TRUE, �����ϸ� FALSE ����
--------------------------------------------------------------------------------------*/
int enqueue(Queue * qPtr, DataType inData) 
{ 
	Node *np = (Node *)calloc(1, sizeof(Node)); //���ο� ��� ����
	if(np==NULL)  // �޸� �Ҵ� �����ϸ� enqueue����
	{
		return FALSE;
	}
	//��带 ���� ��� �ٷ� �տ� ��� �߰�
	qPtr->cur=qPtr->head;
	while(qPtr->cur->next!=qPtr->tail)  // ���� ��� �ٷ� �ճ�带 cur�� ����Ű�� �̵� ��Ŵ
		qPtr->cur = qPtr->cur->next; 
	
	qPtr->cur->next = np;
	np->next = qPtr->tail;
	np->data = inData; //������ ����

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
	if( isQueueEmpty(qPtr) ) // ť�� ��������� dequeue �Ұ� 
	{ 
		return FALSE; 
	} 

	*getData = qPtr->head->next->data; 
	qPtr->cur = qPtr->head->next;
	qPtr->head->next = qPtr->head->next->next;
	free(qPtr->cur);

	return TRUE; 
} 
/*--------------------------------------------------------------------------------------
  �Լ���ױ�� : printQueue() - ť ���� ��� �����͸� ��� ��
  �������� : qPtr - ť ����ü�� �ּ�
             print -  DataType�� ������ ����ϴ� ��� ���� �Լ�
  ���ϰ� : ����
--------------------------------------------------------------------------------------*/
void printQueue(Queue * qPtr, void (*print)(DataType *) ) 
{ 
	if(isQueueEmpty(qPtr)==TRUE) 
	{
		printf("Queue�� ����ֽ��ϴ�!!\n");
		return;
	}
	qPtr->cur = qPtr->head->next;
	while( qPtr->cur != qPtr->tail){
		print(&qPtr->cur->data);
		qPtr->cur = qPtr->cur->next;
	}
	printf("\n\n");
} 
/*--------------------------------------------------------------------------------------
  �Լ���ױ�� : destroyQueue() - ť �Ҹ� �Լ�
  �������� : qPtr - ť ����ü�� �ּ�
  ���ϰ� : ����
--------------------------------------------------------------------------------------*/
void destroyQueue(Queue * qPtr) 
{ 
	qPtr->cur = qPtr->head->next;
	while( qPtr->cur != qPtr->tail){
		qPtr->head->next = qPtr->head->next->next;
		free(qPtr->cur);
		qPtr->cur = qPtr->head->next;
	}
	free(qPtr->head);
	free(qPtr->tail);
	qPtr->head = qPtr->tail = qPtr->cur = NULL;
} 
/*--------------------------------------------------------------------------------------
  �Լ��� �� ���: isQueueEmpty() - ť�� ����ִ°� �˻�
  ��������: qPtr - ť ����ü�� �ּ�
  ���ϰ�: ��������� TRUE ����, ������� ������ FALSE ����
--------------------------------------------------------------------------------------*/
int isQueueEmpty(const Queue *qPtr)
{
	if(qPtr->head->next == qPtr->tail) 
		return TRUE;
	else 
		return FALSE;
}
