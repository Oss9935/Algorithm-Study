#include "liststack.h"
#include <stdio.h>
#include <assert.h>
#include <crtdbg.h>

#define FILE_NAME "c:\\data\\editor1.txt"
#define NEWL puts("")

FILE * fileOpen(char *fileName, char *mode);
void readString(Stack *sPtr, FILE* fp);
void moveLeft(Stack *pLeft, Stack *pRight);
void moveRight(Stack *pLeft, Stack *pRight);
void deleteChar(Stack *pLeft);
void addChar(Stack *pLeft, int operand);
void printStackInorder(Stack *pLeft, Stack *pRight);

int main()
{
	FILE *fp;
	Stack left, right;
	int opCnt;	//입력할 명령어의 갯수
	DataType opCode, operand;

	fp = fileOpen(FILE_NAME, "rt");
	
	// 스택 초기화(커서 기준 left, right 스택 구분)
	initStack(&left);
	initStack(&right);
	
	readString(&left, fp);		// 파일에서 편집기에 입력되어 있는 문자열 read
	fscanf(fp, "%d", &opCnt);	// 파일에서 입력할 명령어의 갯수 read
	for (int i = 0; i < opCnt; i++)
	{
		opCode = NULL;
		operand = NULL;
		// 파일에서 명령어, 대상 데이터 read
		fscanf(fp, " %c", &opCode);
		if(opCode == 'P')
			fscanf(fp, " %c", &operand);

		switch (opCode)
		{
		case 'L': moveLeft(&left, &right); break;
		case 'D': moveRight(&left, &right); break;
		case 'B': deleteChar(&left); break;
		case 'P': addChar(&left, operand); break;
		default:;
		}
	}

	printStackInorder(&left, &right);

	destroyStack(&left);
	destroyStack(&right);

	fclose(fp);

	return 0;
}

void moveLeft(Stack *pLeft, Stack *pRight)
{
	DataType curData;
	if (isStackEmpty(pLeft) == TRUE) { return; }

	pop(pLeft, &curData);
	push(pRight, curData);
}
void moveRight(Stack *pLeft, Stack *pRight)
{
	DataType curData;
	if (isStackEmpty(pRight) == TRUE) { return; }

	pop(pRight, &curData);
	push(pLeft, curData);
}
void deleteChar(Stack *pLeft)
{
	DataType curData;
	if (isStackEmpty(pLeft) == TRUE) { return; }
	pop(pLeft, &curData);
}
void addChar(Stack *pLeft, int operand)
{
	push(pLeft, operand);
}

void readString(Stack *sPtr, FILE* fp)
{
	DataType ch;

	while (1)
	{
		fscanf(fp, "%c", &ch);
		if (ch == '\n') { break; }	//파일의 첫째 줄만 read

		if ('a' <= ch && ch <= 'z')
			push(sPtr, ch);
		else { ; }	//소문자 이외의 경우는 스택에 push하지 않음.
	}
}

FILE * fileOpen(char *fileName, char *mode)
{
	FILE *fp;
	fp = fopen(fileName, mode);
	assert(fp != NULL);

	return fp;
}

void printChar(DataType *p)
{
	printf("%c", *p);
}

void printStackInorder(Stack *pLeft, Stack *pRight)
{
	DataType temp;

	while (pLeft->head->next != pLeft->tail)
	{
		pop(pLeft, &temp);
		push(pRight, temp);
	}
	printStack(pRight, printChar);
	NEWL;
}