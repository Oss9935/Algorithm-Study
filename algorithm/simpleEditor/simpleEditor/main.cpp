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
	int opCnt;	//�Է��� ��ɾ��� ����
	DataType opCode, operand;

	fp = fileOpen(FILE_NAME, "rt");
	
	// ���� �ʱ�ȭ(Ŀ�� ���� left, right ���� ����)
	initStack(&left);
	initStack(&right);
	
	readString(&left, fp);		// ���Ͽ��� �����⿡ �ԷµǾ� �ִ� ���ڿ� read
	fscanf(fp, "%d", &opCnt);	// ���Ͽ��� �Է��� ��ɾ��� ���� read
	for (int i = 0; i < opCnt; i++)
	{
		opCode = NULL;
		operand = NULL;
		// ���Ͽ��� ��ɾ�, ��� ������ read
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
		if (ch == '\n') { break; }	//������ ù° �ٸ� read

		if ('a' <= ch && ch <= 'z')
			push(sPtr, ch);
		else { ; }	//�ҹ��� �̿��� ���� ���ÿ� push���� ����.
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