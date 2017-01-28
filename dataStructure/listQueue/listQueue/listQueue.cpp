#include <stdio.h>
#include <assert.h>
#include <malloc.h> 
#include "listQueue.h" 

/*--------------------------------------------------------------------------------------
Function name	: createQueue - 큐 초기화 함수
Parameters		: qp - 큐 구조체의 주소
Returns			: 성공 - TRUE / 실패 - FALSE
--------------------------------------------------------------------------------------*/
BOOL createQueue(Queue * qp)
{
	qp->head = (Node *)malloc(sizeof(Node));
	assert(qp->head != NULL);
	qp->tail = (Node *)malloc(sizeof(Node));
	assert(qp->tail != NULL);

	qp->head->next = qp->tail;
	qp->tail->next = NULL;

	return TRUE;  // 리턴값은 수정해주세요
}


/*--------------------------------------------------------------------------------------
Function name	: isQueueEmpty - 큐가 비어있는가 검사
Parameters		: qp - 큐 구조체의 주소
Returns			: 완전히 비어있으면 TRUE 리턴, 비어있지 않으면 FALSE 리턴
--------------------------------------------------------------------------------------*/
BOOL isQueueEmpty(const Queue *qp)
{
	if (qp->head->next == qp->tail)
		return TRUE;
	return FALSE;  // 리턴값은 수정해주세요
}


/*--------------------------------------------------------------------------------------
Function name	: enqueue - 큐에 데이터 하나를 저장함
Parameters		: qp - 큐 구조체의 주소
enqueData - 큐에 저장할 데이터
Returns			: 성공적으로 저장하면 TRUE, 실패하면 FALSE 리턴
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

	return TRUE;  // 리턴값은 수정해주세요
}


/*--------------------------------------------------------------------------------------
Function name	: dequeue - 큐에서 데이터 하나를 꺼냄
Parameters		: qp - 큐 구조체의 주소
dequeData - 꺼낸 데이터를 저장할 기억공간의 주소
Returns			: 성공적으로 꺼내면 TRUE, 실패하면 FALSE 리턴
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

	return TRUE;  // 리턴값은 수정해주세요
}


/*--------------------------------------------------------------------------------------
Function name	: printQueue - 큐 내의 모든 데이터를 출력 함
Parameters		: qp - 큐 구조체의 주소
Returns			: 없음
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
Function name	: destroyQueue - 큐 소멸 함수
Parameters		: qp - 큐 구조체의 주소
Returns			: 없음
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
