#include "stack.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
/*--------------------------------------------------------------------------------------
함수명및기능: initStack() - 지정된 크기의 스택을 생성하는 함수
전달인자: sPtr -  스택의 주소
sSize - 스택의 크기
리턴값: 없음
--------------------------------------------------------------------------------------*/
void initStack(Stack *sPtr, int sSize)
{
	sPtr->stack = (DataType *)calloc(sSize , sizeof(DataType));  // 메모리 할당 & 0으로 초기화
	assert(sPtr->stack!=NULL);
	sPtr->sSize = sSize;
	sPtr->top = 0;
}
/*--------------------------------------------------------------------------------------
함수명및기능: clearStack() - 스택 초기화 함수(모든 데이터 삭제 개념)
전달인자: sPtr - 스택의 주소
리턴값: 없음
--------------------------------------------------------------------------------------*/
void clearStack(Stack *sPtr)
{
	while(sPtr->top!=0)
	{
		memset(&sPtr->stack[--sPtr->top], 0, sizeof(DataType));
	}
}
/*--------------------------------------------------------------------------------------
함수명및기능: push() - 스택에 데이터 하나를 저장함
전달인자: sPtr - 스택의 주소
inData - 스택에 저장할 데이터
리턴값: 성공적으로 저장하면1, 실패하면0 리턴
--------------------------------------------------------------------------------------*/
int push(Stack *sPtr, DataType inData) /* stack에 데이터 저장하기 */
{
	if(isStackFull(sPtr))  /* stack이 꽉 차있으면 */
		return 0;
	sPtr->stack[sPtr->top++] = inData;
	return 1;
}
/*--------------------------------------------------------------------------------------
함수명및기능: pop() - 스택에서 데이터 하나를 꺼냄
전달인자: sPtr - 스택의 주소
popData -  꺼낸 데이터를 저장할 기억공간의 주소
리턴값: 성공적으로 꺼내면1, 실패하면0 리턴
--------------------------------------------------------------------------------------*/
int pop(Stack * sPtr, DataType *popData)
{
	if(isStackEmpty(sPtr))  /* stack이 비어있으면 */
		return 0;
	*popData = sPtr->stack[--sPtr->top]; 
	
	return 1;
}
/*--------------------------------------------------------------------------------------
함수명및기능: printStack() - 스택의 모든 데이터를 출력 함
전달인자: sPtr -  스택의 주소
리턴값: 없음
--------------------------------------------------------------------------------------*/
void printStack(const Stack* sPtr, void (*print)(DataType *p))
{
	int i=sPtr->top;
	while(i!=0)
	{
		print( &sPtr->stack[--i]);
	}
	printf("\n");
}
/*--------------------------------------------------------------------------------------
함수명및기능: destroyStack() -  스택 소멸 함수
전달인자: sPtr -  스택의 주소
리턴값: 없음
--------------------------------------------------------------------------------------*/
void destroyStack(Stack *sPtr)
{
	clearStack(sPtr);
	free(sPtr->stack);
	sPtr->stack = NULL;
	sPtr->sSize = 0;
	sPtr->top = 0;
}
/*-----------------------------------------------------------------------------------
함수명 및 기능 : isStackFull() - 스택이 꽉 차있는지 검사
전달인자 : sPtr - 스택의 주소
리턴값 : 스택이 꽉 차있으면 1, 아니면 0 리턴
-----------------------------------------------------------------------------------*/
int isStackFull(Stack *sPtr)
{
	if (sPtr->top == sPtr->sSize)  /* stack이 꽉 차있으면 */
		return 1;
	else
		return 0;
}
/*-----------------------------------------------------------------------------------
함수명 및 기능 : isStackEmpty() - 스택이 비어있는지 검사
전달인자 : sPtr - 스택의 주소
리턴값 : 스택이 비어있으면 1, 아니면 0 리턴
-----------------------------------------------------------------------------------*/
int isStackEmpty(Stack *sPtr)
{ 
	if (sPtr->top == 0)  /* stack이 비어있으면 */
		return 1;
	else
		return 0;
}

