#include <stdio.h> 
#include <malloc.h> 
#include <assert.h> 
#include "listQueue.h" 

/*--------------------------------------------------------------------------------------
  함수명및기능 : initQueue() - 큐 초기화 함수
  리턴값 : 없음
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
  함수명및기능 : enqueue() - 큐에 데이터 하나를 저장함
  전달인자 : qPtr - 큐 구조체의 주소
             inData - 큐에 저장할 데이터
  리턴값 : 성공적으로 저장하면 TRUE, 실패하면 FALSE 리턴
--------------------------------------------------------------------------------------*/
int enqueue(Queue * qPtr, DataType inData) 
{ 
	Node *np = (Node *)calloc(1, sizeof(Node)); //새로운 노드 생성
	if(np==NULL)  // 메모리 할당 실패하면 enqueue실패
	{
		return FALSE;
	}
	//노드를 테일 노드 바로 앞에 노드 추가
	qPtr->cur=qPtr->head;
	while(qPtr->cur->next!=qPtr->tail)  // 테일 노드 바로 앞노드를 cur로 가리키게 이동 시킴
		qPtr->cur = qPtr->cur->next; 
	
	qPtr->cur->next = np;
	np->next = qPtr->tail;
	np->data = inData; //데이터 복사

	return TRUE;

} 
/*--------------------------------------------------------------------------------------
  함수명 및 기능 : dequeue() - 큐에서 데이터 하나를 꺼냄
  전달인자 : qPtr - 큐 구조체의 주소
             getData - 꺼낸 데이터를 저장할 기억공간의 주소
  리턴값 : 성공적으로 꺼내면 TRUE, 실패하면 FALSE 리턴
--------------------------------------------------------------------------------------*/
int dequeue(Queue * qPtr, DataType * getData) 
{ 
	if( isQueueEmpty(qPtr) ) // 큐가 비어있으면 dequeue 불가 
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
  함수명및기능 : printQueue() - 큐 내의 모든 데이터를 출력 함
  전달인자 : qPtr - 큐 구조체의 주소
             print -  DataType의 내용을 출력하는 출력 보조 함수
  리턴값 : 없음
--------------------------------------------------------------------------------------*/
void printQueue(Queue * qPtr, void (*print)(DataType *) ) 
{ 
	if(isQueueEmpty(qPtr)==TRUE) 
	{
		printf("Queue가 비어있습니다!!\n");
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
  함수명및기능 : destroyQueue() - 큐 소멸 함수
  전달인자 : qPtr - 큐 구조체의 주소
  리턴값 : 없음
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
  함수명 및 기능: isQueueEmpty() - 큐가 비어있는가 검사
  전달인자: qPtr - 큐 구조체의 주소
  리턴값: 비어있으면 TRUE 리턴, 비어있지 않으면 FALSE 리턴
--------------------------------------------------------------------------------------*/
int isQueueEmpty(const Queue *qPtr)
{
	if(qPtr->head->next == qPtr->tail) 
		return TRUE;
	else 
		return FALSE;
}
