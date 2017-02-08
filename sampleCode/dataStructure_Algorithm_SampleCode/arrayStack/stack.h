#pragma once
#pragma warning(disable:4996)
#include "datatype.h"
typedef struct _stack{
	DataType *stack;       // stack으로 사용되는 배열을 가리키는 포인터 변수
	int sSize;             // 스택의 크기
	int top;               // 스택의 입,출구 위치정보 저장
}Stack;

void initStack(Stack *, int);     //스택 메모리 할당 및 초기화 함수 top의 위치를 0로 초기화
void clearStack(Stack *);         // 스택 비우는 함수
int push(Stack *, DataType);           // 스택에 데이터 저장하는 함수
int pop(Stack *, DataType *);          // 스택에서 데이터를 꺼내는 함수
void printStack(const Stack*, void (*print)(DataType *));    // 스택 내의 모든 데이터를 출력하는 함수
void destroyStack(Stack *);       // 스택 메모리 해제 함수
int isStackFull(Stack *sPtr);     // 스택이 꽉 차있는지 검사
int isStackEmpty(Stack *sPtr);    // 스택이 완전히 비어있는지 검사